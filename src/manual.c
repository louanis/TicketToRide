#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"


void manual_loop(t_game_info * game_info, int me, int opp, GameData * Gdat){
    MoveData * firstMove = (MoveData*) malloc(sizeof(MoveData));
    MoveData * secondMove = (MoveData*) malloc(sizeof(MoveData));

    int gameFinished = 0;
    int turn = -1; //0 opp 1 me 

    while(gameFinished == 0){
        
    }


    free(firstMove);
    free(secondMove);
    return;
}