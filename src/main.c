#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "../header/all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER "82.29.170.160"

int main(int argc,char** argv){

    char *activeWord = NULL; // To store the word after --active
    int activeInt = 0;       // To store the integer after the word
    char *lobbyString = NULL; // To store the string after --lobby
    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--active") == 0 && i + 2 < argc) {
            activeWord = argv[i + 1]; // Save the word after --active
            activeInt = atoi(argv[i + 2]); // Convert the next string to an integer
            i += 2; // Skip the next two arguments
        } else if (strcmp(argv[i], "--lobby") == 0 && i + 1 < argc) {
            lobbyString = argv[i + 1]; // Save the string after --lobby
            i += 1; // Skip the next argument
        }
    } 
    if (activeWord != NULL) {
        printf("Active Word: %s\n", activeWord);
        printf("Active Int: %d\n", activeInt);
    }
    if (lobbyString != NULL) {
        printf("Lobby String: %s\n", lobbyString);
    }
    extern int DEBUG_LEVEL;
    DEBUG_LEVEL = INTERN_DEBUG;

    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER,"QuoicouTrain");

    
    GameData Gdat;
    actionResult = sendGameSettings("TRAINING NICE_BOT delay=1", &Gdat); //PLAY_RANDOM NICE_BOT
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
    gameInfo->magic_word = activeWord;
    gameInfo->magic_number = activeInt;
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
    getBoardState(&gameInfo->visibleCards);
    gameInfo->oppCardCounter = 5;
    //--------------------------------------------------------
    

    auto_loop(gameInfo);
    free_matrix_track(gamestate);
    printf("Starter %d\n",Gdat.starter);
    actionResult = quitGame();
    return 0;
}