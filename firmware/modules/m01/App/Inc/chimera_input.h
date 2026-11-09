/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

#ifndef CHIMERA_INPUT_H
#define CHIMERA_INPUT_H

typedef struct
{
    char command[16];
    size_t index;
    bool overflow;
} ChimeraInput;

typedef enum
{
    CHIMERA_INPUT_INCOMPLETE,
    CHIMERA_INPUT_READY,
    CHIMERA_INPUT_OVERFLOW,
} ChimeraInputResult;

void ChimeraInput_Init(ChimeraInput *input);

ChimeraInputResult ChimeraInput_Feed(
    ChimeraInput *input,
    char incoming
);

#endif // CHIMERA_INPUT_H