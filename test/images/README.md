# test/images fixtures

Licensing: see [`../LICENSE`](../LICENSE).

- Sources under [`ram_helloworld/source/`](ram_helloworld/source/) are CC0-1.0;
  the committed `.bin` files are build artifacts, not CC0.
- IDF/SDK-built binaries follow ESP-IDF licensing (Apache-2.0 for IDF code,
  plus third-party components such as newlib) — not CC0.
- Size/fill blobs from [`../bin_builder.py`](../bin_builder.py) are generated
  at test time and are not committed.

Do not invent firmware goldens with `esptool`/`espsecure` when running the
suite (circular). Rebuild from the recipes below only when updating a fixture.

## `ram_helloworld/helloworld-*.bin`

On-device `load-ram` tests. Source: [`ram_helloworld/source/`](ram_helloworld/source/).

```bash
cd test/images/ram_helloworld/source
make   # needs Espressif GCC toolchains, or set CROSS_* in the Makefile
esptool --chip <chip> elf2image -o ../helloworld-<chip>.bin build/helloworld-<chip>.elf
```

Use a released esptool for the conversion step. `helloworld-esp32_edit.bin` is
a deliberately modified copy of the ESP32 image — re-apply that edit after a
rebuild if you refresh it.

## Size/fill blobs (not committed)

`one_kb.bin`, `one_mb.bin`, `fifty_kb.bin`, `sector.bin`, `zerolength.bin`,
`onebyte.bin`, `one_kb_all_ef.bin`, `aes_key.bin`:

```bash
python test/bin_builder.py   # also run automatically at pytest start
```

Generated with fixed xorshift seeds in [`../bin_builder.py`](../bin_builder.py)
(not bit-identical to the old committed files). `one_kb.bin` still starts with
`0xED` for `test_image_info.py` invalid-magic coverage.

## Bootloaders

| File                        | How to rebuild                                                                                                                                                                 |
|-----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `bootloader_esp32_v5_2.bin` | ESP-IDF `examples/get-started/hello_world` for esp32 → `idf.py bootloader` → copy `build/bootloader/bootloader.bin`. Update `test_image_info.py` if embedded metadata changes. |
| `bootloader_esp32.bin`      | ESP-IDF bootloader for esp32. Tests pin size **7888** bytes — update asserts if the new build differs.                                                                         |
| `bootloader_esp32c3.bin`    | ESP-IDF bootloader for esp32c3. `image-info` asserts pin layout/checksum — update them if refreshing.                                                                          |
| `bootloader_esp8266.bin`    | ESP8266 SDK bootloader for that chip.                                                                                                                                          |

## Apps and other IDF artifacts

| File                                               | How to rebuild                                                                                                                                   |
|----------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------|
| `esp_idf_blink_esp32s2.bin`                        | ESP-IDF blink example for esp32s2; copy the app binary. Update `test_image_info.py` app-info asserts if metadata changes.                        |
| `partitions_singleapp.bin`                         | See partition CSV below → `gen_esp32part.py`.                                                                                                    |
| `esp32c3_header_min_rev.bin`, `esp32s3_header.bin` | 48-byte header-only stubs (`0xE9` magic) for chip/revision write-flash checks — not full firmware. Edit header fields or truncate a known image. |

`partitions_singleapp.bin` CSV equivalent:

```csv
# Name,   Type, SubType, Offset,  Size
factory,  app,  factory, 0x10000, 1M
rfdata,   data, phy,     0x110000, 0x40000
wifidata, data, nvs,     0x150000, 0x40000
```

```bash
python $IDF_PATH/components/partition_table/gen_esp32part.py singleapp.csv partitions_singleapp.bin
```

## No in-tree rebuild recipe

| File | Notes |
|--------------------------|------------------------------------------------------------------------------|
| `not_4_byte_aligned.bin` | ESP8266 `image-info` golden; no source here.                                 |
| `esp8266_deepsleep.bin`  | Historical deep-sleep regression image; no complete source here.             |
| `efuse/*`                | Opaque test key blobs + `esp_efuse_custom_table.csv` (CSV is the editable form). |

These paths are listed under “Third-party or incomplete-source fixtures” in
[`../LICENSE`](../LICENSE).
