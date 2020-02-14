#include <stdio.h>
#include <time.h>

#include "data_struct.h"
#include "input_output.h"
#include "sorts.h"
#include "file_parsing.h"



int main()
{
    car_t main_table[150];
    car_key_t key_table[150];

    data_t table;
    table.main_table = main_table;
    table.key_table = key_table;
    table.size = 100;

    int menu_key = -1;
    bool_t is_uploaded = FALSE;
    char filename[MAX_STRING_LEN];

    welcome();

    while (menu_key != 0)
    {
        if (scanf("%d", &menu_key) != VALID_INPUT)
        {
            printf("Error: unknown command!\n Please try again.\n\n");
            clear_stream();
            welcome();
            continue;
        }
        
        switch (menu_key)
        {
            // Upload file
            case 1:
                printf("Enter filename to upload: ");
                input_filename(filename);

                int parse_res = parse_table(filename, &table);
                if ((parse_res == FILE_NOT_EXIST_ERROR) || (parse_res == EMPTY_FILE_ERROR))
                {
                    is_uploaded = FALSE;
                    printf("Error!\nFile with given name does not exist or empty!\n\n");
                }
                else
                {
                    is_uploaded = TRUE;
                    printf("File was successfully uploaded!\n\n");
                }

                welcome();
                break;

            // Print original table
            case 2:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                    print_main_table(&table);

                welcome();
                break;

            // Add record
            case 3:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");

                else
                {
                    if (table.size == 150)
                        printf("Error!\nAmount of records at maximum!\n\n");

                    else
                    {
                        int add_result = add_record(&table);

                        if (add_result == INVALID_STRING_FIELD_ERROR)
                            printf("Error!\nInvalid string input!\n\n");
    

                        if (add_result == INVALID_INT_FIELD_ERROR)
                            printf("Error!\nInvalid integer input!\n\n");

                        if (add_result == SUCCESS)
                            printf("Record was successfully added!\n\n");
                    }
                }

                welcome();
                break;

            // Delete records
            case 4:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");

                else
                {
                    int car_price;
                    printf("Enter car price by which delete record: ");
                    if (input_integer_in_range(&car_price, 3000, 5000000) != SUCCESS)
                        printf("Error!\nInvalid car price entered!\n\n");
                    else
                    {
                        int deletions_count = delete_records_by_price(&table, &car_price);
                        printf("%s%d%s\n", "Deleted ", deletions_count, " record(s)\n\n");
                    }
                }

                welcome();
                break;

            // Sort key table with O(nlogn) algorithm
            case 5:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    clock_t start = clock();
                    for (int i = 0; i < 1000; i++)
                        custom_qsort(&table, FALSE, 0, table.size - 1);
                    clock_t end = clock();

                    printf("Time of qsort execution: %lf\n\n", get_seconds(start, end) / 1000);
                }

                welcome();
                break;

            // Sort key table with O(n^2) algorithm
            case 6:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    clock_t start = clock();
                    for (int i = 0; i < 1000; i++)
                        bubble_sort(&table, FALSE);
                    clock_t end = clock();

                    printf("Time of bubble sort execution: %lf\n\n", get_seconds(start, end) / 1000);
                }

                welcome();
                break;

            // Print key table
            case 7:
            if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                    print_key_table(&table);

                welcome();
                break;

            // Printed sorted original with O(nlogn)
            case 8:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    clock_t start = clock();
                    for (int i = 0; i < 1000; i++)
                        custom_qsort(&table, TRUE, 0, table.size - 1);
                    clock_t end = clock();

                    printf("Time of qsort execution: %lf\n\n", get_seconds(start, end) / 1000);
                    print_main_table(&table);

                }

                welcome();
                break;

            // Printed sorted original with O(n^2)
            case 9:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    clock_t start = clock();
                    for (int i = 0; i < 1000; i++)
                        bubble_sort(&table, TRUE);
                    clock_t end = clock();

                    printf("Time of bubble sort execution: %lf\n\n", get_seconds(start, end) / 1000);
                    print_main_table(&table);
                }

                welcome();
                break;

            // Print original table using sorted key table
            case 10:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    clock_t start = clock();
                    for (int i = 0; i < 1000; i++)
                        custom_qsort(&table, FALSE, 0, table.size - 1);
                    clock_t end = clock();

                    printf("Time of qsort execution: %lf\n\n", get_seconds(start, end) / 1000);
                    print_data_by_key(&table);
                }

                welcome();
                break;

            // Print sorting time comparison
            case 11:
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    data_t temp;
                    clock_t start, end;
                    double result_bubble, result_qsort, result_key_bubble, result_key_qsort;

                    // Data bubble sort
                    parse_table(filename, &table);
                    temp = table;  // copy
                    start = clock();
                    for (int i = 0; i < 1000; i++)
                    {
                        bubble_sort(&temp, TRUE);
                        temp = table;
                    }
                    end = clock();
                    result_bubble = get_seconds(start, end) / 1000;

                    // Data table qsort
                    parse_table(filename, &table);
                    temp = table;  // copy
                    start = clock();
                    for (int i = 0; i < 1000; i++)
                    {
                        custom_qsort(&table, TRUE, 0, table.size - 1);
                        temp = table;  // copy
                    }
                    end = clock();
                    result_qsort = get_seconds(start, end) / 1000;

                    // Key bubble sort
                    parse_table(filename, &table);
                    temp = table;  // copy
                    start = clock();
                    for (int i = 0; i < 1000; i++)
                    {
                        bubble_sort(&table, FALSE);
                        temp = table;  // copy
                    }
                    end = clock();
                    result_key_bubble = get_seconds(start, end) / 1000;

                    // key table qsort
                    parse_table(filename, &table);
                    temp = table;  // copy
                    start = clock();
                    for (int i = 0; i < 1000; i++)
                    {
                        custom_qsort(&table, FALSE, 0, table.size - 1);
                        temp = table;  // copy
                    }
                    end = clock();
                    result_key_qsort = get_seconds(start, end) / 1000;

                    printf("Original table bubble sort: %lf seconds\n", result_bubble);
                    printf("Original table qsort: %lf seconds\n", result_qsort);
                    printf("Key table bubble sort: %lf seconds\n", result_key_bubble);
                    printf("Key table qsort: %lf seconds\n\n", result_key_qsort);
                }

                welcome();
                break;

            // Lab task
            case 12:  
                if (is_uploaded == FALSE)
                    printf("Error!\nNo file was uploaded!\nTable is empty!\n\n");
                else
                {
                    char brand_to_find[MAX_STRING_LEN];
                    printf("Enter: car brand: ");
                    scanf("%s", brand_to_find);

                    int lowest;
                    printf("Enter lower limit of cars' price: ");
                    if (scanf("%d", &lowest) != VALID_INPUT)
                        printf("Error!\nInvalid price entered!\n\n");
                    
                    int highest;
                    printf("Enter higher limit of cars' price: ");
                    if (scanf("%d", &highest) != VALID_INPUT)
                        printf("Error!\nInvalid price entered!\n\n");

                    print_table_by_criteria(&table, brand_to_find, lowest, highest);
                }

                welcome();
                break; 

            // Exit program
            case 0:
                continue;

            // Unknown command         
            default:
                printf("Error: unknown command!\nPlease try again.\n\n");
                welcome();
                break;
        }
    }

    printf("See you soon!\n");

    return SUCCESS;
} 
