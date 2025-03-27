#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"


void manual_loop(t_game_info * game_info, int me, int opp, GameData * Gdat){
    MoveData move_data;
    MoveResult move_result;
    MoveData * myMove = (MoveData*)malloc(sizeof(MoveData));

    int gameFinished = 0;
    int turn = -1; //0 me 1 opp 
    int exept;

    t_state state = (Gdat -> starter - 1);

    while(gameFinished == 0){
        choice_move(&move_data,game_info);
        turn = machine_detat(&state,*myMove);
        if(turn == 0){
            sendMove(myMove,&move_result);
        }else if(turn == 1){
            getMove(&move_data,&move_result);
            printf("%s",move_result.opponentMessage);
            interpret_data(&move_data,&move_result);
        }
        printBoard();
        printf("exept:");scanf("%d",&exept);
        if(exept == 52){
            break;
        } 
    }


    free(myMove);
    return;
}

void interpret_data(MoveData * move_data, MoveResult * move_result){
    printf("Player who last moved has :");
    switch(move_data -> action){
        case 0x1:
            printf("Claimed a route\n city1 : %d, city2 : %d, color : %d, length : %d\n",move_data->claimRoute.from,move_data->claimRoute.to,move_data->claimRoute.color,move_data->claimRoute.nbLocomotives);
        break;
        case 0x2:
            printf("Drew (?) a blind card\n");
        break;
        case 0x3:
            printf("Drew (?) a card\n color : %d\n",move_data->drawCard);
        break;
        case 0x4:
            printf("Drew objectives\n");
        break;
        case 0x5:
            printf("Chose objectives\n");
        break;
        default:
        return;
    } 
    return;
} 

void choice_move(MoveData * move_data, t_game_info * game_info){
    int action;
    choix:
    scanf("%d",&action);
    move_data->action = action;

    switch(action){
        case 0x1:
            int cit1,cit2;
            scanf("%d %d",&cit1,&cit2);
            move_data->claimRoute.from = MIN(cit1,cit2);
            move_data->claimRoute.to = MAX(cit1,cit2);
        break;
        case 0x2:
            return;
        break;
        default:
        break;
    } 
    goto choix;
    return;
} 