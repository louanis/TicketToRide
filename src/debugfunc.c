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

void AfficherEtatPlateau(BoardState * EtatPlateau){
    printf("cartes visibles : ");
    for(int i = 0;i<5;i++){
        printf("%d ",EtatPlateau->card[i]);
    } 
    printf("\n");
    return;
} 

void AfficherAction(MoveData * moveData){
    switch((int)moveData->action){
        case 1:
            printf("Route Claim : ");
            printf("from : %d, to : %d, couleur : %d, longueur : %d",moveData->claimRoute.from,moveData->claimRoute.to,(int)moveData->claimRoute.color,moveData->claimRoute.nbLocomotives);
        break;

        case 2:
            printf("blind card was drawn");
        break;

        case 3:
            printf("The drawn card has the color %d",(int)moveData->drawCard);
        break;

        case 4:
            printf("Objectives have been drawn");
        break;

        case 5:
            printf("Objectives have been choosen");
        break;

        default:
        break;
    } 

} 

void AfficherObjectif(MoveResult * mresult){
    printf("objectifs : ");
    for(int i = 0;i<5;i++){
        printf("(from %d to %d score %d)",mresult->objectives[i].from,mresult->objectives[i].to,mresult->objectives[i].score);
    } 
    printf("\n");
    return;
}  

void print_move(MoveData * playMove){
    printf("\n");
    switch(playMove->action){
        case 1:
            printf("from : %d, to: %d, loco: %d, color: %d",playMove->claimRoute.from,playMove->claimRoute.to,playMove->claimRoute.nbLocomotives, playMove->claimRoute.color);
        break;
        case 2:
            printf("blind");
        break;
        default:
        break;
    } 
} 
