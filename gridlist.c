#include <stdlib.h>
#include "gridlist.h"

void addGridToList(GridList** list, Grid* grid) {
    GridList* newList = (GridList*) malloc(sizeof(GridList));
    newList->grid = grid;
    newList->next = *list;
    *list = newList;
}

Grid* getPreviousGrid(GridList** list) {
    if (*list == NULL || (*list)->next == NULL) {
        return NULL;
    }

    GridList* oldList = *list;
    *list = (*list)->next;
    Grid* grid = oldList->grid;
    free(oldList);
    return grid;
}
