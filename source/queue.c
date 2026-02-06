#include "cgeneric/queue.h"
#include "cgeneric/hash.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct queue
{
    uint16_t size_per_element;
    uint16_t capacity;
    uint16_t top;
    uint32_t hash;
    char elements[];
};

queue* _queue_construct(uint16_t capacity, uint16_t size_per_element, char* typename)
{
    const size_t required_size = sizeof(queue) + capacity * size_per_element;
    queue* q = malloc(required_size);
    _queue_init(q, capacity, size_per_element, typename);
    return q;
}

void _queue_init(queue *queue, uint16_t capacity, uint16_t size_per_element, char* typename)
{
    queue->size_per_element = size_per_element;
    queue->capacity = capacity;
    queue->top = 0;
    queue->hash = hash_djb2(typename);
    memset(queue->elements, 0, queue->size_per_element * queue->capacity);    
}

void _queue_destroy(queue** queue)
{
    free(*queue);
    *queue = NULL;
}

bool _queue_push(queue* queue, const void* const data, char* typename)
{
    assert(queue->hash == hash_djb2(typename) && "Queue typenames mismatch");

    if (queue->top == queue->capacity)
    {
        return false;
    }
    memcpy(queue->elements + (queue->size_per_element * queue->top) , data,  queue->size_per_element );    
    queue->top++;
    return true;
}

void _queue_pop(queue* queue, void* result, char* typename)
{
    assert(queue->top > 0 && "Queue is empty! Nothing to Pop!");
    assert(queue->hash == hash_djb2(typename) && "Queue typenames mismatch");
    memcpy(result, queue->elements, queue->size_per_element);
    queue->top--;
    if (queue->top > 0)
    {
        memmove(queue->elements, queue->elements + queue->size_per_element, queue->top * queue->size_per_element);
    }
}

uint16_t _queue_size(const queue* const queue)
{
    return queue->top;
}

void _queue_resize(queue** queue, uint16_t capacity)
{   
    struct queue* new_queue = _queue_construct(capacity, (*queue)->size_per_element, NULL);
    new_queue->hash = (*queue)->hash;
    memcpy(new_queue->elements, (*queue)->elements, (*queue)->size_per_element * capacity);
    _queue_destroy(queue);
    *queue = new_queue;
}


void _queue_peek(queue* queue, void* result, char* typename)
{
    assert(queue->top > 0 && "Queue is empty! Nothing to peek!");
    assert(queue->hash == hash_djb2(typename) && "Queue typenames mismatch");
    memcpy(result, queue->elements, queue->size_per_element);
}

void _queue_for_each(queue* queue, void (*callback)(void* data, void* user_data), void* user_data, char* typename)
{
    assert(queue->hash == hash_djb2(typename) && "Queue typenames mismatch");
    for (uint16_t i = 0; i < queue->top; i++)
    {
        callback(queue->elements + (i * queue->size_per_element), user_data);
    }
}
