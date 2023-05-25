#ifndef CELL_H
#define CELL_H

typedef enum {
    DEAD,
    ALIVE
} CellState;

typedef struct {
    int x;
    int y;
    CellState status;  // DEAD ou ALIVE
} Cell;

#endif
