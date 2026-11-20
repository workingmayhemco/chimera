/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#ifndef CHIMERA_RUNTIME_H
#define CHIMERA_RUNTIME_H

#include <stdint.h>
#include <stddef.h>

int ProcessCommand(
    const char *command,
    uint32_t uptime_ms,
    char *response,
    size_t response_size
);

#endif // CHIMERA_RUNTIME_H