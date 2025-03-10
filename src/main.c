#include "all.h"

#define PORT_SERVER 15001
#define ADDR_SERVER cgs.valentin-lefebre.com

int main(){
    ResultCode actionResult;
    actionResult = connectToCGS(ADDR_SERVER, PORT_SERVER);

    actionResult = ResultCode sendName("QuoicouKING");

    GameSettings gameset = (GameSettings){0x1,0x1,15,1,951,0};
    actionResult = sendGameSettings(GameSettings gameSettings, GameData* gameData);

    actionResult = printBoard();

    actionResult = quitGame();
    return 0;
}