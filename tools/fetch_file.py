# /// script
# requires-python = ">=3.10"
# dependencies = ["requests"]
# ///
"""Download a datasheet/schematic/etc. and check it is what its extension says.

    uv run tools/fetch_file.py URL OUT

Vendors often answer a dead PDF link with an HTML page and status 200. The file
is refused (not written) when its first bytes don't match the extension, so a
"datasheet.pdf" that is really a login page never lands in the library.
Prints: OUT <bytes> <sha256-prefix>
"""
import argparse, hashlib, os, sys

import requests

UA = {"User-Agent": "Mozilla/5.0 (hw-docs fetcher)"}
MAGIC = {
    ".pdf": [b"%PDF"],
    ".zip": [b"PK\x03\x04"],
    ".png": [b"\x89PNG"],
    ".jpg": [b"\xff\xd8\xff"],
    ".jpeg": [b"\xff\xd8\xff"],
    ".gif": [b"GIF8"],
    ".webp": [b"RIFF"],
    ".7z": [b"7z\xbc\xaf"],
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("url")
    ap.add_argument("out")
    a = ap.parse_args()

    try:
        r = requests.get(a.url, headers=UA, timeout=120, allow_redirects=True)
        r.raise_for_status()
    except requests.RequestException as e:
        sys.exit(f"FAILED {a.url}: {e}")
    data = r.content
    ext = os.path.splitext(a.out)[1].lower()
    head = data[:512].lstrip().lower()
    if ext in MAGIC and not any(data.startswith(m) for m in MAGIC[ext]):
        sys.exit(f"REFUSED {a.url}: not a {ext} (starts {data[:16]!r}, "
                 f"content-type {r.headers.get('content-type')})")
    if ext not in (".html", ".htm", ".md") and (head.startswith(b"<!doctype html") or head.startswith(b"<html")):
        sys.exit(f"REFUSED {a.url}: got an HTML page, not a {ext or 'file'}")

    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    with open(a.out, "wb") as f:
        f.write(data)
    print(a.out, len(data), hashlib.sha256(data).hexdigest()[:12])


if __name__ == "__main__":
    main()
