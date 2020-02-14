#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "data_struct.h"
#include "file_parsing.h"
#include "input_output.h"


// Add field
char *get_csv_field(char *const line, int field_index)
{
    char *token;
    for (token = strtok(line, ";"); token && *token; token = strtok(NULL, ";\n"))
    {
        if (!--field_index)
            return token;
    }

    return NULL;
}


// Parse CSV-table
int parse_table(const char *const filename, data_t *const table)
{
    FILE *table_file = fopen(filename, "r");

    if (!table_file)
    {
        return FILE_NOT_EXIST_ERROR;
    }

    if (fgetc(table_file) == EOF)
    {
        return EMPTY_FILE_ERROR;
    }

    fseek(table_file, 0, SEEK_SET);

    for (int record = 0; record < table->size; record++)
    {
        char line[MAX_STRING_LEN];
        fgets(line, MAX_STRING_LEN, table_file);

        char temp[MAX_STRING_LEN];
        strcpy(temp, line);

        strcpy(table->main_table[record].brand, get_csv_field(temp, 1));
        strcpy(temp, line);
        strcpy(table->main_table[record].country, get_csv_field(temp, 2));
        strcpy(temp, line);
        table->main_table[record].price = atoi(get_csv_field(temp, 3));
        strcpy(temp, line);
        strcpy(table->main_table[record].color, get_csv_field(temp, 4));
        strcpy(temp, line);
        table->main_table[record].car_type = atoi(get_csv_field(temp, 5));

        // For the key table
        table->key_table[record].car_table_index = record;
        strcpy(temp, line);
        table->key_table[record].car_price = atoi(get_csv_field(temp, 3));

        // New car
        if (table->main_table[record].car_type == new)
        {
            strcpy(temp, line);
            table->main_table[record].add_info.guarantee = atoi(get_csv_field(temp, 6));
        }

        // Already driven car
        if (table->main_table[record].car_type == used)
        {
            strcpy(temp, line);
            table->main_table[record].add_info.used.year = atoi(get_csv_field(temp, 6));
            strcpy(temp, line);
            table->main_table[record].add_info.used.mileage = atoi(get_csv_field(temp, 7));
            strcpy(temp, line);
            table->main_table[record].add_info.used.repairs = atoi(get_csv_field(temp, 8));
            strcpy(temp, line);
            table->main_table[record].add_info.used.owners = atoi(get_csv_field(temp, 9));
        }
    }

    fclose(table_file);

    return SUCCESS;
}


// Add another record to the table
int add_record(data_t *const table)
{
    car_t new_record;

    printf(
           "\nNOTE!\n"
           "* Instead of typing space (' ') use symbol '_'\n"
           "* Use number and latin letters to enter data\n\n");

    printf("Enter car brand: ");
    if (scanf("%s", new_record.brand) != VALID_INPUT)
    {
        return INVALID_STRING_FIELD_ERROR;
    }

    printf("Enter producing country: ");
    if (scanf("%s", new_record.country) != VALID_INPUT)
    {
        return INVALID_STRING_FIELD_ERROR;
    }

    printf("Enter car price (from 3 000 to 5 000 000): $");
    if (input_integer_in_range(&new_record.price, 3000, 5000000) != SUCCESS)
    {
        return INVALID_INT_FIELD_ERROR;
    }

    printf("Enter car's color: ");
    if (scanf("%s", new_record.color) != VALID_INPUT)
    {
        return INVALID_STRING_FIELD_ERROR;
    }

    printf("Enter type of the car (1 - new, 2 - used): ");
    int condition;
    if (input_integer_in_range(&condition, 1, 2) != SUCCESS)
    {
        return INVALID_INT_FIELD_ERROR;
    }
    new_record.car_type = condition;


    // New car
    if (new_record.car_type == new)
    {
        printf("How many guarantee year does it have (from 1 to 5):");
        if (input_integer_in_range(&new_record.add_info.guarantee, 1, 5) != SUCCESS)
        {
            return INVALID_INT_FIELD_ERROR;
        }
    }

    // Used car
    if (new_record.car_type == used)
    {
        printf("Year of construction (from 1960 to 2019): ");
        if (input_integer_in_range(&new_record.add_info.used.year, 1950, 2019) != SUCCESS)
        {
            return INVALID_INT_FIELD_ERROR;
        }

        printf("Enter car's mileage in km (from 100 to 1 000 000):");
        if (input_integer_in_range(&new_record.add_info.used.mileage, 100, 1000000) != SUCCESS)
        {
            return INVALID_INT_FIELD_ERROR;
        }

        printf("Enter how many repairs has the car (from 0 to 20):");
        if (input_integer_in_range(&new_record.add_info.used.repairs, 0, 20) != SUCCESS)
        {
            return INVALID_INT_FIELD_ERROR;
        }

        printf("Enter how many owners has had the car (from 1 to 10):");
        if (input_integer_in_range(&new_record.add_info.used.owners, 1, 10) != SUCCESS)
        {
            return INVALID_INT_FIELD_ERROR;
        }
    }

    table->main_table[table->size] = new_record;
    table->key_table[table->size].car_table_index = table->size;
    table->key_table[table->size].car_price = new_record.price;

    table->size++;

    return SUCCESS;
}


// Delete record with given car price
int delete_records_by_price(data_t *const table, const int *const price)
{
    int deletions_count = 0;

    for (int record = 0; record < table->size; record++)
    {
        if (table->main_table[record].price == *price)
        {
            for (int record_offset = record; record_offset < table->size - 1; record_offset++)
            {
                table->main_table[record_offset] = table->main_table[record_offset + 1];
                table->key_table[record_offset] = table->key_table[record_offset + 1];
            }

            record--;
            table->size--;
            deletions_count++;
        }
    }

    return deletions_count;
}
