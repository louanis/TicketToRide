#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

void update_move(t_game_info * game_info, MoveData * move, int playerId){
    
    switch(move->action){
        case 1:
            claim_track_board(game_info->board,playerId,move->claimRoute);
            break;
        case 2:

            break;
        case 3:
            break;

        case 4:
            break;


        default:
            break;
    }

    return;
}