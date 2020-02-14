#include <time.h>

#include "data_struct.h"
#include "sorts.h"



// Swap data in table
void swap_data(data_t *const table, const int i, const int j)
{
    car_t temp = table->main_table[i];
    table->main_table[i] = table->main_table[j];
    table->main_table[j] = temp;  
}


// Swap keys
void swap_keys(data_t *const table, const int i, const int j)
{
    car_key_t temp = table->key_table[i];
    table->key_table[i] = table->key_table[j];
    table->key_table[j] = temp;
}


// Bubble sort, O(n^2)
// bool_t sort_data indicates to sort data (TRUE) or keys (FALSE)
void bubble_sort(data_t *const table, const bool_t sort_data)
{
    // Sort DATA
    if (sort_data == TRUE)
    {
        for (int record = 0; record < table->size; record++)
            for (int offset = 0; offset < table->size - 1; offset++)
                if (table->main_table[offset].price < table->main_table[offset + 1].price)
                {
                    swap_data(table, offset, offset + 1);
                }
    }

    // Sort KEYS
    if (sort_data == FALSE)
    {
        for (int record = 0; record < table->size; record++)
            for (int offset =  0; offset < table->size; offset++)
                if (table->key_table[offset].car_price < table->key_table[offset + 1].car_price)
                {
                    swap_keys(table, offset, offset + 1);
                }
    }
}


// qsort, O(n*logn)
// bool_t sort_data indicates to sort data (TRUE) or keys (FALSE)
void custom_qsort(data_t *const table, const bool_t sort_data, const int first, const int last)
{
    if (sort_data == TRUE)
    {
        if (first < last)
        {
            int pivot = (first + last) / 2;
            car_t pivot_record = table->main_table[pivot];

            int f = first;
            int l = last;

            while (f <= l)
            {
                car_t first_record = table->main_table[f];
                while ((first_record.price > pivot_record.price) && (f <= last))
                    first_record = table->main_table[++f];

                car_t last_record = table->main_table[l];
                while ((last_record.price < pivot_record.price) && (l >= first))
                    last_record = table->main_table[--l];

                if (f <= l)
                {
                    table->main_table[f] = last_record;
                    table->main_table[l] = first_record;
                    f++;
                    l--;
                }
            }

            custom_qsort(table, TRUE, first, l);
            custom_qsort(table, TRUE, f, last);
        }
    }

    if (sort_data == FALSE)
    {
        if (first < last)
        {
            int pivot = (first + last) / 2;
            car_key_t pivot_record = table->key_table[pivot];

            int f = first;
            int l = last;

            while (f <= l)
            {
                car_key_t first_record = table->key_table[f];
                while ((first_record.car_price > pivot_record.car_price) && (f <= last))
                    first_record = table->key_table[++f];

                car_key_t last_record = table->key_table[l];
                while ((last_record.car_price < pivot_record.car_price) && (l >= first))
                    last_record = table->key_table[--l];

                if (f <= l)
                {
                    table->key_table[f++] = last_record;
                    table->key_table[l--] = first_record;
                }
            }

            custom_qsort(table, FALSE, first, l);
            custom_qsort(table, FALSE, f, last);
        }
    }
}


// ticks to seconds
double get_seconds(clock_t start, clock_t finish)
{
    return (double)(finish - start) / CLOCKS_PER_SEC;
}
