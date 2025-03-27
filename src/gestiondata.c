#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

/*--------------------------TRACKS MATRIX--------------------------*/

t_matrix_track * init_matrix_track(GameData data){

    t_matrix_track * return_matrix = (t_matrix_track*)malloc(sizeof(t_matrix_track));
    return_matrix -> size = data.nbCities;
    return_matrix -> M = (t_track**) malloc(return_matrix->size*sizeof(t_track*));
    return_matrix -> nullTrack = (t_track){-1,0,0,0};
    return_matrix -> nbTrack = 0;

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

        return_matrix ->nbTrack++;
    }


    return return_matrix;
}

void free_matrix_track(t_matrix_track * matrix){


    for(int i = 0; i<matrix->size; i++){int tabCards[10];
        free(matrix -> M[i]);
    }
    

    free(matrix -> M);

    free(matrix);

    return;
}


void construct_track_list(t_matrix_track * matrix, t_track ** track_list){

    track_list = (t_track**) malloc(matrix->nbTrack*sizeof(t_track*));
    int id = 0;

    for(int i = 0; i<matrix->size;i++){
        for(int j = i; j<matrix->size; j++){
            if(matrix->M[i][j].length != -1){
                track_list[id] = &(matrix->M[i][j]);
                id++;
            }
        }
    }   
    return;
}

void claim_track_board(t_matrix_track * matrix, int player, ClaimRouteMove claimed_track){
    int maxcit = MAX(claimed_track.from,claimed_track.to);
    int mincit = MAX(claimed_track.from,claimed_track.to);
    matrix -> M[maxcit][mincit].owner = player;

    return;
}

/*--------------------------OBJECTIVES--------------------------*/

/*--------------------------PLAYERS--------------------------*/

/*--------------------------GAME INFO--------------------------*/