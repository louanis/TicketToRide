#include <stdlib.h>
#include <stdio.h>
#include "../header/all.h"

int chose_move(t_game_info * game_info, MoveData * playMove){ 

    if(game_info->playerReplay == 0){  
        if(is_placable(game_info,&game_info->board->M[22][23]) >0){
            build_route(game_info,playMove,22,23);
            return 1;
        } 

        if(is_placable(game_info,&game_info->board->M[0][1]) >0){
            build_route(game_info,playMove,0,1);
            return 1;
        } 

        // if(is_placable(game_info,&game_info->board->M[1][2]) >0){
            // build_route(game_info,playMove,1,2);
            // return 1;
        // } 
// 
        // if(is_placable(game_info,&game_info->board->M[16][17]) >0){
            // build_route(game_info,playMove,16,17);
            // return 1;
        // } 
// 
        // if(is_placable(game_info,&game_info->board->M[22][17]) >0){
            // build_route(game_info,playMove,22,17);
            // return 1;
        // } 
        

        if(game_info->wagons[0] == 0 || game_info->wagons[0] == 1){  
            playMove->action = 2;
            return 2;
        } 

        int curra,currb;
        int start = 1;
        for(int i = 0;i<game_info->board->size;i++){
           for(int j = 0;j<game_info->board->size;j++){
                if(i == j){
                    continue;
                }

                if(start != 1){
                    printf(";%d;",game_info->board->M[curra][currb].dijktra);

                    if(game_info->board->M[curra][currb].dijktra <= game_info->board->M[i][j].dijktra) {
                        if(game_info->board->M[i][j].value <= game_info->wagons[0]  && game_info->board->M[curra][currb].value < game_info->board->M[i][j].value && game_info->board->M[i][j].owner == 0 && game_info->board->M[i][j].length > 0){
                            curra = i;
                            currb = j;
                        } 
                    }
                }  
                else if (game_info->board->M[i][j].owner == 0 && game_info->board->M[i][j].length > 0){
                    curra = i;
                    currb = j;
                    start = 0;
                } 
                
            }  
        } 
        printf("((((((((((((((((((((((((((((((((((%d,%d))))))))))))))))))))))))))))))))))",curra,currb);
        if(is_placable(game_info,&game_info->board->M[curra][currb]) >0 && game_info->board->M[curra][currb].length <= game_info->wagons[0]){
            build_route(game_info,playMove,curra,currb);
            return 1;       
        }else if(game_info->board->M[curra][currb].col2 == 0){

            if(is_in(game_info->board->M[curra][currb].col1,(int*)&game_info->visibleCards,5) && game_info->board->M[curra][currb].col1 != 9){
                playMove->action = 3; // Draw a face-up card
                playMove->drawCard = game_info->board->M[curra][currb].col1 ;
                return 3;
            } 
        } else{
            if(game_info->myCards[game_info->board->M[curra][currb].col1] > game_info->myCards[game_info->board->M[curra][currb].col2]){
                if(is_in(game_info->board->M[curra][currb].col1,(int*)&game_info->visibleCards,5) && game_info->board->M[curra][currb].col1 != 9){
                playMove->action = 3; // Draw a face-up card
                playMove->drawCard = game_info->board->M[curra][currb].col1 ;
                return 3;
                } 
            } else{
                if(is_in(game_info->board->M[curra][currb].col2,(int*)&game_info->visibleCards,5) && game_info->board->M[curra][currb].col1 != 9){
                playMove->action = 3; // Draw a face-up card
                playMove->drawCard = game_info->board->M[curra][currb].col2 ;
                return 3;
                } 
            } 
        } 

        playMove->action = 2;
        return 2;
    } 

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
        game_info->obj[i] = (mresult->objectives[i].from<<16) + mresult->objectives[i].to;
    }
    myMove->chooseObjectives[max] = 0;
    game_info->not_chosen_obj = max;
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

uint32 choose_biggest_per_col(t_game_info * game_info,int min, int col){ //if no biggest placable, returns 0. else returns (city1<<16)+city2 or the opposite it doesn't matter, i can <<16 bcause the city id will never be on more bits than 16 anyway

    int currsize = 0;
    t_track currtrack;
    uint32 retcit;
    for(int i = 0; i<game_info->board->size;i++){
        for(int j = 0; j<game_info->board->size;j++){
            currtrack = game_info->board->M[i][j];  
            if(is_placable(game_info,&currtrack) != 0 && (currtrack.col1 == col || currtrack.col2) ){
                if(currsize<currtrack.length){
                    currsize = currtrack.length;
                    retcit = (i<<16) + j;
                } 
            } 
        } 
    } 
    if (currsize == 0){
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
    playMove->claimRoute.color = is_placable(game_info,&game_info->board->M[cit1][cit2]);
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
    
    if(game_info->board->M[cit1][cit2].dijktra == 1) printf("QOUAIHDZIAHDIAZHFIAZHFIZARAZIFHIAZHD\n\n\n");

    return;
}



void maj_value(t_game_info * game_info){
    for(int i = 0;i<game_info->board->size;i++){
        for(int j = 0;j<game_info->board->size;j++){

            game_info->board->M[i][j].dijktra = 0;
            game_info->board->M[j][i].dijktra = 0;

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
                game_info->board->M[i][j].value = score(game_info->board->M[i][j].length) * WEIGHT_TRACK_LENGTH;
                game_info->board->M[j][i].value = score(game_info->board->M[i][j].length) * WEIGHT_TRACK_LENGTH;
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