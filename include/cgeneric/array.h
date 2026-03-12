#ifndef __C_GENERIC_ARRAY_H__
#define __C_GENERIC_ARRAY_H__

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * The array implementation does not provide any safe guards. 
 * So, the caller must be aware that any out of bounds access is undefined behavior
*/

typedef struct array array;

#define ARRAY_CONSTRUCT(_ARRAY_TYPE, _ARRAY_ELEMENTS)(array_construct(_ARRAY_ELEMENTS, sizeof(_ARRAY_TYPE)))
#define ARRAY_INIT(_ARRAY_ARRAY, _ARRAY_TYPE, _ARRAY_ELEMENTS)(array_init(_ARRAY_ARRAY, _ARRAY_ELEMENTS, sizeof(_ARRAY_TYPE)))
#define ARRAY_ADD(_ARRAY_ARRAY, AR_INDEX, AR_VALUE)({typeof(AR_VALUE) tmp = (AR_VALUE); array_add(_ARRAY_ARRAY, AR_INDEX, &tmp);})
#define ARRAY_GET(_ARRAY_ARRAY, AR_INDEX, _ARRAY_TYPE)({_ARRAY_TYPE tmp[1] = {0}; array_get(_ARRAY_ARRAY, AR_INDEX, tmp); *tmp;})
#define ARRAY_AT(_ARRAY_ARRAY, AR_INDEX, _ARRAY_TYPE)({_ARRAY_TYPE* tmp = array_at(_ARRAY_ARRAY, AR_INDEX); tmp;})
#define ARRAY_DESTROY(_ARRAY_ARRAY)array_destroy(&_ARRAY_ARRAY)
#define ARRAY_RESIZE(_ARRAY_ARRAY, _ARRAY_ELEMENTS)array_resize(&_ARRAY_ARRAY, _ARRAY_ELEMENTS);
#define ARRAY_CONTENT(_ARRAY_ARRAY, _ARRAY_TYPE)({_ARRAY_TYPE* tmp = array_content(_ARRAY_ARRAY); tmp;})
#define ARRAY_REMOVE(_ARRAY_ARRAY, AR_INDEX, _ARRAY_TYPE)array_remove_at(_ARRAY_ARRAY, AR_INDEX)
#define ARRAY_CAPACITY(_ARRAY_ARRAY)array_capacity(_ARRAY_ARRAY)
#define ARRAY_FOR_EACH(_ARRAY_ARRAY, _ARRAY_FUNCTION){for (size_t index = 0; index < array_capacity(_ARRAY_ARRAY); index++) _ARRAY_FUNCTION(array_at(_ARRAY_ARRAY, index)); }

array* array_construct(uint16_t capacity, uint16_t size_per_element);
void array_init(array* ar, uint16_t capacity, uint16_t size_per_element);
void* array_at(array* ar, uint16_t index);
void array_get(array* ar, uint16_t index, void* result);
void array_add(array* ar, uint16_t index, const void* data);   
void array_destroy(array** ar);
void array_resize(array** ar, uint16_t capacity);
void* array_content(array* ar);
void array_remove_at(array* ar, uint16_t index);
uint16_t array_capacity(array* ar);

#endif
