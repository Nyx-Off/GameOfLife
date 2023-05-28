#include <stdlib.h>
#include "gridlist.h"

void addGridToList(GridList** list, Grid* grid) {
    GridList* newList = (GridList*) malloc(sizeof(GridList));
    newList->grid = grid;
    newList->next = *list;
    newList->prev = NULL;
    newList->count = (*list != NULL) ? (*list)->count + 1 : 1;  // Increment count

    if (*list != NULL) {
        (*list)->prev = newList;
    }
    *list = newList;

    // Check if list size exceeded maximum and remove oldest if necessary
    if ((*list)->count > MAX_LIST_SIZE) {
        GridList* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        if (current->prev != NULL) {
            current->prev->next = NULL;
        }
        freeGrid(current->grid);
        free(current);
    }
}

Grid* getPreviousGrid(GridList** list) {
    if (*list == NULL) {
        return NULL;
    }
    Grid* grid = (*list)->grid;
    *list = (*list)->next;
    return grid;
}

Grid* getNextGrid(GridList** list) {
    if (*list == NULL) {
        return NULL;
    }
    Grid* grid = (*list)->grid;
    *list = (*list)->next;
    return grid;
}
