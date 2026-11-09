/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/
#ifndef CHIMERA_COMMANDS_H
#define CHIMERA_COMMANDS_H

typedef enum
{
  CHIMERA_CMD_UNKNOWN = 0,
  CHIMERA_CMD_PING,
  CHIMERA_CMD_HELP,
  CHIMERA_CMD_STATUS,
} ChimeraCommand;

ChimeraCommand ChimeraCommands_Parse(const char *command);

#endif // CHIMERA_COMMANDS_H