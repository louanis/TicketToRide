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
    for(int i = 0; i<data.nbTracks;i++){
        printf("%d %d %d %d %d\n",data.trackData[i*5],data.trackData[i*5+1],data.trackData[i*5+2],data.trackData[i*5+3],data.trackData[i*5+4]);
        //printf("%d-----",i);
    }

    return;

}
