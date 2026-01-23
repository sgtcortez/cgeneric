#ifndef __C_GENERIC_HASHTABLE_H__
#define __C_GENERIC_HASHTABLE_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct hash_table hash_table;

#define HASH_TABLE_CONSTRUCT(_HASHTABLE_ELEMENT_TYPE, _HASHTABLE_CAPACITY)(_hash_table_construct(_HASHTABLE_CAPACITY, sizeof(_HASHTABLE_ELEMENT_TYPE)))
#define HASH_TABLE_PUT(_HASHTABLE_TABLE, _HASHTABLE_KEY, _HASHTABLE_VALUE, _HASHTABLE_ALLOW_OVERRIDE)({typeof(_HASHTABLE_VALUE) tmp = (_HASHTABLE_VALUE); _hash_table_put(_HASHTABLE_TABLE, _HASHTABLE_KEY, &tmp, _HASHTABLE_ALLOW_OVERRIDE, sizeof(_HASHTABLE_VALUE)); })
#define HASH_TABLE_GET(_HASHTABLE_TABLE, _HASHTABLE_KEY, _HASHTABLE_ELEMENT_TYPE_PTR)(_hash_table_get(_HASHTABLE_TABLE, _HASHTABLE_KEY, _HASHTABLE_ELEMENT_TYPE_PTR, sizeof(*_HASHTABLE_ELEMENT_TYPE_PTR)))
#define HASH_TABLE_DESTROY(_HASHTABLE_TABLE)(_hash_table_destroy(&_HASHTABLE_TABLE))
#define HASH_TABLE_LOAD_FACTOR(_HASHTABLE_TABLE)_hash_table_load_factor(_HASHTABLE_TABLE)

void _hash_table_init(hash_table* hs, uint16_t capacity, uint8_t load_factor, uint8_t element_size);
hash_table* _hash_table_construct(uint16_t capacity, uint8_t element_size);
void _hash_table_destroy(hash_table** hs);
bool _hash_table_put(hash_table* hs, uint32_t key, const void* const value, bool override, uint8_t element_size);
bool _hash_table_get(hash_table* hs, uint32_t key, void* value, uint8_t element_size);
void _hash_table_remove(hash_table* hs, uint32_t key);
float _hash_table_load_factor(const hash_table* const hs);

#endif