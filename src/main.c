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

    print_board_data(Gdat);

    is_all_good(actionResult);

    t_matrix_board * gamestate = init_matrix_board(Gdat);
    free_matrix_board(gamestate);

    actionResult = quitGame();
    return 0;
}