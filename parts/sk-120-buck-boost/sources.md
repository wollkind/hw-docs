# Sources (fetched 2026-09-21)

- Listing: https://www.amazon.com/dp/B0D9H3Z637 — not fetched (amazon.com is blocked by the sandbox proxy). The 6–36 V in / 0–36 V out / 120 W figures in `README.md` come from the queue entry the owner wrote from that listing, not from a vendor document.
- Vendor PDFs, via https://github.com/csvke/XY-SK120-Modbus-RTU-TTL @ `53cdfafa6cb38539919c59eb4c5cde66a0e7ad7f`, which bundles them in `documentation/`:
  - `XY-SK120X.pdf` → `datasheets/xy-sk120-modbus-protocol.pdf`
  - `XY-SK120-Modbus_Address.pdf` → `datasheets/xy-sk120-modbus-address.pdf`
  - `lib/XY-SKxxx/XY-SKxxx.h` → `reference/`
  - `documentation/Data Group (Press VSET To rotate paramet.md` → `reference/data-group-osd-notes.md`
- Not copied from that repo: `20240731220204XY-SK60.pdf` (3.6 MB scan of the **SK60** user guide, image-only, no extractable text), `XY6020L-Modbus-Interface.pdf` (different product), `XY-SK120X.docx` (same content as the PDF).
- Manuals found but unreachable from the sandbox (all blocked by the egress proxy): https://telemetry2u.com/downloads/SK60_SK120_Power_Supply_User_Guide.pdf, manuals.plus listings for SK120X / SK60-SK120 / SK150-SK120, https://done.land/components/power/powersupplies/dc-dc-converters/plug&playconverters/xy-sk120x/. Any of these would settle the electrical specs and the front-panel menu.
- Open: which variant the owner has (SK120 / SK120X / SK120D) and whether it carries the Sinilink ESP8285 Wi-Fi module. The TTL header is present on all of them.
