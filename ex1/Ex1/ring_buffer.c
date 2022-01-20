#include "ring_buffer.h"

/**
 * @brief   Initializes ring buffer structure.
 * @param   [inout] me - ring buffer structure to be initialized
 * @param   [in] data - memory where ring buffer data will be stored
 * @param   [in] data_size - size of `data` argument
 * @return  true if initialized sucessfully, otherwise false
 */
bool ring_buffer_init(struct ring_buffer *me, uint8_t *data, size_t data_size) {
    if(data_size == 0) {
        me->initialized = false;
    } else {
        me->buffer_max_size = data_size;
        me->buffer = data;
        me->buffer_current_size = 0;
        me->head = 0;
        me->tail = 0;
        me->initialized = true;
    }
    return me->initialized;
}

/**
 * @brief   Clears ring buffer data.
 * @param   [inout] me - ring buffer structure
 * @return  true if cleared sucessfully, otherwise false
 */
bool ring_buffer_clear(struct ring_buffer *me) {
    if(!me->initialized) return false;
    me->head = 0;
    me->tail = 0;
    me->buffer_current_size = 0;
    return true;
}

/**
 * @brief   Checks if ring buffer is empty.
 * @param   [in] me - ring buffer structure
 * @return  true if buffer is empty, otherwise false
 */
bool ring_buffer_is_empty(const struct ring_buffer *me) {
    if(!me->initialized) return true;
    if(me->buffer_current_size == 0) return true;
    else return false;
}

/**
 * @brief   Gets current number of ring buffer elements.
 * @param   [in] me - ring buffer structure
 * @return  number of currently used data elements
 */
size_t ring_buffer_get_size(const struct ring_buffer *me) {
    if(!me->initialized) return false;
    return me->buffer_current_size;
}

/**
 * @brief   Gets maximum number of ring buffer elements that can be stored.
 * @param   [in] me - ring buffer structure
 * @return  maximum number of currently used data elements
 */
size_t ring_buffer_get_max_size(const struct ring_buffer *me) {
    if(!me->initialized) return false;
    return me->buffer_max_size;
}

/**
 * @brief   Appends new data to the ring buffer if there is empty place, increments current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [in] data - new data to be appended to the ring buffer
 * @return  true if data was successfully added into ring buffer, otherwise false
 */
bool ring_buffer_put(struct ring_buffer *me, uint8_t data) {
    if(!me->initialized) return false;
    if(me->head == me->tail && me->buffer_current_size > 0) return false;
    me->buffer[me->head++] = data;
    me->buffer_current_size++;
    if(me->head == me->buffer_max_size) me->head = 0;
    return true;
}

/**
 * @brief   Pulls data from the ring buffer, decrements current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [out] data - container for output data
 * @return  true if data was successfully added into output container, otherwise false
 */
bool ring_buffer_get(struct ring_buffer *me, uint8_t *data) {
    if(!me->initialized) return false;
    if(me->buffer_current_size == 0) return false;
    *data = me->buffer[me->tail++];
    me->buffer_current_size--;
    if(me->tail == me->buffer_max_size) me->tail = 0;
    return true;
}

