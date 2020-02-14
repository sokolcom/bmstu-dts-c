#include <stdio.h>
#include <string.h>

#include "data_struct.h"
#include "input_output.h"



// Info for user
void welcome()
{
    printf("%s", "CARS & SORTS v1.0\n\n");
    printf("%s",
           "This program allows to:\n"
           "\t* compare two different sorting algorithms with\n"
           "\t  O(nlogn) and O(n^2) complexities;\n"
           "\t* print sorted key table while original table is shuffled\n"
           "\t* print sorted original table;\n"
           "\t* print sorted original table using sorted key table\n"
           "\t* print results of applying different sorting algorithms.\n"
           "\t* append record entered by user to the end of the table;\n"
           "\t* delete record from the table by given car price;\n\n");
    printf("%s", 
           "Choose option by entering its key:\n");
    printf("%s",
           "\t1. Upload table from CSV-file.\n"
           "\t2. Print uploaded table.\n"
           "\t3. Add record to the table.\n"
           "\t4. Delete records in the table by car price.\n"
           "\t5. Sort key table using algorithm with O(nlogn) complexity.\n"
           "\t6. Sort key table using algorithm with O(n^2) complexity.\n"
           "\t7. Print key table.\n"
           "\t8. Print sorted by car price original table using algorith with O(nlogn) complexity.\n"
           "\t9. Print sorted by car price original table using algorith with O(n^2) complexity.\n"
           "\t10. Print original table using sorted key table.\n"
           "\t11. Print sorting time comparison of usage sorting alorithms with complexities\n"
           "\t    O(n^2) and O(nlogn) and sorting time comparison of trivial sorting and \n"
           "\t    key array sorting.\n"
           "\t12. Print list of used cars with specified brand, one previous owner,\n"
           "\t    0 repairs and in given price range.\n"
           "\t0. Exit program.\n\n");
}


// Print full table (database)
void print_main_table(const data_t *const table)
{
    if (table->size == 0)
    {
        printf("WARNING!\nTable is empty!\n\n");
        return;
    }
    
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("|       BRAND       |    COUNTRY   | PRICE ($$) |  COLOR  | TYPE | GUARANTEE | YEAR | MILEAGE | REPAIRS | # OWNERS |\n");
    printf("|-------------------|--------------|------------|---------|------|-----------|------|---------|---------|----------|\n");

    for (int record = 0; record < table->size; record++)
    {
        printf("|%19s|%14s|%12d|%9s|",
               table->main_table[record].brand,
               table->main_table[record].country,
               table->main_table[record].price,
               table->main_table[record].color);

        // new car
        if (table->main_table[record].car_type == new)
        {
            printf("%s|%11d|      |         |         |          |\n",
                   "  NEW ",
                   table->main_table[record].add_info.guarantee);
        }

        // already used car
        if (table->main_table[record].car_type == used)
        {
            printf("%s|           |%6d|%9d|%9d|%10d|\n",
                   " USED ",
                   table->main_table[record].add_info.used.year,
                   table->main_table[record].add_info.used.mileage,
                   table->main_table[record].add_info.used.repairs,
                   table->main_table[record].add_info.used.owners);
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------\n\n");
}


// Print key table
void print_key_table(const data_t *const table)
{
    if (table->size == 0)
    {
        printf("WARNING!\nTable is empty!\n\n");
        return;
    }

    printf("----------------------\n");
    printf("| INDEX |    KEY     |\n");
    printf("|-------|------------|\n");
    for (int record = 0; record < table->size; record++)
    {
        printf("|%7d|%12d|\n",
               table->key_table[record].car_table_index,
               table->key_table[record].car_price);
    }

    printf("----------------------\n\n");
}


void print_data_by_key(const data_t *const table)
{
    if (table->size == 0)
    {
        printf("WARNING!\nTable is empty!\n\n");
        return;
    }

    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("|       BRAND       |    COUNTRY   | PRICE ($$) |  COLOR  | TYPE | GUARANTEE | YEAR | MILEAGE | REPAIRS | # OWNERS |\n");
    printf("|-------------------|--------------|------------|---------|------|-----------|------|---------|---------|----------|\n");

    for (int record = 0; record < table->size; record++)
    {
        printf("|%19s|%14s|%12d|%9s|",
               table->main_table[table->key_table[record].car_table_index].brand,
               table->main_table[table->key_table[record].car_table_index].country,
               table->main_table[table->key_table[record].car_table_index].price,
               table->main_table[table->key_table[record].car_table_index].color);

        // new car
        if (table->main_table[table->key_table[record].car_table_index].car_type == new)
        {
            printf("%s|%11d|      |         |         |          |\n",
                   "  NEW ",
                   table->main_table[table->key_table[record].car_table_index].add_info.guarantee);
        }

        // Already driven
        if (table->main_table[table->key_table[record].car_table_index].car_type == used)
        {
            printf("%s|           |%6d|%9d|%9d|%10d|\n",
                   " USED ",
                   table->main_table[table->key_table[record].car_table_index].add_info.used.year,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.mileage,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.repairs,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.owners);
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------\n\n");
}


// <lab task>
void print_table_by_criteria(const data_t *const table, char *criteria_brand, const int lowest_price, const int highest_price)
{   
    if (table->size == 0)
    {
        printf("WARNING!\nTable is empty!\n\n");
        return;
    }

    int cars_count = 0;

    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("|       BRAND       |    COUNTRY   | PRICE ($$) |  COLOR  | TYPE | GUARANTEE | YEAR | MILEAGE | REPAIRS | # OWNERS |\n");
    printf("|-------------------|--------------|------------|---------|------|-----------|------|---------|---------|----------|\n");


    for (int record = 0; record < table->size; record++)
    {
        if ((table->main_table[record].car_type == used) &&
            (table->main_table[record].add_info.used.owners == 1) &&
            (table->main_table[record].add_info.used.repairs == 0) &&
            (table->main_table[record].price >= lowest_price) &&
            (table->main_table[record].price <= highest_price) &&
            (strcmp(table->main_table[record].brand, criteria_brand) == SAME_BRAND))
        {
            printf("|%19s|%14s|%12d|%9s|",
               table->main_table[record].brand,
               table->main_table[record].country,
               table->main_table[record].price,
               table->main_table[record].color);

            printf("%s|           |%6d|%9d|%9d|%10d|\n",
                   " USED ",
                   table->main_table[table->key_table[record].car_table_index].add_info.used.year,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.mileage,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.repairs,
                   table->main_table[table->key_table[record].car_table_index].add_info.used.owners);
            
            cars_count++;
        }
    }

    printf("--------------------------------------------------------------------------------------------------------------------\n\n");
    
    if (!cars_count)
        printf("NO CARS MATCH THE SPECIFIED CRITERIA!\n");
}


// Remove trash from the input stream
void clear_stream()
{
    char symbol;
    while (((symbol = getchar()) != '\n') && (symbol != EOF));
}


// Inputing filename to open
void input_filename(char *filename)
{
    scanf("%s", filename);
}


// Enter integer in the given range 
int input_integer_in_range(int *const number, const int left_border, const int right_border)
{
    if (scanf("%d", number) != VALID_INPUT)
    {
        clear_stream();
        return INVALID_INT_FIELD_ERROR;
    }

    if (*number < left_border || *number > right_border)
    {
        clear_stream();
        return VALUE_ERROR;
    }

    return SUCCESS;
}
