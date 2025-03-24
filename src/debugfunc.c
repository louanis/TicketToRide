#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

void is_all_good(ResultCode actionResult){
    
    if(actionResult == ALL_GOOD){
        printf("All Good\n");
    }else{
        printf("Oh Oh\n");
    }

    return;
}
void print_board_data(GameData data){
    for(int i = 0; i<data.nbTracks*5;i+=5){
        printf("%d %d %d %d %d\n",data.trackData[i],data.trackData[i+1],data.trackData[i+2],data.trackData[i+3],data.trackData[i+4]);
    }
    return;

}
