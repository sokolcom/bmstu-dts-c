#ifndef _DATA_STRUCT_H_
#define _DATA_STRUCT_H_

#define MAX_FIELD_LEN 50


typedef enum
{
    FALSE,
    TRUE
} bool_t;


typedef enum
{
    new = 1,
    used
} condition_t;


// Not new (alreary driven)
typedef struct
{
    int year;
    int mileage;
    int repairs;
    int owners;
} driven_t;


// Vehicle condition
typedef union 
{
    int guarantee;  // new
    driven_t used;  // already owned
 
} variable_t;


// Car info type
typedef struct
{
    char brand[MAX_FIELD_LEN];
    char country[MAX_FIELD_LEN];
    int price;
    char color[MAX_FIELD_LEN];
    condition_t car_type;
    variable_t add_info;
    
} car_t;


// Keys (car price)
typedef struct
{
    int car_table_index;
    int car_price;
} car_key_t;



// All in one data
typedef struct
{
    car_t *main_table;
    car_key_t *key_table;
    int size;
} data_t;

#endif
