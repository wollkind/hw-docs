# /// script
# requires-python = ">=3.10"
# dependencies = ["beautifulsoup4", "markdownify", "requests"]
# ///
"""Save a vendor wiki/doc page as local markdown with its images.

    uv run tools/fetch_page.py URL OUT.md [--img-dir img]

Writes OUT.md (source + fetch date header, page body as markdown, images
downloaded next to it with rewritten links) and prints a JSON summary of
links on the page: downloadable files (pdf/zip/step/...) and same-site pages,
so the caller can decide what else to fetch.
"""
import argparse, datetime, hashlib, json, os, re, sys
from urllib.parse import urljoin, urlparse, unquote

import requests
from bs4 import BeautifulSoup
from markdownify import markdownify

UA = {"User-Agent": "Mozilla/5.0 (hw-docs fetcher)"}
MAIN = ["article", "main", "[role=main]", ".theme-doc-markdown", ".mw-parser-output",
        "#content", ".content", ".post-content", ".entry-content"]
JUNK = ["script", "style", "noscript", "nav", "footer", "header", "aside", "iframe", "form",
        ".breadcrumbs", ".pagination-nav", ".theme-doc-toc-mobile", ".table-of-contents",
        ".theme-edit-this-page", ".hash-link", ".headerlink"]
FILE_EXT = re.compile(r"\.(pdf|zip|7z|rar|step|stp|dxf|dwg|kicad_\w+|sch|brd|gbr|bin|uf2|ino|h|c|py|txt|csv|xlsx?)(\?|$)", re.I)


def pick_main(soup):
    for sel in MAIN:
        node = soup.select_one(sel)
        if node and len(node.get_text(strip=True)) > 200:
            return node
    return soup.body or soup


def save_image(src, page_url, img_dir, rel_dir):
    url = urljoin(page_url, src)
    if url.startswith("data:"):
        return None
    name = os.path.basename(unquote(urlparse(url).path)) or "img"
    stem, ext = os.path.splitext(name)
    name = f"{stem[:60]}-{hashlib.sha1(url.encode()).hexdigest()[:6]}{ext or '.png'}"
    path = os.path.join(img_dir, name)
    if not os.path.exists(path):
        try:
            r = requests.get(url, headers=UA, timeout=30)
            r.raise_for_status()
        except requests.RequestException as e:
            print(f"image failed: {url} ({e})", file=sys.stderr)
            return url
        os.makedirs(img_dir, exist_ok=True)
        with open(path, "wb") as f:
            f.write(r.content)
    return f"{rel_dir}/{name}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("url")
    ap.add_argument("out")
    ap.add_argument("--img-dir", default="img", help="relative to OUT's directory")
    a = ap.parse_args()

    r = requests.get(a.url, headers=UA, timeout=30)
    r.raise_for_status()
    soup = BeautifulSoup(r.content, "html.parser")  # bytes, so bs4 honours the page charset
    title = (soup.title.get_text(strip=True) if soup.title else a.url)
    body = pick_main(soup)
    for sel in JUNK:
        for n in body.select(sel):
            n.decompose()

    out_dir = os.path.dirname(os.path.abspath(a.out))
    img_dir = os.path.join(out_dir, a.img_dir)
    for img in body.find_all("img"):
        src = img.get("data-src") or img.get("src")
        if not src:
            continue
        local = save_image(src, a.url, img_dir, a.img_dir.replace(os.sep, "/"))
        if local:
            img["src"] = local
        for attr in ("srcset", "data-src", "loading", "decoding"):
            img.attrs.pop(attr, None)

    # Syntax highlighters split code into per-line divs/spans; flatten back to plain text.
    for pre in body.find_all("pre"):
        lines = [d.get_text() for d in pre.select(".token-line")]
        text = "\n".join(lines).strip("\n") if lines else pre.get_text()
        lang = next((c[9:] for c in pre.get("class", []) if c.startswith("language-")), "")
        pre.clear()
        pre["data-lang"] = lang
        pre.string = text

    files, pages = set(), set()
    host = urlparse(a.url).netloc
    for link in body.find_all("a", href=True):
        href = urljoin(a.url, link["href"]).split("#")[0]
        link["href"] = href
        if not href.startswith("http"):
            continue
        if FILE_EXT.search(urlparse(href).path):
            files.add(href)
        elif urlparse(href).netloc == host and href.rstrip("/") != a.url.rstrip("/"):
            pages.add(href)
        elif "github.com" in href:
            pages.add(href)

    md = markdownify(str(body), heading_style="ATX", bullets="-",
                      code_language_callback=lambda el: el.get("data-lang", ""))
    md = re.sub(r"\n{3,}", "\n\n", md).strip()
    today = datetime.date.today().isoformat()
    with open(a.out, "w", encoding="utf-8", newline="\n") as f:
        f.write(f"<!-- source: {a.url} | fetched: {today} -->\n# {title}\n\n{md}\n")

    print(json.dumps({"out": a.out, "title": title, "chars": len(md),
                      "files": sorted(files), "pages": sorted(pages)}, indent=1))


if __name__ == "__main__":
    main()
