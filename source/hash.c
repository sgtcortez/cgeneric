#include "cgeneric/hash.h"
#include <stdint.h>

#define DJB2_MAGIC_NUMBER 5381


uint32_t hash_djb2(const char* string)
{
    uint32_t hash = DJB2_MAGIC_NUMBER;
    while (1)
    {
        int c = *string++;
        if (c == 0)
        {
            break;
        }
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}