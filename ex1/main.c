#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"

#define BUFFER_MAX_SIZE 1024

struct ring_buffer ring;
uint8_t data[BUFFER_MAX_SIZE];
uint8_t test_put_data = 5, test_get_data;

int main(int arc, char *argv[])
{
    /* Trying initialize buffer with wrong data_size
        1) function ring_buffer_init should return false
    */
    assert(ring_buffer_init(&ring, data, 0) == false);

    /** Tests with buffer uninitialized */
    /* When ring buffer is uninitialized
        2) initialized flag should be false
        3) other functions should return false (except ring_buffer_is_empty, this should return true due to initialized buffer)
    */
    assert(ring.initialized == false);
    assert(ring_buffer_get_max_size(&ring) == false);
    assert(ring_buffer_clear(&ring) == false);
    assert(ring_buffer_is_empty(&ring) == true);
    assert(ring_buffer_get_size(&ring) == false);
    assert(ring_buffer_get_max_size(&ring) == false);
    assert(ring_buffer_put(&ring, test_put_data) == false);
    assert(ring_buffer_get(&ring, &test_put_data) == false);

    /** Tests with buffer initialized */
    /* When correct data_size
        1) function ring_buffer_init should return true (ring buffer initialized)
        2) initialized flag should be true
        3) function ring_buffer_is_empty should return true
    */
    assert(ring_buffer_init(&ring, data, BUFFER_MAX_SIZE) == true);
    assert(ring.initialized == true);
    assert(ring_buffer_is_empty(&ring) == true);
    /* Function ring_buffer_get_max_size should return BUFFER_MAX_SIZE */
    assert(ring_buffer_get_max_size(&ring) == BUFFER_MAX_SIZE);
    /* Trying get data from empty buffer
        1) function ring_buffer_get should return false
    */
    assert(ring_buffer_get(&ring, &test_get_data) == false);
    /* Trying put data into empty buffer
        1) function ring_buffer_put should return true
        2) function ring_buffer_get_size should return 1 after putting data into buffer
        3) head should be equal to 1
    */
    assert(ring_buffer_put(&ring, test_put_data) == true);
    assert(ring_buffer_get_size(&ring) == 1);
    assert(ring.head == 1);
    /* Trying get data from non-empty buffer
        1) function ring_buffer_get should return true
        2) data from ring_buffer_get should be equal to test_put_data
        3) function ring_buffer_get_size should return 0 after getting data
        4) tail should be equal to 1
    */
    assert(ring_buffer_get(&ring, &test_get_data) == true);
    assert(test_get_data == test_put_data);
    assert(ring_buffer_get_size(&ring) == 0);
    assert(ring.tail == 1);
    /* Clearing buffer
        1) function ring_buffer_clear should return true
        2) head, tail, current_buffer_size should be equal to 0
    */
    assert(ring_buffer_clear(&ring) == true);
    assert(ring.head == 0);
    assert(ring.tail == 0);
    assert(ring.buffer_current_size == 0);

        /** Tests with full buffer */
    for(uint16_t i=0; i < 1024; i++) ring_buffer_put(&ring, test_put_data);
    /*
        function ring_buffer_get_size should return BUFFER_MAX_SIZE
    */
    assert(ring_buffer_get_size(&ring) == BUFFER_MAX_SIZE);
    /* Trying put data into full buffer
        1) function ring_buffer_put should return false (buffer full, new data will be lost)
        2) head should be equal to 0 (reached end of buffer, skipped to start)
    */
    assert(ring_buffer_put(&ring, test_put_data) == false);
    assert(ring.head == 0);

    /* Manually clear buffer */
    for(uint16_t i = 0; i < 1024; i++) {
        ring_buffer_get(&ring, &test_put_data);
    }
    /*
        1) function ring_buffer_get should return false
        2) function ring_buffer_get_size should return 0
        3) tail should be equal to 0 (reached end of buffer, skipped to start)
    */
    assert(ring_buffer_get(&ring, &test_get_data) == false);
    assert(ring_buffer_get_size(&ring) == 0);
    assert(ring.tail == 0);


};
