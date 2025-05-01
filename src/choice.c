#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

int chose_move(t_game_info * game_info){ 
    return 2;
    // TODO : REMAKE THE FUNCTION SO THAT EVERYTING FROM SELECTION TO SENDING TO THE GAME IS DONE INSIDE THIS FUNCTION
    if(choose_biggest(game_info) != 0){
        return 1;
    } 
}

int chose_obj(t_game_info * game_info, MoveData * myMove, MoveResult * mresult){
    int max = 0;
    for(int i = 0;i<3;i++){
        if(mresult->objectives[i].score > mresult->objectives[max].score){
            max = i;
        } 
        myMove->chooseObjectives[i] = 1;
    }
    myMove->chooseObjectives[max] = 0;
    return 1;
}


uint32 choose_biggest(t_game_info * game_info){ //if no biggest placable, returns 0. else returns (city1<<16)+city2 or the opposite it doesn't matter, i can <<16 bcause the city id will never be on more bits than 16 anyway

    int currsize = 0;
    t_track currtrack;
    uint32 retcit;
    for(int i = 0; i<game_info->board->size;i++){
        for(int j = 0; j<game_info->board->size;j++){
            currtrack = game_info->board->M[i][j];  
            if(is_placable(game_info,&currtrack) != 0){
                if(currsize<currtrack.length){
                    currsize = currtrack.length;
                    retcit = (i<<16) + j;
                } 
            } 
        } 
    } 
    if (currsize == 0){
        return 0;
    } 
    return retcit;
}