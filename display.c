#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

void initDisplay(int width, int height) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


void updateDisplay(Grid* grid) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Obtenez la largeur et la hauteur de la fenêtre
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Calculez la taille de la cellule pour que toutes les cellules s'adaptent à la fenêtre
    int cellWidth = windowWidth / grid->width;
    int cellHeight = windowHeight / grid->height;

    // Parcourez toutes les cellules et dessinez-les
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            Cell* cell = &(grid->cells[i][j]);
            SDL_Rect cellRect = {cell->x * cellWidth, cell->y * cellHeight, cellWidth, cellHeight};
            if (cell->status == ALIVE) {
                // Utilisez la couleur souhaitée ici, par exemple, la couleur en fonction du compteur pour les cellules vivantes
                SDL_SetRenderDrawColor(renderer,(rand() % 226) + 30, (rand() % 226) + 30,(rand() % 226) + 30, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // couleur noire pour les cellules mortes
            }
            SDL_RenderFillRect(renderer, &cellRect);
        }
    }

    SDL_RenderPresent(renderer);
}




void freeDisplay() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
