/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/

// #include <stdbool.h>
// #include <stdint.h>

#include "chimera_uart_rx.h"

void ChimeraUartRx_Init(ChimeraUartRx *rx)
{
    ChimeraRx_Init(&rx->queue);

    rx->overflow = false;
    rx->discarding = false;
    rx->resume_armed = false;
}

void ChimeraUartRx_OnByte(ChimeraUartRx *rx, uint8_t byte)
{
    if (rx->discarding)
    {
        if (rx->resume_armed &&
            (byte == '\r' || byte == '\n'))
        {
            rx->resume_armed = false;
            rx->discarding = false;
        }

        return;
    }

    if (!ChimeraRx_Push(&rx->queue, byte))
    {
        rx->overflow = true;
        rx->discarding = true;
    }
}

void ChimeraUartRx_AcknowledgeOverflow(ChimeraUartRx *rx)
{
    // Caller must prevent ISR access during reset.
    if (rx->overflow)
    {
        ChimeraRx_Init(&rx->queue);
        rx->overflow = false;
        rx->resume_armed = true;
    }
}

bool ChimeraUartRx_Pop(
    ChimeraUartRx *rx,
    uint8_t *byte
)
{
    return ChimeraRx_Pop(&rx->queue, byte);
}

bool ChimeraUartRx_CanExecute(const ChimeraUartRx *rx)
{
    return !rx->overflow &&
           !rx->discarding &&
           !rx->resume_armed;
}