#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

t_matrix_board * init_matrix_board(GameData data){
    t_matrix_board * return_matrix = (t_matrix_board*) malloc(sizeof(t_matrix_board));
    return_matrix -> matrixTrackLength = (t_matrix*) malloc(sizeof(t_matrix));
    return_matrix -> matrixTrackOwner = (t_matrix*) malloc(sizeof(t_matrix));
    return_matrix -> matrixTrackCol1 = (t_matrix*) malloc(sizeof(t_matrix));
    return_matrix -> matrixTrackCol2 = (t_matrix*) malloc(sizeof(t_matrix));

    return_matrix -> matrixTrackLength -> size = data.nbCities;
    return_matrix -> matrixTrackOwner -> size = data.nbCities;
    return_matrix -> matrixTrackCol1 -> size = data.nbCities;
    return_matrix -> matrixTrackCol2 -> size = data.nbCities;


    return_matrix -> matrixTrackLength -> M = (int**) malloc(data.nbCities*sizeof(int *));
    return_matrix -> matrixTrackOwner -> M = (int**) malloc(data.nbCities*sizeof(int *));
    return_matrix -> matrixTrackCol1 -> M = (int**) malloc(data.nbCities*sizeof(int *));
    return_matrix -> matrixTrackCol2 -> M = (int**) malloc(data.nbCities*sizeof(int *));
    for(int iL = 0; iL < data.nbCities; iL++){
        return_matrix -> matrixTrackLength -> M[iL] = (int*) malloc(data.nbCities*sizeof(int));
    }
    for(int iO = 0; iO < data.nbCities; iO++){
        return_matrix -> matrixTrackOwner -> M[iO] = (int*) malloc(data.nbCities*sizeof(int));
    }
    for(int iC1 = 0; iC1 < data.nbCities; iC1++){
        return_matrix -> matrixTrackCol1 -> M[iC1] = (int*) malloc(data.nbCities*sizeof(int));
    }
    for(int iC2 = 0; iC2 < data.nbCities; iC2++){
        return_matrix -> matrixTrackCol2 -> M[iC2] = (int*) malloc(data.nbCities*sizeof(int));
    }

    for(int i = 0; i<data.nbCities; i++){
        for(int j = 0; j<data.nbCities; j++){
            return_matrix -> matrixTrackLength -> M[i][j] = -1;
        }
    }
    
    for(int i = 0; i<data.nbCities; i++){
        for(int j = 0; j<data.nbCities; j++){
            return_matrix -> matrixTrackOwner -> M[i][j] = 0;
        }
    }

    for(int i = 0; i<data.nbCities; i++){
        for(int j = 0; j<data.nbCities; j++){
            return_matrix -> matrixTrackCol1 -> M[i][j] = -1;
        }
    }

    for(int i = 0; i<data.nbCities; i++){
        for(int j = 0; j<data.nbCities; j++){
            return_matrix -> matrixTrackCol2 -> M[i][j] = -1;
        }
    }


    for(int i = 0; i<data.nbTracks*5; i+=5){
        int mincit = MIN(data.trackData[i+0],data.trackData[i+1]);
        int maxcit = MAX(data.trackData[i+0],data.trackData[i+1]);
        return_matrix -> matrixTrackLength -> M[maxcit][mincit] = data.trackData[i+2];
        return_matrix -> matrixTrackCol1 -> M[maxcit][mincit] = data.trackData[i+3];
        return_matrix -> matrixTrackCol2 -> M[maxcit][mincit] = data.trackData[i+4];


        return_matrix -> matrixTrackLength -> M[mincit][maxcit] = data.trackData[i+2];
        return_matrix -> matrixTrackCol1 -> M[mincit][maxcit] = data.trackData[i+3];
        return_matrix -> matrixTrackCol2 -> M[mincit][maxcit] = data.trackData[i+4];
    }

    return return_matrix;
}

void free_matrix_board(t_matrix_board * matrix){

    int size = matrix -> matrixTrackCol1 -> size;

    for(int i = 0; i<size; i++){
        free(matrix -> matrixTrackLength -> M[i]);
    }

    for(int i = 0; i<size; i++){
        free(matrix -> matrixTrackOwner -> M[i]);
    }

    for(int i = 0; i<size; i++){
        free(matrix -> matrixTrackCol1 -> M[i]);
    }

    for(int i = 0; i<size; i++){
        free(matrix -> matrixTrackCol2 -> M[i]);
    }

    free(matrix -> matrixTrackLength);
    free(matrix -> matrixTrackOwner);
    free(matrix -> matrixTrackCol1);
    free(matrix -> matrixTrackCol2);

    free(matrix);

    return;
}