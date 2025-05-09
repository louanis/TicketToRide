#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

int chose_move(t_game_info * game_info, MoveData * playMove){ 

    if(is_placable(game_info,&game_info->board->M[22][23]) >0){
        build_route(game_info,playMove,22,23);
        return 1;
    } 

    if(is_placable(game_info,&game_info->board->M[0][1]) >0){
        build_route(game_info,playMove,0,1);
        return 1;
    } 

    if(is_placable(game_info,&game_info->board->M[1][2]) >0){
        build_route(game_info,playMove,1,2);
        return 1;
    } 


    playMove->action = 2;
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

uint32 choose_biggest_per_col(t_game_info * game_info,int col){ //if no biggest placable, returns 0. else returns (city1<<16)+city2 or the opposite it doesn't matter, i can <<16 bcause the city id will never be on more bits than 16 anyway

    int currsize = 0;
    t_track currtrack;
    uint32 retcit;
    for(int i = 0; i<game_info->board->size;i++){
        for(int j = 0; j<game_info->board->size;j++){
            currtrack = game_info->board->M[i][j];  
            if(is_placable(game_info,&currtrack) != 0 && (currtrack.col1 == col || currtrack.col2) ){
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


uint32 min_presence_col(t_game_info * game_info){
    int set_min = 0;
    int ret_id;
    for(int i = 1;i<9;i++){
        if(game_info->myCards[i] > 0){
            if(set_min == 0){
                ret_id = i;
                set_min = 1;
            } 
            else {
                if(game_info->myCards[i]<game_info->myCards[ret_id]){
                    ret_id=i;
                } 
            } 
        } 
    } 
    return (uint32) ret_id;
}

void build_route(t_game_info * game_info, MoveData * playMove, uint32 cit1, uint32 cit2){
    playMove->action = 1;
    playMove->claimRoute.color = is_placable(game_info,&game_info->board->M[cit1][cit2]);
    playMove->claimRoute.from = cit1;
    playMove->claimRoute.to = cit2;

    if(game_info->myCards[is_placable(game_info,&game_info->board->M[cit1][cit2])] < game_info->board->M[cit1][cit2].length){
        playMove->claimRoute.nbLocomotives = game_info->board->M[cit1][cit2].length - game_info->myCards[is_placable(game_info,&game_info->board->M[cit1][cit2])];
    } else{
        playMove->claimRoute.nbLocomotives = 0;
    }
    game_info->board->M[cit1][cit2].owner = 1;
    game_info->board->M[cit2][cit1].owner = 1;
    game_info->myCards[playMove->claimRoute.color] -=  game_info->board->M[cit1][cit2].length - playMove->claimRoute.nbLocomotives;
    game_info->myCards[9] -= playMove->claimRoute.nbLocomotives; 

    return;
} 