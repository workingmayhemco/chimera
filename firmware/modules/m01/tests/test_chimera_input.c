/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#include "chimera_input.h"

int main(void)
{
  ChimeraInput input;

  ChimeraInput_Init(&input);

  assert(input.index == 0);
  assert(input.overflow == false);

  assert(ChimeraInput_Feed(&input, 'P') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'I') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'N') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'G') == CHIMERA_INPUT_INCOMPLETE);

  assert(ChimeraInput_Feed(&input, '\r') == CHIMERA_INPUT_READY);

  assert(strcmp(input.command, "PING") == 0);

  // Test maximum command length: 15 characters
  ChimeraInput_Init(&input);

  const char *message = "ABCDEFGHIJKLMNO";

  for (size_t i = 0; message[i] != '\0'; i++)
  {
    assert(
      ChimeraInput_Feed(&input, message[i]) == CHIMERA_INPUT_INCOMPLETE
    );
  }

  assert(input.index == 15);
  assert(input.overflow == false);

  assert(ChimeraInput_Feed(&input, '\r') == CHIMERA_INPUT_READY);

  assert(strcmp(input.command, message) == 0);

  // Test overflow
  ChimeraInput_Init(&input);

  const char *long_message = "ABCDEFGHIJKLMNOP";

  for (size_t i = 0; long_message[i] != '\0'; i++)
  {
    assert(
      ChimeraInput_Feed(&input, long_message[i]) == CHIMERA_INPUT_INCOMPLETE
    );
  }

  assert(input.index == 15);
  assert(input.overflow == true);


  assert(ChimeraInput_Feed(&input, '\r') == CHIMERA_INPUT_OVERFLOW);
  
  assert(input.index == 0);
  assert(input.overflow == false);
  assert(input.command[0] == '\0');

  // test recovery after overflow

  assert(ChimeraInput_Feed(&input, 'P') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'I') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'N') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'G') == CHIMERA_INPUT_INCOMPLETE);
  
  assert(ChimeraInput_Feed(&input, '\r') == CHIMERA_INPUT_READY);

  assert(strcmp(input.command, "PING") == 0);
  assert(input.overflow == false);

  // Test CRLF command termination
  ChimeraInput_Init(&input);

  assert(ChimeraInput_Feed(&input, 'P') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'I') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'N') == CHIMERA_INPUT_INCOMPLETE);
  assert(ChimeraInput_Feed(&input, 'G') == CHIMERA_INPUT_INCOMPLETE);
  
  // Carriage return completes the command
  assert(ChimeraInput_Feed(&input, '\r') == CHIMERA_INPUT_READY);
  assert(strcmp(input.command, "PING") == 0);

  // Line feed must NOT produce another command
  assert(ChimeraInput_Feed(&input, '\n') == CHIMERA_INPUT_INCOMPLETE);
  assert(input.index == 0);

  printf("PASS: ChimeraIn put basic command\n");

  return 0;
}