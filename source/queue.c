#include "cgeneric/queue.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct queue
{
    uint8_t size_per_element;
    uint16_t capacity;
    uint16_t top;
    char elements[];
};

queue* _queue_construct(uint16_t capacity, uint8_t size_per_element)
{
    const size_t required_size = sizeof(queue) + capacity * size_per_element;
    queue* q = malloc(required_size);
    _queue_init(q, capacity, size_per_element);
    return q;
}

void _queue_init(queue *queue, uint16_t capacity, uint8_t size_per_element)
{
    queue->size_per_element = size_per_element;
    queue->capacity = capacity;
    queue->top = 0;
    memset(queue->elements, 0, queue->size_per_element * queue->capacity);    
}

void _queue_destroy(queue** queue)
{
    free(*queue);
    *queue = NULL;
}

bool _queue_push(queue* queue, const void* const data, uint8_t size)
{
    assert(size == queue->size_per_element);

    if (queue->top == queue->capacity)
    {
        return false;
    }
    memcpy(queue->elements + (queue->size_per_element * queue->top) , data,  queue->size_per_element );    
    queue->top++;
    return true;
}

void _queue_pop(queue* queue, void* result)
{
    assert(queue->top > 0 && "Queue is empty! Nothing to Pop!");
    memcpy(result, queue->elements, queue->size_per_element);
    queue->top--;
    memmove(queue->elements, queue->elements + 1, queue->top * queue->size_per_element);
}

uint16_t _queue_size(const queue* const queue)
{
    return queue->top;
}

void _queue_resize(queue** queue, uint16_t capacity)
{   
    struct queue* new_queue = _queue_construct(capacity, (*queue)->size_per_element);
    memcpy(new_queue->elements, (*queue)->elements, (*queue)->size_per_element * (*queue)->top);
    _queue_destroy(queue);
    *queue = new_queue;
}


void _queue_peek(queue* queue, void* result)
{
    assert(queue->top > 0 && "Queue is empty! Nothing to peek!");
    memcpy(result, queue->elements, queue->size_per_element);
}