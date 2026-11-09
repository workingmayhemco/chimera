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

  printf("PASS: FormatStatus\n");

  return 0;
}