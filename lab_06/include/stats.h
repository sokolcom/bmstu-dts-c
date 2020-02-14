#ifndef _STATS_H_
#define _STATS_H_

void init_stats(statData_t *const _Stats);
int get_value(FILE *const _IStream, FILE *const _OStream, int *const _Value);
int run_stats(statData_t *const _Stats, const char *const _Filename, const int _Divisor, const int _Colls, const int _Value);
void print_stats(FILE *const _Stream, statData_t *const _Stats);

void refresh_file(const char *const _Filename);
int add_file(const char *const _Filename, const int _Value);
int delete_file(const char *const _Filename, const int _Value);

#endif
