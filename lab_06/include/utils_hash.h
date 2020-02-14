#ifndef _UTILS_HASH_H_
#define _UTILS_HASH_H_

void init_hash_table(hashTable_t *const _Table, const int _Size);
int add_hash_table(hashTable_t *const _Table, const int value, const int _Collisions, const int _Divisor, int (*hfunc)(const int, const int));
void delete_hash_table(hashTable_t *const _Table, const int _Value);
hashTable_t *upload_hash_table(const char *const _Filename, const int _Divisor, const int _Collisions, int *const _Code);
void print_hash_table(FILE *const _Stream, hashTable_t *const _Table);


#endif
