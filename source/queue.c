#include "cgeneric/queue.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static bool compare_names(const char* left, const char* right);

struct queue
{
    uint8_t size_per_element;
    uint16_t capacity;
    uint16_t top;
    char *typename;
    char elements[];
};

queue* _queue_construct(uint16_t capacity, uint8_t size_per_element, char* typename)
{
    const size_t required_size = sizeof(queue) + capacity * size_per_element;
    queue* q = malloc(required_size);
    _queue_init(q, capacity, size_per_element, typename);
    return q;
}

void _queue_init(queue *queue, uint16_t capacity, uint8_t size_per_element, char* typename)
{
    queue->size_per_element = size_per_element;
    queue->capacity = capacity;
    queue->top = 0;
    queue->typename = typename;
    memset(queue->elements, 0, queue->size_per_element * queue->capacity);    
}

void _queue_destroy(queue** queue)
{
    free(*queue);
    *queue = NULL;
}

bool _queue_push(queue* queue, const void* const data, char* typename)
{
    assert(compare_names(queue->typename, typename) && "Stack typenames mismatch");

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
    assert(compare_names(queue->typename, typename) && "Stack typenames mismatch");
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
    struct queue* new_queue = _queue_construct(capacity, (*queue)->size_per_element, (*queue)->typename);
    memcpy(new_queue->elements, (*queue)->elements, (*queue)->size_per_element * (*queue)->top);
    _queue_destroy(queue);
    *queue = new_queue;
}


void _queue_peek(queue* queue, void* result, char* typename)
{
    assert(queue->top > 0 && "Queue is empty! Nothing to peek!");
    assert(compare_names(queue->typename, typename) && "Stack typenames mismatch");
    memcpy(result, queue->elements, queue->size_per_element);
}


bool compare_names(const char* left, const char* right)
{
    if (left == right)
    {
        // same memory 
        return true;
    }
    // compares character per character, ignoring whitespaces ...
    // "operator*"" vs "operator *" are equal, cause they are handling the same data type.
    while(true)
    {
        if (((*left) && !(*right)) || (!(*left) && (*right)))
        {
            return false;
        }

        if ((*left) == (*right))
        {
            if ((*left) == 0)
            {
                // reached the end of the string
                // strings are equals
                return true;
            }
            left++;
            right++;
            continue;
        }

        if ((*left) == ' ')
        {
            left++;
            continue;
        }
        if ((*right) == ' ')
        {
            right++;
            continue;
        } 

        if ((*left) != (*right))
        {
            return false;
        }
    }
    return true;
}