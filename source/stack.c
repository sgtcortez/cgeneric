#include "cgeneric/stack.h"

#include "cgeneric/hash.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct stack
{
    uint16_t size_per_element;
    uint16_t capacity;
    uint16_t top;
    uint32_t hash;
    char elements[];
};

stack* _stack_construct(uint16_t capacity, uint16_t size_per_element, char *typename)
{
    const size_t required_size = sizeof(stack) + capacity * size_per_element;
    stack* q = malloc(required_size);
    _stack_init(q, capacity, size_per_element, typename);
    return q;
}

void _stack_init(stack *stack, uint16_t capacity, uint16_t size_per_element, char* typename)
{
    stack->size_per_element = size_per_element;
    stack->capacity = capacity;
    stack->top = 0;
    stack->hash = hash_djb2(typename);
    memset(stack->elements, 0, stack->size_per_element * stack->capacity);    
}

void _stack_destroy(stack** stack)
{
    free(*stack);
    *stack = NULL;
}

bool _stack_push(stack* stack, const void* const data, const char* typename)
{
    assert(stack->hash == hash_djb2(typename) && "Stack typenames mismatch");
    if (stack->top == stack->capacity)
    {
        return false;
    }
    memcpy(stack->elements + (stack->size_per_element * stack->top) , data,  stack->size_per_element );    
    stack->top++;
    return true;
}

void _stack_pop(stack* stack, void* result, const char* typename)
{
    assert(stack->top > 0 && "Stack is empty! Nothing to Pop!");
    assert(stack->hash == hash_djb2(typename) && "Stack typenames mismatch");
    stack->top--;
    memcpy(result, stack->elements + (stack->top * stack->size_per_element), stack->size_per_element);
}

uint16_t _stack_size(const stack* const stack)
{
    return stack->top;
}

void _stack_resize(stack** stack, uint16_t capacity)
{   
    struct stack* new_stack = _stack_construct(capacity, (*stack)->size_per_element, NULL);
    new_stack->hash = (*stack)->hash;
    memcpy(new_stack->elements, (*stack)->elements, (*stack)->size_per_element * capacity);
    _stack_destroy(stack);
    *stack = new_stack;
}


void _stack_peek(stack* stack, void* result, const char* typename)
{
    assert(stack->top > 0 && "Stack is empty! Nothing to peek!");
    assert(stack->hash == hash_djb2(typename) && "Stack typenames mismatch");
    memcpy(result, stack->elements + ((stack->top - 1) * stack->size_per_element), stack->size_per_element);
}

void _stack_for_each(stack* stack, void (*callback)(void* data, void* user_data), void* user_data, const char* typename)
{
    assert(stack->hash == hash_djb2(typename) && "Stack typenames mismatch");
    for (uint16_t i = stack->top; i > 0; i--)
    {
        callback(stack->elements + ((i - 1) * stack->size_per_element), user_data);
    }
}
