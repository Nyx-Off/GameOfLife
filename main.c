#include <SDL.h>
#include <stdio.h>
#include "grid.h"
#include "gameoflife.h"
#include "display.h"
#include "gridlist.h"

int main(int argc, char* argv[]) {
    // Initialisation de la SDL
    initDisplay(800, 800);

    // Initialisation de la liste pour le suivi de l'historique de la grille
    GridList* history = NULL;
    GridList* future = NULL;

    // Chargement de la grille à partir d'un fichier
    Grid* grid = loadGrid("last_state.txt");
    if (grid == NULL) {
        grid = createGrid(100, 100);
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
                        resetGrid(grid);
                        initializeGrid(grid); // ajouter cette ligne
                        if (paused) { // ajouter ces lignes
                            while (history) { 
                                GridList* previousGrid = history;
                                history = history->next;
                                freeGrid(previousGrid->grid);
                                free(previousGrid);
                            }
                            addGridToList(&history, copyGrid(grid));
                        }
                        break;
                        case SDLK_RIGHT:
                            if (paused) {
                                updateGrid(grid);
                            }
                            break;
                        case SDLK_LEFT:
                            if (paused && history) {
                                GridList* previousGrid = history;
                                history = history->next;
                                addGridToList(&future, grid);
                                grid = previousGrid->grid;
                                free(previousGrid);
                            }
                            break;
                    }
                    break;
            }
        }

        if (!paused) {
            // Sauvegarde de l'état actuel de la grille avant l'itération
            char filename[100]; 
            //sprintf(filename, "save_state\\gridsave_%d.txt", SDL_GetTicks());
            //saveGrid(grid, filename);

            // Mise à jour de l'historique et de la grille
            addGridToList(&history, copyGrid(grid));
            updateGrid(grid);

            // Vidange de la liste future quand le jeu n'est pas en pause
            while (future) {
                GridList* nextGrid = future;
                future = future->next;
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
        history = history->next;
        freeGrid(previousGrid->grid);
        free(previousGrid);
    }

    while (future) {
        GridList* nextGrid = future;
        future = future->next;
        freeGrid(nextGrid->grid);
        free(nextGrid);
    }

    return 0;
}
