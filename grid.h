#ifndef GRID_H
#define GRID_H

#include "cell.h"

typedef struct {
    int width;
    int height;
    Cell** cells;
} Grid;

Grid* createGrid(int width, int height);
void resizeGrid(Grid* grid, int newWidth, int newHeight);
void freeGrid(Grid* grid);
void initializeGrid(Grid* grid);
void updateGrid(Grid* grid);
void saveGrid(Grid* grid, const char* filename);
Grid* loadGrid(const char* filename);
void resetGrid(Grid* grid);
Grid* copyGrid(const Grid* original);

#endif