#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

int chose_move(t_game_info * game_info, MoveData * playMove){ 
    
    maj_biggest_per_col(game_info);
    int col = biggest_col_majoration(game_info);
    uint32 road = choose_biggest_color(game_info,game_info->maxSizeCol[col],col);
        
    if(game_info->playerReplay == 0){  

        uint32 roadBIG = choose_biggest(game_info,6); 
        if(roadBIG != 0 && is_placable(game_info,&game_info->board->M[roadBIG>>16][roadBIG&(0xFFFF)])>0) {
            build_route(game_info,playMove,roadBIG>>16,roadBIG&(0xFFFF));
            return 1;
        }
        if(game_info->wagons[0] <= 5){
            uint32 road2 = choose_biggest(game_info,2); 
            if(road2 != 0 && is_placable(game_info,&game_info->board->M[road2>>16][road2&(0xFFFF)])>0) {
                build_route(game_info,playMove,road2>>16,road2&(0xFFFF));
                return 1;
            }
            road2 = choose_biggest(game_info,1); 
            if(road2 != 0 && is_placable(game_info,&game_info->board->M[road2>>16][road2&(0xFFFF)])>0) {
                build_route(game_info,playMove,road2>>16,road2&(0xFFFF));
                return 1;
            }
        } 
      
        if(col != 0 && road != (uint32) 0 && is_placable(game_info,&game_info->board->M[MAX(road>>16,road&(0xFFFF))][MIN(road>>16,road&(0xFFFF))]) > 0){
            build_route(game_info,playMove,road>>16,road&(0xFFFF));
            return 1;
        } 
    }
    for(int i = 0;i<9;i++) game_info->cardToPick[i] = 0;
    
    for(int i = 1;i<9;i++) {
        maj_card_to_pick(game_info);
        int we_pick = 0;
        for(int i = 0;i<5;i++) {
            int ind_c = game_info->visibleCards.card[i];
            for(int i = 1;i<9;i++) {
                if(game_info->cardToPick[ind_c] == 1) {
                    we_pick = ind_c;
                    break;
                }
            }
            if(we_pick > 0) break;
        }
        
        if(we_pick > 0) {
            printf("\n\n\n\n\n\n\n\n\n\n\n\n");

            playMove->action = 3; 
            playMove->drawCard = we_pick ;
            return 3;
        }
    }
    
    playMove->action = 2;
    return 2; 
    uint32 road2 = choose_biggest(game_info,6); 
    if(road2 == 0){
        //TODO : si aucun 6 posable pour l'instant et qu'une couleur est en presence de 5, poser une route de cette couleur 
        playMove->action = 2;
        return 2; 
        road = choose_biggest(game_info,5);
    } 
    if(road != (uint32) 0){
        build_route(game_info,playMove,road2>>16,road2&~(0xFFFF0000));
        return 1;
    } 
    
    playMove->action = 2;
    return 2; 


    // /*----
    // Choose the best face-up card to build the biggest route*/
    int bestCardIndex = -1;
    int maxPotential = 0;

    for (int i = 0; i < 5; i++) { // Iterate over the 5 face-up cards
        int cardColor = game_info->visibleCards.card[i];
        if (cardColor == 0 || cardColor == 9) {
            continue; // Skip if the card is not valid
        }

        // /*Calculate the potential of this card to help build the biggest route*/
        int potential = 0;
        for (int j = 0; j < game_info->board->size; j++) {
            for (int k = 0; k < game_info->board->size; k++) {
                t_track *track = &game_info->board->M[j][k];
                if (track->owner == 0 && (track->col1 == cardColor || track->col2 == cardColor || track->col1 == 9)) {
                    int neededCards = track->length - game_info->myCards[cardColor] - game_info->myCards[9];
                    if (neededCards <= 1) { // Prioritize tracks that are close to being completed
                        potential += track->length;
                    }
                }
            }
        }

        // /*Update the best card if this one has higher potential*/
        if (potential > maxPotential) {
            maxPotential = potential;
            bestCardIndex = i;
        }
    }

    if (bestCardIndex != -1 && bestCardIndex != 9 && bestCardIndex != 0) {
        playMove->action = 3; // Draw a face-up card
        playMove->drawCard = game_info->visibleCards.card[bestCardIndex] ;
        return 3;
    }


    playMove->action = 2;
    return 2;
    // TODO : REMAKE THE FUNCTION SO THAT EVERYTING FROM SELECTION TO SENDING TO THE GAME IS DONE INSIDE THIS FUNCTION
    if(choose_biggest(game_info,4) != 0){
        return 1;
    } 
}

