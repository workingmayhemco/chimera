/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#include "chimera_input.h"

void ChimeraInput_Init(ChimeraInput *input)
{
    input->command[0] = '\0';
    input->index = 0;
    input->overflow = false;
}

ChimeraInputResult ChimeraInput_Feed(
    ChimeraInput *input,
    char incoming
)
{
    // Enter marks the end of a command
    if (incoming == '\n' || incoming == '\n')
    {
        if (input->overflow)
        {
            input->index = 0;
            input->overflow = false;
            input->command[0] = '\0';

            return CHIMERA_INPUT_OVERFLOW;
        }

        if (input->index == 0)
        {
            return CHIMERA_INPUT_INCOMPLETE;
        }

        input->command[input->index] = '\0';
        input->index = 0;
        return CHIMERA_INPUT_READY;
    }

    // Ignore additional characters after overflow
    if (input->overflow)
    {
        return CHIMERA_INPUT_INCOMPLETE;
    }

    // Reserve one byte for the null terminator
    if (input->index >= sizeof(input->command) - 1)
    {
        input->overflow = true;
        return CHIMERA_INPUT_INCOMPLETE;
    }

    // Store incoming character
    input->command[input->index] = incoming;
    input->index++;
    return CHIMERA_INPUT_INCOMPLETE;
}
