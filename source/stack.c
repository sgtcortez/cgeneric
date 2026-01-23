#include "cgeneric/stack.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct stack
{
    uint8_t size_per_element;
    uint16_t capacity;
    uint16_t top;
    char elements[];
};

stack* _stack_construct(uint16_t capacity, uint8_t size_per_element)
{
    const size_t required_size = sizeof(stack) + capacity * size_per_element;
    stack* q = malloc(required_size);
    _stack_init(q, capacity, size_per_element);
    return q;
}

void _stack_init(stack *stack, uint16_t capacity, uint8_t size_per_element)
{
    stack->size_per_element = size_per_element;
    stack->capacity = capacity;
    stack->top = 0;
    memset(stack->elements, 0, stack->size_per_element * stack->capacity);    
}

void _stack_destroy(stack** stack)
{
    free(*stack);
    *stack = NULL;
}

bool _stack_push(stack* stack, const void* const data, uint8_t size)
{
    assert(size == stack->size_per_element);

    if (stack->top == stack->capacity)
    {
        return false;
    }
    memcpy(stack->elements + (stack->size_per_element * stack->top) , data,  stack->size_per_element );    
    stack->top++;
    return true;
}

void _stack_pop(stack* stack, void* result)
{
    assert(stack->top > 0 && "Stack is empty! Nothing to Pop!");
    stack->top--;
    memcpy(result, stack->elements + (stack->top * stack->size_per_element), stack->size_per_element);
}

uint16_t _stack_size(const stack* const stack)
{
    return stack->top;
}

void _stack_resize(stack** stack, uint16_t capacity)
{   
    struct stack* new_stack = _stack_construct(capacity, (*stack)->size_per_element);
    memcpy(new_stack->elements, (*stack)->elements, (*stack)->size_per_element * (*stack)->top);
    _stack_destroy(stack);
    *stack = new_stack;
}


void _stack_peek(stack* stack, void* result)
{
    assert(stack->top > 0 && "Stack is empty! Nothing to peek!");
    memcpy(result, stack->elements + ((stack->top - 1) * stack->size_per_element), stack->size_per_element);
}