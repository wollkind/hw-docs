# Sources (fetched 2026-09-21, extended 2026-09-22)

- Listing: https://www.amazon.com/dp/B0D9H3Z637 — not fetched. The 6–36 V in / 0–36 V out / 120 W figures were originally taken from the owner's queue entry; the 120 W/6 A rating and its 130–150 W qualification are now confirmed from the vendor manual below, and the 6–36 V / 0–36 V range from the community write-up.
- Vendor PDFs, via https://github.com/csvke/XY-SK120-Modbus-RTU-TTL @ `53cdfafa6cb38539919c59eb4c5cde66a0e7ad7f`, which bundles them in `documentation/`:
  - `XY-SK120X.pdf` → `datasheets/xy-sk120-modbus-protocol.pdf`
  - `XY-SK120-Modbus_Address.pdf` → `datasheets/xy-sk120-modbus-address.pdf`
  - `lib/XY-SKxxx/XY-SKxxx.h` → `reference/`
  - `documentation/Data Group (Press VSET To rotate paramet.md` → `reference/data-group-osd-notes.md`
- Not copied from that repo: `20240731220204XY-SK60.pdf` (3.6 MB scan of the **SK60** user guide, image-only, no extractable text), `XY6020L-Modbus-Interface.pdf` (different product), `XY-SK120X.docx` (same content as the PDF).
- https://telemetry2u.com/downloads/SK60_SK120_Power_Supply_User_Guide.pdf → `manuals/sk60-sk120-user-guide.pdf` (fetched 2026-09-22, 10.4 MB). The pages are mostly images; the text layer carries the operating instructions, the CV/CC/CW description, the 120 W/150 W rating note, the reverse-connection warning and the package weight, but **no electrical specification table**.
- https://done.land/components/power/powersupplies/dc-dc-converters/plug&playconverters/xy-sk120x/ → `wiki/done-land-xy-sk120x.md` (fetched 2026-09-22). A community write-up, not a vendor document: it is the source for the 0.01 V display resolution, the dimensions, the terminal labels and the slow-feedback observation, and everything taken from it is marked in `README.md`.
- Still missing: a manufacturer specification sheet with tolerances, ripple, efficiency and the exact input/output limits per variant. The manuals.plus listings for SK120X / SK60-SK120 / SK150-SK120 were not fetched.
- Open: which variant the owner has (SK120 / SK120X / SK120D) and whether it carries the Sinilink ESP8285 Wi-Fi module. The TTL header is present on all of them.
