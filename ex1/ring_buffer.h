#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

//------------------------------------------------------------------------------

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//------------------------------------------------------------------------------

struct ring_buffer
{
    /** TODO: Fill ring buffer structure. */
    uint8_t *buffer;
    size_t buffer_max_size;
    size_t buffer_current_size;
    size_t head;
    size_t tail;
    bool initialized;
};

//------------------------------------------------------------------------------

/**
 * @brief   Initializes ring buffer structure.
 * @param   [inout] me - ring buffer structure to be initialized
 * @param   [in] data - memory where ring buffer data will be stored
 * @param   [in] data_size - size of `data` argument
 * @return  true if initialized sucessfully, otherwise false
 */
bool ring_buffer_init(struct ring_buffer *me, uint8_t *data, size_t data_size);

/**
 * @brief   Clears ring buffer data.
 * @param   [inout] me - ring buffer structure
 * @return  true if cleared sucessfully, otherwise false
 */
bool ring_buffer_clear(struct ring_buffer *me);

/**
 * @brief   Checks if ring buffer is empty.
 * @param   [in] me - ring buffer structure
 * @return  true if empty sucessfully, otherwise false
 */
bool ring_buffer_is_empty(const struct ring_buffer *me);

/**
 * @brief   Gets current number of ring buffer elements.
 * @param   [in] me - ring buffer structure
 * @return  number of currently used data elements
 */
size_t ring_buffer_get_size(const struct ring_buffer *me);

/**
 * @brief   Gets maximum number of ring buffer elements that can be stored.
 * @param   [in] me - ring buffer structure
 * @return  maximum number of currently used data elements
 */
size_t ring_buffer_get_max_size(const struct ring_buffer *me);

/**
 * @brief   Appends new data to the ring buffer if there is empty place, increments current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [in] data - new data to be appended to the ring buffer
 * @return  true if data was successfully added into ring buffer, otherwise false
 */
bool ring_buffer_put(struct ring_buffer *me, uint8_t data);

/**
 * @brief   Pulls data from the ring buffer, decrements current size by 1.
 * @param   [inout] me - ring buffer structure
 * @param   [out] data - container for output data
 * @return  true if data was successfully added into ring buffer, otherwise false
 */
bool ring_buffer_get(struct ring_buffer *me, uint8_t *data);

//------------------------------------------------------------------------------

#endif /* _RING_BUFFER_H_ */
