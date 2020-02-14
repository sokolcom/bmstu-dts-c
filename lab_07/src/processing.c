#include <stdio.h>
#include <string.h>

#include "../include/define.h"
#include "../include/processing.h"



// Welcome print
void welcome()
{
    printf("This program finds the cities whic are further from given city (capital)\n"
           "than the given distance\n\n");
    printf("Data uploads from the 'data.gv' file\n\n\n");
}


int find_city(char cities[][MAX_LEN_STATION], char *station)
{
    for (int i = 0; i < MAX_LEN; i++)
    {
        if (!strcmp(cities[i], station))
            return i;
    }

    return NOT_FOUND;
}


// Upload data from the file
int upload_data(FILE *src_file, char cities[][MAX_LEN_STATION])
{
    int amount = 0;

    char city_1[MAX_LEN_STATION] = { 0 };
    char city_2[MAX_LEN_STATION] = { 0 };
    char color[100] = { 0 };

    int length;

    fseek(src_file, DATA_OFFSET, 0);
    while (!feof(src_file))
    {
        fscanf(src_file, "%s -- %s [label=\" %d \" color=%s];", city_1, city_2, &length, color);

        if (!strcmp(city_1, "}") || !strcmp(city_2, "}"))
            break;

        if (find_city(cities, city_1) == NOT_FOUND)
        {
            strcpy(cities[amount], city_1);
            amount++;
        }

        if (find_city(cities, city_2) == NOT_FOUND)
        {
            strcpy(cities[amount], city_2);
            amount++;
        }
    }

    return amount;
}


void parse_matrix(FILE *src_file, char cities[][MAX_LEN_STATION], int adj_matrix[][MAX_LEN])
{
    char city_1[MAX_LEN_STATION];
    char city_2[MAX_LEN_STATION];
    char color[100];

    int length;

    fseek(src_file, DATA_OFFSET, 0);
    while (!feof(src_file))
    {
        fscanf(src_file, "%s -- %s [label=\" %d \" color=%s];", city_1, city_2, &length, color);

        if (!strcmp(city_1, "}") || !strcmp(city_2, "}"))
            break;

        adj_matrix[find_city(cities, city_1)][find_city(cities, city_2)] = length;
        adj_matrix[find_city(cities, city_2)][find_city(cities, city_1)] = length;
    }
}


void alg_FloydWarshall(int amount, int adj[][MAX_LEN], int path[][MAX_LEN], int dist[][MAX_LEN])
{
    // Init matricies
    for (int u = 0; u < amount; u++)
    {
        for (int v = 0; v < amount; v++)
        {
            if ((adj[u][v]) || (u == v))
            {
                path[u][v] = v;
                dist[u][v] = adj[u][v];
            }
            else
            {
                path[u][v] = MAX_LEN;
                dist[u][v] = (int)INF;
            }
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < amount; k++)
    {
        for (int u = 0; u < amount; u++)
        {
            if (dist[u][k] != INF)
            {
                for (int v = 0; v < amount; ++v)
                {
                    if (dist[u][v] > dist[u][k] + dist[k][v])
                    {
                        dist[u][v] = dist[u][k] + dist[k][v];
                        path[u][v] = path[u][k];
                    }
                }
            }
        }
    }
}


// Print uploaded data
void print_data(char cities[][MAX_LEN_STATION], const int amount)
{
    printf("Uploaded cities:\n");
    for (int i = 0; i < amount; i++)
    {
        printf("%-18s\n", cities[i]);
    }
}


void visualize_result(FILE* result, int amount, char cities[][MAX_LEN_STATION], int adj[][MAX_LEN], int path[][MAX_LEN], int dist[][MAX_LEN], int min_dist, char *capital)
{
    fprintf(result, "graph G\n{\n"
        "edge[color=\"gray\",fontcolor=\"black\",fontsize=12, len=6, penwidth=3.0];\n"
        "node[color=\"indigo\",fontsize=12];\n\n");

    int used_roads[MAX_LEN][MAX_LEN] = { 0 };
    int city_idx, temp;
    int end_city;

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if ((dist[i][j] > min_dist) && !strcmp(cities[i], capital))
            {
                city_idx = i;
                end_city = j;

                while (city_idx != end_city)
                {   
                    temp = path[city_idx][end_city];

                    if (!used_roads[city_idx][temp])
                    {
                        fprintf(result, "%s -- ", cities[city_idx]);
                        temp = path[city_idx][end_city];

                        fprintf(result, "%s [label=\" %d \" color=green];\n",  cities[temp], adj[city_idx][temp]);

                        used_roads[city_idx][temp] = 1;
                    }

                    city_idx = temp;
                }
            }
        }
    }

    fprintf(result, "}\n");
}


void print_valid_cities(int amount, char cities[][MAX_LEN_STATION], int dist[][MAX_LEN], int min_dist, char *capital)
{
    int city_count = 0;

    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < amount; j++)
        {
            if ((dist[i][j] > min_dist) && !strcmp(cities[i], capital))
            {
                if (!city_count)
                    printf("Valid cities:\n");

                printf("%18s --- %-18s [%dkm]\n", cities[i], cities[j], dist[i][j]);
                city_count++;
            }
        }
    }

    if (city_count == 0)
    {
        printf("No such cities exist!\n");
    }
}
