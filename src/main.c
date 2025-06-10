#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "../header/all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER "82.29.170.160"

int main(int argc,char** argv){

    /* Parse command-line arguments */
    char *activeWord = NULL; // To store the word after --active
    int activeInt = -1;      // To store the integer after the word after --active
    int versus = 0;          // Flag for versus mode
    int lobby = 0;           // Flag for lobby mode
    char *lobbyString = NULL;// To store the string after --lobby
    int boucle = -1;         // Loop counter for repeated games

    // Parse all command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--active") == 0 && i + 2 < argc) {
            activeWord = argv[i + 1]; // Save the word after --active
            activeInt = atoi(argv[i + 2]); // Convert the next string to an integer
            i += 2; // Skip the next two arguments
        } else if (strcmp(argv[i], "--lobby") == 0 && i + 1 < argc) {
            lobbyString = argv[i + 1]; // Save the string after --lobby
            lobby = 1;
            i += 1; // Skip the next argument
        } else if(strcmp(argv[i], "--versus") == 0) {
            versus = 1;
        } else if(strcmp(argv[i], "--bouclee") == 0 && i + 1 < argc) {
            boucle = atoi(argv[i + 1]); // Convert the next string to an integer
            printf("%d",boucle);
            i += 1; // Skip the next argument
        }
    } 

    // Print parsed arguments for debugging
    if (activeWord != NULL) {
        printf("Active Word: %s\n", activeWord);
        printf("Active Int: %d\n", activeInt);
    }
    if (lobbyString != NULL) {
        printf("Lobby String: %s\n", lobbyString);
    }

    // Set debug level
    extern int DEBUG_LEVEL;
    DEBUG_LEVEL = INTERN_DEBUG;

    // Connect to the game server
    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER,"QuoicouTrain");
    FILE * f;

    // Game data and tournament string
    GameData Gdat;
    char tourn[256];

    // Send game settings depending on mode (versus, lobby, or training)
    if(versus == 1){
        actionResult = sendGameSettings("", &Gdat);

    } else if(lobby == 1) {
         
        boucle = -2;
        if(lobbyString != NULL){
            snprintf(tourn, sizeof(tourn), "TOURNAMENT %s", lobbyString);
        } else {
            tourn[0] = '\0'; // fallback to empty string if lobbyString is NULL
        }
        actionResult = sendGameSettings(tourn, &Gdat);
    } else if(versus == 0 && lobby == 0){
        actionResult = sendGameSettings("TRAINING NICE_BOT delay=0", &Gdat); //PLAY_RANDOM NICE_BOT
        f = fopen("./data/vsNiceBot.txt","a");
    }
    
    // Print the board state for debugging
    actionResult = printBoard();
    printf("%d",actionResult);

    // Allocate and initialize the main game info structure
    t_game_info * gameInfo = (t_game_info *)malloc(sizeof(t_game_info));

    // Main game loop: repeat games as needed (for training, tournaments, etc.)
    while(boucle >= 0 || boucle == -1 || lobby == 1) {

    
        printf("------");
        // Initialize the board and get the current board state
        t_matrix_track * gamestate = init_matrix_track(Gdat);
        BoardState EtatPlateau;
        getBoardState(&EtatPlateau);
        // MoveResult mresult;

        
        //--------------------------------------------------------

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
        for(int i = 0;i<10;i++){
            gameInfo->myCards[i] = 0;
            gameInfo->availableCardsMajoration[i] = 12;
        } 
        gameInfo->availableCardsMajoration[9] = 14;
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

        // Write the result to file if in training mode
        if(f != NULL){
            fprintf(f,"%d\n",gameInfo->last_result);
        } 
        // Free the board memory
        free_matrix_track(gamestate);
        printf("Starter %d\n",Gdat.starter);

        // Exit loop if only one game is to be played
        if(boucle == -1|| boucle == 0 ) break;
        printf("QUOICOUHAHAHAHAHAHHAHAHA");
        boucle -= 1;

        // Reset game settings for the next game if needed
        if(versus == 1){
            actionResult = sendGameSettings("", &Gdat);
        } else if(lobby == 1) {
            actionResult = sendGameSettings(tourn, &Gdat);
            
        } else if(versus == 0 && lobby == 0){
            actionResult = sendGameSettings("TRAINING NICE_BOT delay=0", &Gdat); //PLAY_RANDOM NICE_BOT
        }
        
    }

    // If in training mode, calculate and write winrate to file
    if(f != NULL){
        fclose(f);
        f = fopen("./data/vsNiceBot.txt","r");
        int compteurtot = 0;
        int compteurwin = 0;
        int ca;
        while(feof(f) == 0){
            fscanf(f,"%d\n",&ca);
            compteurtot++;
            switch(ca){
                case 1:
                compteurwin ++;
                break;
                default:
                break;
            } 

        } 
        FILE * fwr = fopen("./data/currWr.txt","w");
        float wr = (1.0*compteurwin)/(compteurtot*1.0);
        fprintf(fwr,"%f",wr);
        fclose(fwr);
        fclose(f);
    } 

    // Quit the game and free any allocated memory
    actionResult = quitGame();
    if(activeWord != NULL){
        free(activeWord);
    }
    if(lobbyString != NULL){
       free(lobbyString); 
    }
    return 0;
}