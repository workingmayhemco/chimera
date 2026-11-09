/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#ifndef CHIMERA_STATUS_H
#define CHIMERA_STATUS_H

#include <stdint.h>
#include <stddef.h>

int FormatStatus(uint32_t uptime_ms, char *response, size_t response_size);

#endif // CHIMERA_STATUS_H 