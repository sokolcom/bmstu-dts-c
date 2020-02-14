#include <stdlib.h>

#include "../include/hash_function.h"



// Hash function (divisor is variable!)
int mod_hash(const int key, const int divisor)
{
    return abs(key) % divisor;
}
