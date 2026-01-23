#include "cgeneric/hashtable.h"
#include "cgeneric/array.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

static uint16_t get_index(uint32_t key, uint16_t capacity);
static int32_t find_best_fit(uint16_t start_index, uint32_t key,  array* array, bool allow_override);

typedef enum slot 
{
    SLOT_EMPTY = 0,
    SLOT_OCCUPIED = 1,
} slot;

typedef struct entry
{
    slot slot_type;
    uint32_t key;
    char value[];
} entry;


struct hash_table
{
    //uint8_t load_factor;
    uint8_t size_per_element;
    uint16_t capacity;
    uint16_t size;
    array* elements;    
};

hash_table* _hash_table_construct(uint16_t capacity, uint8_t element_size)
{
    hash_table* hs = malloc(sizeof(hash_table));
    hs->capacity = capacity;
    hs->size_per_element = element_size;
    hs->size = 0;
    hs->elements = _array_construct(capacity, sizeof(entry) + element_size);
    return hs;
}

bool _hash_table_put(hash_table* hs, uint32_t key, const void* const value, bool override, uint8_t element_size)
{
    assert(hs->size_per_element == element_size || "Elements size mismatch!");    
    if (hs->capacity == hs->size)
    {
        return false;
    }
    int32_t real_index = find_best_fit(get_index(key, hs->capacity), key, hs->elements, override);
    if (real_index == -1)
    {
        // maybe to many collissions, or there is already an entry for this key in this index ... or hashmap is almost full ...
        return false;
    }
    entry* ent = _array_at(hs->elements, real_index);
    ent->key = key;
    ent->slot_type = SLOT_OCCUPIED;
    strncpy(ent->value, value, hs->size_per_element);
    hs->size++;
    return true;
}

bool _hash_table_get(hash_table* hs, uint32_t key, void* value, uint8_t element_size)
{
    assert(hs->size > 0 && "Hashtable is empty!");
    assert(hs->size_per_element == element_size && "Elements size mismatch!");
    uint16_t index = get_index(key, hs->capacity);
    int32_t real_index = find_best_fit(index, key, hs->elements, true);
    if (real_index == -1)
    {
        memset(value, 0, hs->size_per_element);
        return false;
    }
    entry* en = _array_at(hs->elements, get_index(key, hs->capacity));
    if (en->slot_type == SLOT_EMPTY)
    {
        memset(value, 0, hs->size_per_element);
        return false;
    }
    memcpy(value, en->value, hs->size_per_element);
    return true;
}

float _hash_table_load_factor(const hash_table* const hs)
{
    return 1.0 * hs->size / hs->capacity;
}


static uint16_t get_index(uint32_t key, uint16_t capacity)
{
    // TODO: Improve this algorithm
    return key % capacity;
}

static int32_t find_best_fit(uint16_t start_index, uint32_t key, array* array, bool allow_override)
{
    int retries = 3;
    while (retries-- > 0)
    {
        entry* e = _array_at(array, start_index);
        if (e->slot_type == SLOT_EMPTY)
        {
            return start_index;
        }
        if (e->key == key)
        {
            return allow_override ? start_index : -1;
        }
        start_index = ARRAY_CAPACITY(array) > start_index ? start_index + 1 : 0;
    }
    return -1;
}