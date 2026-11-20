/*
SPDX-FileCopyrightText: 2026 Working Mayhem
SPDX-License-Identifier: Apache-2.0
*/
#ifndef CHIMERA_UART_RX_H
#define CHIMERA_UART_RX_H

#include <stdbool.h>
#include <stdint.h>

#include "chimera_rx_buffer.h"

typedef struct
{
    ChimeraRxBuffer queue;
    volatile bool overflow;
    volatile bool discarding;
    volatile bool resume_armed;
} ChimeraUartRx;

void ChimeraUartRx_Init(ChimeraUartRx *rx);

void ChimeraUartRx_OnByte(ChimeraUartRx *rx, uint8_t byte);

void ChimeraUartRx_AcknowledgeOverflow(ChimeraUartRx *rx);

bool ChimeraUartRx_Pop(ChimeraUartRx *rx, uint8_t *byte);

bool ChimeraUartRx_CanExecute(const ChimeraUartRx *rx);

#endif // CHIMERA_UART_RX_H