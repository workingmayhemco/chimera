#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "chimera_rx_buffer.h"

int main(void)
{
    ChimeraRxBuffer rx;
    uint8_t byte = 0;

    ChimeraRx_Init(&rx);

    assert(rx.head == 0);
    assert(rx.tail == 0);

    assert(ChimeraRx_Push(&rx, 'A') == true);
    assert(ChimeraRx_Push(&rx, 'B') == true);

    assert(ChimeraRx_Pop(&rx, &byte) == true);
    assert(byte == 'A');

    assert(ChimeraRx_Pop(&rx, &byte) == true);
    assert(byte == 'B');

    assert(rx.head == rx.tail);

    assert(ChimeraRx_Pop(&rx, &byte) == false);
    assert(byte == 'B');

    printf("PASS: ChimeraRx FIFO\n");
    
    // Start a new test scenario
    ChimeraRx_Init(&rx);
    
    // Fill all 63 usable slots in the buffer
    for (size_t i = 0; i < CHIMERA_RX_BUFFER_SIZE - 1; i++)
    {
        assert(ChimeraRx_Push(&rx, 'A') == true);
    }
    
    assert(rx.head == 63);
    assert(rx.tail == 0);
    
    assert(ChimeraRx_Push(&rx, 'B') == false);
    
    assert(rx.head == 63);
    assert(rx.tail == 0);
    
    // Remove one byte
    assert(ChimeraRx_Pop(&rx, &byte) == true);
    assert(byte == 'A');
    
    assert(rx.tail == 1);
    
    // Now there's room for B
    assert(ChimeraRx_Push(&rx, 'B') == true);
    
    // Head wraps from 63 to 0
    assert(rx.head == 0);
    assert(rx.tail == 1);
    
    for (size_t i = 0; i < 62; i++)
    {
        // Pop a byte
        assert(ChimeraRx_Pop(&rx, &byte) == true);
        // Assert that it equals 'A'
        assert(byte == 'A');
    }
    
    // Pop the last byte and verify it equals 'B'
    assert(ChimeraRx_Pop(&rx, &byte) == true);
    assert(byte == 'B');
    
    // Verify that the buffer is now empty
    assert(rx.head == rx.tail);
    printf("PASS: ChimeraRx FIFO wrap-around\n");
    return 0;
}