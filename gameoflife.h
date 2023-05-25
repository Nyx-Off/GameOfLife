#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "grid.h"

void applyGameOfLifeRules(Grid* grid);
int countLivingNeighbors(Grid* grid, int row, int col);

#endif
