# esptool test suite

See the [Automated Integration Tests section in `esptool` documentation](https://docs.espressif.com/projects/esptool/en/latest/esp32/contributing.html#automated-integration-tests) to learn about the test suite and how to run it.

## Binary fixtures

The suite uses a **hybrid** model:

- **Committed** real IDF / SDK (and historical) builds under `test/images/`,
  `test/secure_images/`, and `test/elf2image/`
- **Generated** size/fill blobs from [`bin_builder.py`](bin_builder.py) into
  `test/images/` at pytest start (not committed)

**License / redistribution:** see [`LICENSE`](LICENSE). Authored **sources**
(e.g. `ram_helloworld/source`) may be CC0; IDF-built **binaries** are not —
they follow ESP-IDF / component licenses. Incomplete-provenance goldens are
called out for packagers ([espressif/esptool#861](https://github.com/espressif/esptool/issues/861)).

| Path                               | Notes                                                                                   |
|------------------------------------|-----------------------------------------------------------------------------------------|
| [`images/`](images/)               | Flash/RAM fixtures and rebuild notes — [`images/README.md`](images/README.md)           |
| [`secure_images/`](secure_images/) | Keys and signed/encrypted images — [`secure_images/README.md`](secure_images/README.md) |
| [`elf2image/`](elf2image/)         | ELF inputs — [`elf2image/README.md`](elf2image/README.md)                               |
| [`bin_builder.py`](bin_builder.py) | Generates `one_kb.bin` / `one_mb.bin` / etc. before tests                               |
