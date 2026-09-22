# Sources (fetched 2026-09-22)

- https://cdn-shop.adafruit.com/product-files/3179/sx1276_77_78_79.pdf → `datasheets/sx1276-77-78-79-datasheet-rev4.pdf`. This is Semtech's own document (SX1276/77/78/79 datasheet, Rev 4, March 2015, 132 pages) rehosted by Adafruit for their RFM9x modules.

**Why not from semtech.com:** the product page at https://www.semtech.com/products/wireless-rf/lora-connect/sx1276 links its documents through `semtech.my.salesforce.com/sfc/p/...`. That URL returns an HTML page whose only content is a JavaScript form post-back; following the post-back by hand returns the Salesforce document viewer, which loads the file itself through a further scripted request. `curl` cannot reach the PDF, and `fetch_file.py` refuses the HTML. A browser can: open the product page, click **Datasheet**, and save the result.

Also behind the same post-back, not fetched: the **SX1276-7-8 Errata Note** and the application notes (AN1200.x), including AN1200.24 "SX1276 Settings for LoRaWAN" and AN1200.22 "LoRa Modulation Basics".
