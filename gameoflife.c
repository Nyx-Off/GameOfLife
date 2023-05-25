#include "gameoflife.h"

Grid* copyGrid(const Grid* grid) {
    Grid* newGrid = createGrid(grid->width, grid->height);
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            newGrid->cells[i][j] = grid->cells[i][j];
        }
    }
    return newGrid;
}

void applyGameOfLifeRules(Grid* grid) {
    // Copie de la grille pour se référer aux états précédents
    Grid* oldGrid = copyGrid(grid);

    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            int livingNeighbors = countLivingNeighbors(oldGrid, i, j);

            if (oldGrid->cells[i][j].status == DEAD && livingNeighbors == 3) {
                grid->cells[i][j].status = ALIVE; // Naissance
            } else if (oldGrid->cells[i][j].status == ALIVE && (livingNeighbors < 2 || livingNeighbors > 3)) {
                grid->cells[i][j].status = DEAD; // Mort
            }
        }
    }
    
    freeGrid(oldGrid); // Libération de la mémoire de la grille copiée
}

int countLivingNeighbors(Grid* grid, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < grid->height && newCol >= 0 && newCol < grid->width) {
                count += (grid->cells[newRow][newCol].status == ALIVE) ? 1 : 0;
            }
        }
    }
    count -= (grid->cells[row][col].status == ALIVE) ? 1 : 0; // On enlève la cellule elle-même
    return count;
}
