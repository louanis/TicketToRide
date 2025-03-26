#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

t_matrix_track * init_matrix_track(GameData data){

    t_matrix_track * return_matrix = (t_matrix_track*)malloc(sizeof(t_matrix_track));
    return_matrix -> size = data.nbCities;
    return_matrix -> M = (t_track**) malloc(return_matrix->size*sizeof(t_track*));
    return_matrix -> nullTrack = (t_track){0xFFFF,0,0,0};

    for(int i = 0;i<return_matrix->size;i++){
        return_matrix -> M[i] = (t_track*) malloc(return_matrix->size*sizeof(t_track));
    }

    for(int i = 0;i<return_matrix->size;i++){
        for(int j = 0;j<return_matrix->size;j++){
            return_matrix -> M[i][j] = return_matrix -> nullTrack;
        }
    }

    for(int i = 0; i<data.nbTracks*5; i+=5){
        int mincit = MIN(data.trackData[i+0],data.trackData[i+1]);
        int maxcit = MAX(data.trackData[i+0],data.trackData[i+1]);

        return_matrix -> M[maxcit][mincit].length = data.trackData[i+2];
        return_matrix -> M[maxcit][mincit].col1 = data.trackData[i+3];
        return_matrix -> M[maxcit][mincit].col2 = data.trackData[i+4];

        return_matrix -> M[mincit][maxcit].length = data.trackData[i+2];
        return_matrix -> M[mincit][maxcit].col1 = data.trackData[i+3];
        return_matrix -> M[mincit][maxcit].col2 = data.trackData[i+4];
    }


    return return_matrix;
}

void free_matrix_track(t_matrix_track * matrix){


    for(int i = 0; i<matrix->size; i++){
        free(matrix -> M[i]);
    }
    

    free(matrix -> M);

    free(matrix);

    return;
}