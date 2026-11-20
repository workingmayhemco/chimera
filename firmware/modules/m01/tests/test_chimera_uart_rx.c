
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "chimera_uart_rx.h"
#include "chimera_input.h"

int main(void)
{
    ChimeraUartRx rx;
    ChimeraInput input;
    uint8_t byte = 0;

    ChimeraUartRx_Init(&rx);
    ChimeraInput_Init(&input);

    // Fill all 63 usable slots
    for (size_t i = 0;
         i < CHIMERA_RX_BUFFER_SIZE - 1;
         i++)
    {
        ChimeraUartRx_OnByte(&rx, 'X');
    }

    assert(rx.overflow == false);

    // The 64th byte is lost
    ChimeraUartRx_OnByte(&rx, 'P');

    assert(rx.overflow == true);
    assert(rx.discarding == true);
    assert(ChimeraUartRx_CanExecute(&rx) == false);

    // Terminator before acknowledgement is ignored
    ChimeraUartRx_OnByte(&rx, '\r');

    assert(rx.discarding == true);

    // Simulate main-loop recovery
    ChimeraInput_Init(&input);
    ChimeraUartRx_AcknowledgeOverflow(&rx);

    assert(rx.overflow == false);
    assert(rx.discarding == true);
    assert(rx.resume_armed == true);
    assert(rx.queue.head == rx.queue.tail);

    // First command after acknowledgement is discarded
    const char *discarded = "PING\r";

    for (size_t i = 0; discarded[i] != '\0'; i++)
    {
        ChimeraUartRx_OnByte(&rx, (uint8_t)discarded[i]);
    }

    assert(rx.discarding == false);
    assert(rx.resume_armed == false);
    assert(ChimeraUartRx_Pop(&rx, &byte) == false);

    // The next complete command is accepted
    const char *message = "PING\r";

    for (size_t i = 0; message[i] != '\0'; i++)
    {
        ChimeraUartRx_OnByte(&rx, (uint8_t)message[i]);
    }

    ChimeraInputResult result = CHIMERA_INPUT_INCOMPLETE;

    while (ChimeraUartRx_Pop(&rx, &byte))
    {
        result = ChimeraInput_Feed(&input, (char)byte);
    }

    assert(result == CHIMERA_INPUT_READY);
    assert(strcmp(input.command, "PING") == 0);
    assert(ChimeraUartRx_CanExecute(&rx) == true);

    printf("PASS: UART overflow recovery\n");

    return 0;
}