int chose_obj(t_game_info * game_info, MoveData * myMove, MoveResult * mresult){
    int max = 0;
    for(int i = 0;i<3;i++){
        if(mresult->objectives[i].score > mresult->objectives[max].score){
            max = i;
        } 
        myMove->chooseObjectives[i] = 1;
    }
    myMove->chooseObjectives[max] = 0;
    return 1;
}


uint32 choose_biggest(t_game_info *game_info, int min) {
    int currsize = 0;
    t_track currtrack;
    uint32 retcit = 0;

    // Array to track connected cities
    int *connectedCities = (int *)calloc(game_info->board->size, sizeof(int));

    // Mark cities already connected by owned tracks
    for (int i = 0; i < game_info->board->size; i++) {
        for (int j = 0; j < game_info->board->size; j++) {
            if (game_info->board->M[i][j].owner == 1) { // Owned track
                connectedCities[i] = 1;
                connectedCities[j] = 1;
            }
        }
    }

    for (int i = 0; i < game_info->board->size; i++) {
        for (int j = 0; j < game_info->board->size; j++) {
            currtrack = game_info->board->M[i][j];
            if (is_placable(game_info, &currtrack) != 0) {
                // Check if the track connects to a city already connected
                int isPriority = connectedCities[i] || connectedCities[j];

                // Prioritize tracks that connect to already connected cities
                if ((isPriority && currsize <= currtrack.length) || (!isPriority && currsize < currtrack.length)) {
                    if (currtrack.length >= min && currtrack.length <= game_info->wagons[0]) {
                        currsize = currtrack.length;
                        retcit = (i << 16) + j;
                    }
                }
            }
        }
    }

    free(connectedCities);

    if (currsize == 0) {
        return 0;
    }
    return retcit;
}


uint32 choose_biggest_color(t_game_info *game_info, int min, int col) {
    int currsize = 0;
    t_track currtrack;
    uint32 retcit = 0;

    // Array to track connected cities
    int *connectedCities = (int *)calloc(game_info->board->size, sizeof(int));

    // Mark cities already connected by owned tracks
    for (int i = 0; i < game_info->board->size; i++) {
        for (int j = 0; j < game_info->board->size; j++) {
            if (game_info->board->M[i][j].owner == 1) { // Owned track
                connectedCities[i] = 1;
                connectedCities[j] = 1;
            }
        }
    }

    for (int i = 0; i < game_info->board->size; i++) {
        for (int j = 0; j < game_info->board->size; j++) {
            currtrack = game_info->board->M[i][j];
            if (is_placable(game_info, &currtrack) != 0) {
                // Check if the track connects to a city already connected
                int isPriority = connectedCities[i] || connectedCities[j];

                // Prioritize tracks that connect to already connected cities
                if(col != 9) {
                    
                    if ((isPriority && currsize <= currtrack.length) || (!isPriority && currsize < currtrack.length)) {
                        if (currtrack.length >= min && currtrack.length <= game_info->wagons[0] && (currtrack.col1 == col || currtrack.col2 == col)) {
                            currsize = currtrack.length;
                            retcit = (i << 16) + j;
                        }
                    }

                }else {

                    
                    if ((isPriority && currsize <= currtrack.length) || (!isPriority && currsize < currtrack.length)) {
                        if (currtrack.length >= min && currtrack.length <= game_info->wagons[0] && (currtrack.col1 == col || currtrack.col2 == col)) {
                            currsize = currtrack.length;
                            retcit = (i << 16) + j;
                        }
                    }
                    
                }
            }
        }
    }

    free(connectedCities);

    if (currsize == 0) {
        return 0;
    }
    return retcit;
}


int min_presence_col(t_game_info * game_info,int threshold){ //Returns the least present color in the deck but still above a certain threshold, if none then returns -1
    int set_min = 0;
    int ret_id = -1;
    for(int i = 1;i<9;i++){
        if(game_info->myCards[i] >= threshold){
            if(set_min == 0){
                ret_id = i;
                set_min = 1;
            } 
            else {
                if(game_info->myCards[i]<game_info->myCards[ret_id]){
                    ret_id=i;
                } 
            } 
        } 
    } 
    return ret_id;
}

void build_route(t_game_info * game_info, MoveData * playMove, uint32 cit1, uint32 cit2){
    playMove->action = 1;
    playMove->claimRoute.color = is_placable(game_info,&game_info->board->M[MAX(cit1,cit2)][MIN(cit1,cit2)]);
    playMove->claimRoute.from = cit1;
    playMove->claimRoute.to = cit2;

    if(game_info->myCards[is_placable(game_info,&game_info->board->M[cit1][cit2])] < game_info->board->M[cit1][cit2].length){
        playMove->claimRoute.nbLocomotives = game_info->board->M[cit1][cit2].length - game_info->myCards[is_placable(game_info,&game_info->board->M[cit1][cit2])];
    } else{
        playMove->claimRoute.nbLocomotives = 0;
    }
    game_info->board->M[cit1][cit2].owner = 1;
    game_info->board->M[cit2][cit1].owner = 1;
    game_info->myCards[playMove->claimRoute.color] -=  game_info->board->M[cit1][cit2].length - playMove->claimRoute.nbLocomotives;
    game_info->myCards[9] -= playMove->claimRoute.nbLocomotives; 
    game_info->wagons[0] -= game_info->board->M[cit1][cit2].length; 

    return;
}



