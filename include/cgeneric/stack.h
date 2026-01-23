#ifndef __C_GENERIC_STACK_H__
#define __C_GENERIC_STACK_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct stack stack;

#define STACK_CONSTRUCT(_STACK_TYPE, _STACK_ELEMENTS)(_stack_construct(_STACK_ELEMENTS, sizeof(_STACK_TYPE)))
#define STACK_INIT(_STACK_STACK, _STACK_TYPE, _STACK_ELEMENTS)(_stack_init(_STACK_STACK, _STACK_ELEMENTS, sizeof(_STACK_TYPE)))
#define STACK_PUSH(_STACK_STACK, STACK_VALUE)({typeof(STACK_VALUE) tmp = (STACK_VALUE); _stack_push(_STACK_STACK, &tmp, sizeof(STACK_VALUE));})
#define STACK_DESTROY(_STACK_STACK)_stack_destroy(&_STACK_STACK)
#define STACK_POP(_STACK_STACK, _STACK_TYPE)({_STACK_TYPE tmp[1] = {0}; _stack_pop(_STACK_STACK, tmp); *tmp; })
#define STACK_SIZE(_STACK_STACK)_stack_size(_STACK_STACK)
#define STACK_RESIZE(_STACK_STACK, _STACK_ELEMENTS)_stack_resize(&_STACK_STACK, _STACK_ELEMENTS);
#define STACK_PEEK(_STACK_STACK, _STACK_TYPE)({_STACK_TYPE tmp[1] = {0}; _stack_peek(_STACK_STACK, tmp); *tmp;}) 


stack* _stack_construct(uint16_t capacity, uint8_t element_size);
void _stack_init(stack* s, uint16_t capacity, uint8_t element_size);
bool _stack_push(stack* s, const void* const data, uint8_t size);
void _stack_destroy(stack** s);
void _stack_pop(stack* s, void* result);
uint16_t _stack_size(const stack* const s);
void _stack_resize(stack** s, uint16_t capacity);
void _stack_peek(stack* s, void* result);

#endif 