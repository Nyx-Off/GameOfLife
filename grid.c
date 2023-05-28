#include <stdlib.h>
#include <stdio.h>  
#include "grid.h"
#include "gameoflife.h" 

Grid* createGrid(int width, int height) {
    Grid* grid = (Grid*) malloc(sizeof(Grid));
    grid->width = width;
    grid->height = height;
    
    // Memory allocation for cells
    grid->cells = (Cell**) malloc(height * sizeof(Cell*));
    for (int i = 0; i < height; i++) {
        grid->cells[i] = (Cell*) malloc(width * sizeof(Cell));
        for (int j = 0; j < width; j++) {
            grid->cells[i][j].x = i;
            grid->cells[i][j].y = j;
            grid->cells[i][j].status = DEAD;
        }
    }
    
    return grid;
}

// grid.c
void resetGrid(Grid* grid) {
    for(int i = 0; i < grid->height; i++) {
        for(int j = 0; j < grid->width; j++) {
            grid->cells[i][j].status = DEAD;
        }
    }
}

void resizeGrid(Grid* grid, int newWidth, int newHeight) {
    // Create new cells
    Cell** newCells = (Cell**) malloc(newHeight * sizeof(Cell*));
    for (int i = 0; i < newHeight; i++) {
        newCells[i] = (Cell*) malloc(newWidth * sizeof(Cell));
        for (int j = 0; j < newWidth; j++) {
            if (i < grid->height && j < grid->width) {
                newCells[i][j] = grid->cells[i][j];  // Copy old cells
            } else {
                newCells[i][j].x = i;
                newCells[i][j].y = j;
                newCells[i][j].status = DEAD;  // Initialize new cells
            }
        }
    }
    
    // Free old cells
    freeGrid(grid);

    // Update grid
    grid->cells = newCells;
    grid->width = newWidth;
    grid->height = newHeight;
}

void initializeGrid(Grid* grid) {
    for(int i = 0; i < grid->height; i++) {
        for(int j = 0; j < grid->width; j++) {
            if (i == j || i == grid->width - j) { // par exemple, initialiser une diagonale de cellules à ALIVE
                grid->cells[i][j].status = ALIVE;
            } else {
                grid->cells[i][j].status = DEAD;
            }
        }
    }
}

void updateGrid(Grid* grid) {
    // Logic for updating the grid goes here.
    applyGameOfLifeRules(grid); // Added this line
}

void freeGrid(Grid* grid) {
    for (int i = 0; i < grid->height; i++) {
        free(grid->cells[i]);
    }
    free(grid->cells);
    free(grid);
}


void saveGrid(Grid* grid, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return;
    }

    fprintf(file, "%d %d\n", grid->width, grid->height);

    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            fprintf(file, "%d ", grid->cells[i][j].status);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

Grid* loadGrid(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return NULL;
    }

    int width, height;
    fscanf(file, "%d %d", &width, &height);

    Grid* grid = createGrid(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(file, "%d", &(grid->cells[i][j].status));
        }
    }

    fclose(file);

    return grid;
}