void maj_value(t_game_info * game_info){
    for(int i = 0;i<game_info->board->size;i++){
        for(int j = 0;j<game_info->board->size;j++){
            if(game_info->board->M[i][j].owner == -1){
                game_info->board->M[i][j].value = 0;
                game_info->board->M[j][i].value = 0;
            } 
            else if (game_info->board->M[i][j].owner == 1){
                game_info->board->M[i][j].value = (uint32) -1;
                game_info->board->M[j][i].value = (uint32) -1;
            } 
            else if (game_info->board->M[i][j].owner == -2){
                game_info->board->M[i][j].value = 0;
                game_info->board->M[j][i].value = 0;
            } 
            else{
                game_info->board->M[i][j].value = game_info->board->M[i][j].length * WEIGHT_TRACK_LENGTH;
                game_info->board->M[j][i].value = game_info->board->M[i][j].length * WEIGHT_TRACK_LENGTH;
            } 
        } 
    } 
} 


void maj_value_card(t_game_info * game_info){

    for(int i = 0;i<game_info->board->size;i++){
        for(int j = 0;j<game_info->board->size;j++){
            if (game_info->board->M[i][j].owner == 0){
                if(is_placable(game_info,&game_info->board->M[i][j]) > 0){
                    game_info->board->M[i][j].value += WEIGHT_POSABLE;
                    game_info->board->M[j][i].value += WEIGHT_POSABLE;
                } 
            } 
        } 
    } 
} 

void maj_biggest_per_col(t_game_info * game_info){

    for(int i = 0;i<10;i++) game_info->maxSizeCol[i] = 0;

    for(int i = 0;i<game_info->board->size;i++){
        for(int j = 0;j<game_info->board->size;j++){
            int col1 = game_info->board->M[i][j].col1;
            int col2 = game_info->board->M[i][j].col2;
            if ((game_info->board->M[i][j].owner == 0)){
                game_info->maxSizeCol[col1] = MIN(game_info->wagons[0], MAX(game_info->maxSizeCol[col1],game_info->board->M[i][j].length) );
                game_info->maxSizeCol[col2] = MIN(game_info->wagons[0], MAX(game_info->maxSizeCol[col2],game_info->board->M[i][j].length) );
            } 
        } 
    } 
} 

int biggest_col_majoration(t_game_info * game_info){ //Ret 0 if none fullfil the conditions, else the color that fulfill it
    int deb = 1; 
    int ret = 0;
    for(int i = 0;i<9;i++){
        if(game_info->myCards[i] >= game_info->maxSizeCol[i] && game_info->myCards[i] >= game_info->maxSizeCol[9]){
            if(deb == 1){
                deb = 0;
                ret = i;
            } else{
                if(game_info->maxSizeCol[i]>game_info->maxSizeCol[ret]){
                    ret = i;
                } 
            } 
        } 
    } 

    if(ret == 0) {
        for(int i = 0;i<9;i++){
        if(game_info->myCards[i] >= game_info->maxSizeCol[9]){
            if(deb == 1){
                deb = 0;
                ret = i;
            } else{
                if(game_info->maxSizeCol[i]>game_info->maxSizeCol[9]){
                    ret = i;
                } 
            } 
        } 
    } 

    }
    return ret;
} 


void maj_card_to_pick(t_game_info * game_info) { 
    int curr_min = 0xFFF;
    int curr_max = 0;
    int ind = 0;
    for(int i = 1 ; i<9; i++) {
        if(game_info->cardToPick[i] == 2) continue;
        else if(game_info->cardToPick[i] == 1) game_info->cardToPick[i] = 2;
    }
    for(int i = 1; i<9 ; i++) {
        if(game_info->cardToPick[i] == 0) {

            if((game_info->availableCardsMajoration[i] - game_info->myCards[i] <= curr_min) && game_info->availableCardsMajoration[i] >= curr_max) {
                game_info->cardToPick[ind] = 0;
                game_info->cardToPick[i] = 1; 
                ind = i;
                curr_min = game_info->availableCardsMajoration[i] - game_info->myCards[i];
                curr_max = game_info->availableCardsMajoration[i];
            }   
        }
    }
}