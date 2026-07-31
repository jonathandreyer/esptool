/* SPDX-FileCopyrightText: 2016-2026 Espressif Systems (Shanghai) CO LTD
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdlib.h>

void ets_printf(const char *s); // not the correct prototype, but should be enough!

void __attribute__((noreturn)) ram_main()
{
  while (1) {
    ets_printf("Hello world!\n");
  }
}
