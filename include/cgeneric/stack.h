#ifndef __C_GENERIC_STACK_H__
#define __C_GENERIC_STACK_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct stack stack;

#define STACK_CONSTRUCT(_STACK_TYPE, _STACK_ELEMENTS)(stack_construct(_STACK_ELEMENTS, sizeof(_STACK_TYPE), #_STACK_TYPE))
#define STACK_INIT(_STACK_STACK, _STACK_TYPE, _STACK_ELEMENTS)(stack_init(_STACK_STACK, _STACK_ELEMENTS, sizeof(_STACK_TYPE), #_STACK_TYPE))
#define STACK_PUSH(_STACK_STACK, _STACK_TYPE, STACK_VALUE)({typeof(STACK_VALUE) tmp = (STACK_VALUE); stack_push(_STACK_STACK, &tmp, #_STACK_TYPE );})
#define STACK_DESTROY(_STACK_STACK)stack_destroy(&_STACK_STACK)
#define STACK_POP(_STACK_STACK, _STACK_TYPE)({_STACK_TYPE tmp[1] = {0}; stack_pop(_STACK_STACK, tmp, #_STACK_TYPE); *tmp;})
#define STACK_SIZE(_STACK_STACK)stack_size(_STACK_STACK)
#define STACK_RESIZE(_STACK_STACK, _STACK_ELEMENTS)stack_resize(&_STACK_STACK, _STACK_ELEMENTS);
#define STACK_PEEK(_STACK_STACK, _STACK_TYPE)({_STACK_TYPE tmp[1] = {0}; stack_peek(_STACK_STACK, tmp, #_STACK_TYPE); *tmp;}) 
#define STACK_FOREACH(_STACK_STACK, _STACK_TYPE, _CALLBACK, _USER_DATA)({stack_for_each(_STACK_STACK, _CALLBACK, _USER_DATA, #_STACK_TYPE);})


stack* stack_construct(uint16_t capacity, uint16_t element_size, char* typename);
void stack_init(stack* s, uint16_t capacity, uint16_t element_size, char* typename);
bool stack_push(stack* s, const void* const data, const char* typename);
void stack_destroy(stack** s);
void stack_pop(stack* s, void* result, const char* typename);
uint16_t stack_size(const stack* const s);
void stack_resize(stack** s, uint16_t capacity);
void stack_peek(stack* s, void* result, const char* typename);
void stack_for_each(stack* s, void (*callback)(void* data, void* user_data), void* user_data, const char* typename);

#endif 
