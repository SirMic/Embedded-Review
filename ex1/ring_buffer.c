
#include "ring_buffer.h"


bool ring_buffer_init(struct ring_buffer *me, uint8_t *data, size_t data_size) {

    if(data_size == 0) return false;
    ring_buffer->buffer_size = data_size;
    ring_buffer->buffer = data;
    ring_buffer->head = 0;
    ring_buffer->tail = 0;
    return true;
}
