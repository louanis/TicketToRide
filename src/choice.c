#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

int chose_move(t_game_info * game_info){ 
    // TODO : REMAKE THE FUNCTION SO THAT EVERYTING FROM SELECTION TO SENDING TO THE GAME IS DONE INSIDE THIS FUNCTION
    if(choose_biggest(game_info) != 0){
        return 1;
    } 

    return 2;
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

