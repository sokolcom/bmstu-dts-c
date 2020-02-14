#ifndef _FILE_PARSING_H_
#define _FILE_PARSING_H_

// Exit codes
#define SUCCESS 0
#define FILE_NOT_EXIST_ERROR 1000
#define EMPTY_FILE_ERROR 1100
#define INVALID_STRING_FIELD_ERROR 2100

// Macroreplacements
#define MAX_STRING_LEN 256


int parse_table(const char *const filename, data_t *const table);
int add_record(data_t *const table);
int delete_records_by_price(data_t *const table, const int *const price);

#endif
