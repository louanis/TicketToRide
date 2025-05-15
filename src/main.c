#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER "82.29.170.160"

int main(int argc,char** argv){

    for(int i = 0;i<argc;i++){
    } 
    extern int DEBUG_LEVEL;
    DEBUG_LEVEL = INTERN_DEBUG;

    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER,"QuoicouTrain");

    
    GameData Gdat;
    actionResult = sendGameSettings("TRAINING NICE_BOT delay=0", &Gdat); //PLAY_RANDOM NICE_BOT
    printf("-----");
    
    actionResult = printBoard();
    printf("%d",actionResult);

    // print_board_data(Gdat);

    // printf("------");
    t_matrix_track * gamestate = init_matrix_track(Gdat);
    BoardState EtatPlateau;
    getBoardState(&EtatPlateau);
    // MoveResult mresult;

    
    //--------------------------------------------------------
    t_game_info * gameInfo = (t_game_info *)malloc(sizeof(t_game_info));
    gameInfo->gData = &Gdat;
    gameInfo->board = gamestate;
    gameInfo->myNumber = 1;
    switch(Gdat.starter){
        case 1:
        gameInfo->playerTurn = 2;
        break;

        default:
        gameInfo->playerTurn = 1;
        break;
    }
    for(int i = 0;i<9;i++){
        gameInfo->myCards[i] = 0;
    } 
    for(int i = 0;i<4;i++){
        gameInfo->myCards[Gdat.cards[i]]++; 
    }
    gameInfo->wagons[0] = 45;
    gameInfo->wagons[1] = 45; 
    //gameInfo->availableCardsMajoration[1] =  
    // getBoardState(&gameInfo->visibleCards);
    gameInfo->oppCardCounter = 5;
    gameInfo->speed = 1;
    //--------------------------------------------------------
    

    auto_loop(gameInfo);
    free_matrix_track(gamestate);
    printf("Starter %d\n",Gdat.starter);
    actionResult = quitGame();
    return 0;
}