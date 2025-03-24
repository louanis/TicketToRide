#ifndef STRUCT_H
#define STRUCT_H
#include "all.h"


typedef struct t_matrix_{
    int ** M;
    int size;
}t_matrix;

typedef struct t_matrix_board_{
    t_matrix * matrixTrackLength;
    t_matrix * matrixTrackOwner;
    t_matrix * matrixTrackCol1;
    t_matrix * matrixTrackCol2;
}t_matrix_board;

#endif