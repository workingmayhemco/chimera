/*
 * SPDX-FileCopyrightText: 2026 Working Mayhem
 * SPDX-License-Identifier: Apache-2.0
 */

 #ifndef CHIMERA_RX_BUFFER_H
 #define CHIMERA_RX_BUFFER_H

 #include <stdint.h>
 #include <stdbool.h>
 #include <stddef.h>

 #define CHIMERA_RX_BUFFER_SIZE 64U

 typedef struct
 {
    volatile uint8_t data[CHIMERA_RX_BUFFER_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
 } ChimeraRxBuffer;

 void ChimeraRx_Init(ChimeraRxBuffer *buffer);

 bool ChimeraRx_Push(ChimeraRxBuffer *buffer, uint8_t byte);

 bool ChimeraRx_Pop(ChimeraRxBuffer *buffer, uint8_t *byte);

 #endif // CHIMERA_RX_BUFFER_H