#ifndef GRIDLIS_H
#define GRIDLIS_H

#include "grid.h"

typedef struct GridList {
    Grid* grid;
    struct GridList* next;
} GridList;

void addGridToList(GridList** list, Grid* grid);
Grid* getPreviousGrid(GridList** list);
void clearGridList(GridList** list);

#endif
