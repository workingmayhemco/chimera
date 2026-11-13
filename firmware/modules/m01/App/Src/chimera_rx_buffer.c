/*
 * SPDX-FileCopyrightText: 2026 Working Mayhem
 * SPDX-License-Identifier: Apache-2.0
 */

 #include "chimera_rx_buffer.h"

void ChimeraRx_Init(ChimeraRxBuffer *buffer)
{
  buffer->head = 0;
  buffer->tail = 0;
}

bool ChimeraRx_Push(ChimeraRxBuffer *buffer, uint8_t byte)
{
  uint8_t head = buffer->head;

  uint8_t next = (uint8_t)(
    (head + 1U) % CHIMERA_RX_BUFFER_SIZE
  );

  // Buffer is full
  if (next == buffer->tail)
  {
    return false;
  }

  // Store the byte, then publish the new head
  buffer->data[head] = byte;
  buffer->head = next;
  return true;
}

bool ChimeraRx_Pop(ChimeraRxBuffer *buffer, uint8_t *byte)
{
  uint8_t tail = buffer->tail;

  // Buffer is empty
  if (tail == buffer->head)
  {
    return false;
  }

  // Read the byte, then release its slot
  *byte = buffer->data[tail];

  buffer->tail = (uint8_t)(
    (tail + 1U) % CHIMERA_RX_BUFFER_SIZE
  );
  return true;
}