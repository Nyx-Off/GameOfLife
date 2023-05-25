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

    // Parcourez toutes les cellules et dessinez-les
    for (int i = 0; i < grid->height; i++) {
        for (int j = 0; j < grid->width; j++) {
            Cell* cell = &(grid->cells[i][j]);
            SDL_Rect cellRect = {cell->x * 4, cell->y * 4, 4, 4}; // taille des cellules définie à 2px pour cet exemple
            if (cell->status == ALIVE) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // couleur blanche pour les cellules vivantes
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
