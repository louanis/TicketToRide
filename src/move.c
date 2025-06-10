#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

void update_move(t_game_info * game_info, MoveData * move, int playerId){
    
    switch(move->action){
        case 1:
            claim_track_board(game_info->board,playerId,move->claimRoute);
            break;
        case 2:
            game_info->oppCardCounter+= 1;
            break;
        case 3:
            game_info->availableCardsMajoration[move->drawCard] -= 1; 
            game_info->oppCardCounter+= 1;
            break;

        case 4:
            break;


        default:
            break;
    }

    return;
}