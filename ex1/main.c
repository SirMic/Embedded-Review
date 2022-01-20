#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"

#define BUFFER_SIZE 1024

struct ring_buffer TestRingBuffer;
uint8_t DataBuffer[BUFFER_SIZE];
int main(int arc, char *argv[])
{
    ring_buffer_init(&TestRingBuffer, DataBuffer, BUFFER_SIZE);
    printf("%d", sizeof(size_t));

    /** TODO: Write tests using assert.h */
    // Example - wrong data_size function argument:
    // assert(ring_buffer_init(&ring, &data, 0) == false);
};
