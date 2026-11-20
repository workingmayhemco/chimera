/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include <assert.h>
#include <stdio.h>

#include "chimera_commands.h"

int main(void)
{
  assert(ChimeraCommands_Parse("PING") == CHIMERA_CMD_PING);
  assert(ChimeraCommands_Parse("HELP") == CHIMERA_CMD_HELP);
  assert(ChimeraCommands_Parse("STATUS") == CHIMERA_CMD_STATUS);
  assert(ChimeraCommands_Parse("BANANA") == CHIMERA_CMD_UNKNOWN);
  assert(ChimeraCommands_Parse("ping") == CHIMERA_CMD_UNKNOWN);

  printf("PASS: ChimeraCommands_Parse\n");

  return 0;
}
