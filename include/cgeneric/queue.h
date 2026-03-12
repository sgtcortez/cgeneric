#ifndef __C_GENERIC_QUEUE_H__
#define __C_GENERIC_QUEUE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct queue queue;

#define QUEUE_CONSTRUCT(_QUEUE_TYPE, _QUEUE_ELEMENTS)(queue_construct(_QUEUE_ELEMENTS, sizeof(_QUEUE_TYPE), #_QUEUE_TYPE))
#define QUEUE_INIT(_QUEUE_QUEUE, _QUEUE_TYPE, _QUEUE_ELEMENTS)(queue_init(_QUEUE_QUEUE, _QUEUE_ELEMENTS, sizeof(_QUEUE_TYPE), #_QUEUE_TYPE))
#define QUEUE_PUSH(_QUEUE_QUEUE, _QUEUE_TYPE,  QUEUE_VALUE)({typeof(QUEUE_VALUE) tmp = (QUEUE_VALUE); queue_push(_QUEUE_QUEUE, &tmp, #_QUEUE_TYPE);})
#define QUEUE_DESTROY(_QUEUE_QUEUE)queue_destroy(&_QUEUE_QUEUE)
#define QUEUE_POP(_QUEUE_QUEUE, _QUEUE_TYPE)({_QUEUE_TYPE tmp[1] = {0}; queue_pop(_QUEUE_QUEUE, tmp, #_QUEUE_TYPE); *tmp; })
#define QUEUE_SIZE(_QUEUE_QUEUE)queue_size(_QUEUE_QUEUE)
#define QUEUE_RESIZE(_QUEUE_QUEUE, _QUEUE_ELEMENTS)queue_resize(&_QUEUE_QUEUE, _QUEUE_ELEMENTS);
#define QUEUE_PEEK(_QUEUE_QUEUE, _QUEUE_TYPE)({_QUEUE_TYPE tmp[1] = {0}; queue_peek(_QUEUE_QUEUE, tmp, #_QUEUE_TYPE); *tmp;}) 
#define QUEUE_FOREACH(_QUEUE_QUEUE, _QUEUE_TYPE, _CALLBACK, _USER_DATA)({queue_for_each(_QUEUE_QUEUE, _CALLBACK, _USER_DATA, #_QUEUE_TYPE);}) 


/**
 * Constructs a queue(allocates memory using default malloc)
 * Calle is the owner of the returned pointer
*/
queue* queue_construct(uint16_t capacity, uint16_t size_per_element, char* typename);

/**
 * Let the user allocate memory(this can be allocated on stack, heap, static) 
*/
void queue_init(queue* queue, uint16_t capacity, uint16_t size_per_element, char* typename);

/**
 * Deallocate the memory using default free and set the pointer to null(0x00)
*/
void queue_destroy(queue** queue);

/**
 * Push elements into the queue
 * Returns true on success, false when there is no more space(and a resize must be done)
*/
bool queue_push(queue* queue, const void* const data, char* typename);

/**
 * Pops the top element from the queue
*/
void queue_pop(queue* queue, void* result, char* typename);

/**
 * Returns the size of the queue(how many elements are there)
*/
uint16_t queue_size(const queue* const queue);

/**
 * Resize the queue(grows).
 * This is not intend to be used if queue was not created with queue_construct
*/
void queue_resize(queue** queue, uint16_t capacity);

/**
 * Peek the top element
 */
void queue_peek(queue* queue, void* result, char* typename);

/**
 * Iterate over all elements in FIFO order
 */
void queue_for_each(queue* queue, void (*callback)(void* data, void* user_data), void* user_data, char* typename);

#endif
