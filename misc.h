#ifndef MISC
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int readFile(char* file, int** vertices, char** edges, int* len);
int* getColors(int nbColors, int vertex, char* graph, int* colors, int size);
void greedy(char* edges, int* colors, int size, int* nbCols);
int partialGreedy(int* order, char* edges, int* colors, int size, int start_index);
void copySolution(int* src, int* dst, int size);
void invert(int* array, int step);
#define MISC
#endif
