#ifndef _SORTS_H_
#define _SORTS_H_

void bubble_sort(data_t *const table, const bool_t sort_data);
void custom_qsort(data_t *const table, const bool_t sort_data, const int first, const int last);

double get_seconds(clock_t start, clock_t finish);

#endif
