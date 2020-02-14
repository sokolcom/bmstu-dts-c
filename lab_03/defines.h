#ifndef _DEFINES_H_
#define _DEFINES_H_

// Return codes
#define SUCCESS 0



// Macroreplacements
#define VALID_INPUT 1  // scanf() read successfully 1 variable

#define INPUT_ERROR -1 // indicates of input error
#define MULTIPLICATION_ERROR -2  // indicates invalid multiplication
#define GENERATION_ERROR -3  // indicates error in generation

#define UNREAL_VALUE -1  // in sparse m12n
#define ZERO_MULTIPLICATION -10  // indicate that result is equal [0]

// Type of input/print: vector_row or matrix; std or sparse
typedef enum
{
    vector_input,
    matrix_input,
} type_t;


// Boolean type
typedef enum
{
    FALSE = 0,
    TRUE
} bool_t;

#endif