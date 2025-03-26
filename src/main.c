#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER "cgs.valentin-lelievre.com"

int main(){
    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER);

    actionResult = sendName("QuoicouKING");
    
    GameSettings Gset = GameSettingsDefaults;
    GameData Gdat = GameDataDefaults;
    actionResult = sendGameSettings(Gset, &Gdat);
    printf("-----");
    
    actionResult = printBoard();
    printf("%d",actionResult);

    print_board_data(Gdat);

    // printf("------");
    t_matrix_track * gamestate = init_matrix_track(Gdat);
    free_matrix_track(gamestate);

    actionResult = quitGame();
    return 0;
}