#ifndef _PROCESSING_H_
#define _PROCESSING_H_

void welcome();

int find_city(char _Cities[][256], char *_Station);

int upload_data(FILE *_File, char _Cities[][256]);
void parse_matrix(FILE *_File, char _Cities[][256], int _Adj_matrix[][100]);
void alg_FloydWarshall(int _Amount, int _Adj[][100], int _Path[][100], int _Dist[][100]);
void print_data(char _Cities[][256], const int _Amount);
void visualize_result(FILE *_Result, int _Amount, char _Cities[][256], int _Adj[][100], int _Path[][100], int _Dist[][100], int _Min_dist, char *_Capital);
void print_valid_cities(int _Amount, char _Cities[][256], int _Dist[][100], int _Min_dist, char *_Capital);

#endif