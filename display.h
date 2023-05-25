#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include "grid.h"

void initDisplay(int width, int height);
void updateDisplay(Grid* grid);
void freeDisplay();

#endif