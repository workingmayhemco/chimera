/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include "chimera_status.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  char response[128];

  int written = FormatStatus(
    3675000U,
    response, 
    sizeof(response)
  );

  assert(written > 0);
  assert((size_t)written < sizeof(response));
  assert(strcmp(response, "UPTIME: 01:01:15\r\n") == 0);

  written = FormatStatus(
    0U,
    response,
    sizeof(response)
  );

  assert(written > 0);
  assert((size_t)written < sizeof(response));
  assert(strcmp(response, "UPTIME: 00:00:00\r\n") == 0);

  char small_response[8];

  written = FormatStatus(
    3675000U,
    small_response,
    sizeof(small_response)
  );

  assert(written == 18);
  assert(strcmp(small_response, "UPTIME:") == 0);
  assert(written < 0 || (size_t)written >= sizeof(small_response));

  printf("PASS: FormatStatus\n");

  return 0;
}