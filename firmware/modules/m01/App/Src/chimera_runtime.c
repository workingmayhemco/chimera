/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include "chimera_runtime.h"
#include "chimera_commands.h"
#include "chimera_status.h"

#include <stdio.h>

int ProcessCommand(
    const char *command,
    uint32_t uptime_ms,
    char *response,
    size_t response_size
)
{
    ChimeraCommand parsed = ChimeraCommands_Parse(command);

    switch (parsed)
    {
        case CHIMERA_CMD_PING:
          return snprintf(
            response,
            response_size,
            "PONG\r\n"
          );

        case CHIMERA_CMD_HELP:
          return snprintf(
            response,
            response_size,
            "Available commands: PING, HELP, STATUS\r\n"
          );

        case CHIMERA_CMD_STATUS:
          return FormatStatus(
            uptime_ms,
            response,
            response_size
          );
        
        default:
          return snprintf(
            response,
            response_size,
            "UNKNOWN COMMAND\r\n"
          );
    }
}