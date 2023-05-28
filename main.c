#include <SDL.h>
#include <stdio.h>
#include "grid.h"
#include "gameoflife.h"
#include "display.h"
#include "gridlist.h"

int main(int argc, char* argv[]) {
    // Initialisation de la SDL
    initDisplay(800, 800);

    // Demander à l'utilisateur la taille de la grille
    int size;
    printf("Veuillez entrer la taille de la grille(cellules x cellules): ");
    scanf("%d", &size);

    // Initialisation de la liste pour le suivi de l'historique de la grille
    GridList* history = NULL;
    GridList* future = NULL;

    // Chargement de la grille à partir d'un fichier
    Grid* grid = loadGrid("start.txt");
    if (grid == NULL) {
        grid = createGrid(size, size);
        initializeGrid(grid);
    }
    int running = 1;
    int paused = 0;
    while (running) {
        // Traitement des événements SDL
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    saveGrid(grid, "last_state.txt");
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_SPACE:
                            paused = !paused;
                            break;
                        case SDLK_r:
                        freeGrid(grid);  // Libérer la mémoire de l'ancienne grille
                        grid = loadGrid("start.txt");  // Charger à nouveau la grille à partir du fichier
                        if (grid == NULL) {
                            grid = createGrid(size, size);
                            initializeGrid(grid);
                        }
                        while (history) {
                            GridList* previousGrid = history;
                            history = previousGrid->next;
                            freeGrid(previousGrid->grid);
                            free(previousGrid);
                        }
                        addGridToList(&history, copyGrid(grid));
                        break;
                        case SDLK_RIGHT:
                        if (paused && future) {
                            GridList* nextGrid = future;
                            future = future->prev;
                            addGridToList(&history, copyGrid(grid));
                            grid = nextGrid->grid;
                            free(nextGrid);
                        } else {
                            addGridToList(&history, copyGrid(grid));
                            updateGrid(grid);
                            while (future) {
                                GridList* nextGrid = future;
                                future = future->prev;
                                freeGrid(nextGrid->grid);
                                free(nextGrid);
                            }
                        }
                        break;
                        case SDLK_LEFT:
                            if (paused && history) {
                                addGridToList(&future, grid);
                                grid = getPreviousGrid(&history);
                            }
                            break;
                    }
                    break;
            }
        }

        if (!paused) {
            addGridToList(&history, copyGrid(grid));
            updateGrid(grid);
            while (future) {
                GridList* nextGrid = future;
                future = future->prev;
                freeGrid(nextGrid->grid);
                free(nextGrid);
            }
        }


        // Mise à jour de l'affichage
        updateDisplay(grid);

        SDL_Delay(100);
    }

    // Libération des ressources
    freeGrid(grid);
    freeDisplay();

    while (history) {
        GridList* previousGrid = history;
        history = previousGrid->next;
        freeGrid(previousGrid->grid);
        free(previousGrid);
    }

    while (future) {
        GridList* nextGrid = future;
        future = nextGrid->next;
        freeGrid(nextGrid->grid);
        free(nextGrid);
    }

    return 0;
}

