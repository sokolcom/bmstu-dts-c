#ifndef _INPUT_OUTPUT_H_
#define _INPUT_OUTPUT_H_

// Return codes
#define SUCCESS 0
#define INVALID_INT_FIELD_ERROR 2200
#define VALUE_ERROR 2210

// Macroreplacements 
#define SAME_BRAND 0
#define VALID_INPUT 1
#define INVALID_INT_FIELD_ERROR 2200



void welcome();

void clear_stream();
void input_filename(char *filename);
int input_integer_in_range(int *const number, const int left_border, const int right_border);

void print_main_table(const data_t *const table);
void print_key_table(const data_t *const table);
void print_data_by_key(const data_t *const table);
void print_table_by_criteria(const data_t *const table, char *criteria_brand, const int lowest_price, const int highest_price);

#endif
