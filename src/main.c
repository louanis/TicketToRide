#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER "82.29.170.160"

int main(){
    extern int DEBUG_LEVEL;
    DEBUG_LEVEL = INTERN_DEBUG;

    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER,"QuoicouTrain");

    
    GameData Gdat;
    actionResult = sendGameSettings("TRAINING PLAY_RANDOM delay=2", &Gdat);
    printf("-----");
    
    actionResult = printBoard();
    printf("%d",actionResult);

    print_board_data(Gdat);

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
    gameInfo->playerTurn = 1+((Gdat.starter-1)^1);
    for(int i = 0;i<9;i++){
        gameInfo->myCards[i] = 0;
    } 
    for(int i = 0;i<4;i++){
        gameInfo->myCards[Gdat.cards[i]]++; 
    }
    // getBoardState(&gameInfo->visibleCards);
    //--------------------------------------------------------
    

    auto_loop(gameInfo);
    free_matrix_track(gamestate);
    printf("Starter %d\n",Gdat.starter);
    actionResult = quitGame();
    return 0;
}