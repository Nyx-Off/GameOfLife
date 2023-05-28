#ifndef GRIDLIS_H
#define GRIDLIS_H
#define MAX_LIST_SIZE 100


#include "grid.h"

typedef struct GridList {
    struct GridList* next;
    struct GridList* prev;
    Grid* grid;
    int count;
} GridList;

void addGridToList(GridList** list, Grid* grid);
Grid* getPreviousGrid(GridList** list);
Grid* getNextGrid(GridList** list);  
void clearGridList(GridList** list);

#endif
