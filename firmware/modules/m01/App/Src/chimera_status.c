/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include "chimera_status.h"
#include <stdio.h>

int FormatStatus(uint32_t uptime_ms, char *response, size_t response_size)
{
  uint32_t uptime_sec = uptime_ms / 1000U;
  uint32_t uptime_min = uptime_sec / 60U;
  uint32_t hours = uptime_min / 60U;
  uint32_t minutes = uptime_min % 60U;
  uint32_t seconds = uptime_sec % 60U;

  return snprintf(
    response,
    response_size,
    "UPTIME: %02lu:%02lu:%02lu\r\n",
    (unsigned long)hours,
    (unsigned long)minutes,
    (unsigned long)seconds
  );
}