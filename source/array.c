#include "cgeneric/array.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct array
{
    uint8_t size_per_element;
    uint16_t capacity;
    char elements[];
};

array* _array_construct(uint16_t capacity, uint16_t size_per_element)
{   
    size_t required_size = sizeof(array) + capacity * size_per_element;
    array* ar = malloc(required_size);
    _array_init(ar, capacity, size_per_element);
    return ar;
}

void _array_init(array *ar, uint16_t capacity, uint16_t size_per_element)
{
    ar->size_per_element = size_per_element;
    ar->capacity = capacity;
    memset(ar->elements, 0, ar->size_per_element * ar->capacity);
}

void* _array_at(array* ar, uint16_t index)
{
    return ar->elements + (index * ar->size_per_element);
}

void _array_get(array* ar, uint16_t index, void* result)
{
    memcpy(result, ar->elements + (index * ar->size_per_element), ar->size_per_element);
}

void _array_add(array* ar, uint16_t index, const void* data)
{
    memcpy(ar->elements + (ar->size_per_element * index), data, ar->size_per_element);
}

void _array_destroy(array** ar)
{   
    if (*ar == NULL)
    {
        return;
    }
    free(*ar);
    *ar = NULL;
}
void _array_resize(array** ar, uint16_t capacity)
{
    array* new_array = _array_construct(capacity, (*ar)->size_per_element);
    memcpy(new_array->elements, (*ar)->elements, (*ar)->size_per_element * capacity);
    _array_destroy(ar);
    *ar = new_array;
}

void* _array_content(array *ar)
{
    return ar->elements;
}

void _array_remove_at(array* ar, uint16_t index)
{
    memset(ar->elements + (index * ar->size_per_element), 0, ar->size_per_element);
}

uint16_t _array_capacity(array* ar)
{
    return ar->capacity;
}