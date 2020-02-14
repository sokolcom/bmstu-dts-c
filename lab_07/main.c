#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "include/define.h"
#include "include/processing.h"

// Processor ticks' counter
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}


int main()
{
    uint64_t start, end;
    welcome();

    int adjacency_matrix[MAX_LEN][MAX_LEN];
    int path_matrix[MAX_LEN][MAX_LEN];
    int distance_matrix[MAX_LEN][MAX_LEN];

    char cities[MAX_LEN][MAX_LEN_STATION];

    char capital[MAX_LEN_STATION];
    int min_dist;

    FILE *src_file = fopen(FILENAME, "r");
    if (!src_file)
    {
        printf("Error!\nFailed to upload data - file not found!\n");
        return UPLOAD_ERROR;
    }
    if (feof(src_file))
    {
        printf("Error!\nFailed to upload data - empty file!\n");
        return UPLOAD_ERROR;
    }
    rewind(src_file);

    int amount = upload_data(src_file, cities);
    print_data(cities, amount);

    printf("Enter the capital:\n");
    scanf("%s", capital);
    if (find_city(cities, capital) == NOT_FOUND)
    {
        printf("Error!\nUploaded data doesn't contain entered city!\n");
        return CAPITAL_ERROR;
    }

    printf("Entere minimum distance from the capital (integer):\n");
    int code = scanf("%d", &min_dist);
    if ((!code) || (min_dist <= 0))
    {
        printf("Error!\nInvalid distance entered!\n");
        return CAPITAL_ERROR;
    }

    FILE *res_file = fopen(RESULT, "w");

    parse_matrix(src_file, cities, adjacency_matrix);
    start = tick();
    alg_FloydWarshall(amount, adjacency_matrix, path_matrix, distance_matrix);
    visualize_result(res_file, amount, cities, adjacency_matrix, path_matrix, distance_matrix, min_dist, capital);
    end = tick();
    print_valid_cities(amount, cities, distance_matrix, min_dist, capital);

    printf("\nPROCESSOR TICKS: %" PRIu64 "\n", end - start);

    fclose(src_file);
    fclose(res_file);

    return SUCCESS;
}
