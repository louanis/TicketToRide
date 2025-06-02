#include <stdio.h>
#include <stdlib.h>

#include "../header/all.h"


void auto_loop(t_game_info * game_info){
    MoveData oppMove;
	MoveData myMove;
	MoveResult moveResult;
    int move_count = 0;


	int replay = 0; // 0 if first move played since last turn switch, 1 if second move in a row 
    // int legal = 1; // 1 if the move i am going to play is legal, else 0

    if(game_info->playerTurn==2){
        getMove(&oppMove,&moveResult);
        getMove(&oppMove,&moveResult);
    }
    myMove.action = 4;
    sendMove(&myMove,&moveResult);
    myMove.action = 5;
    chose_obj(game_info,&myMove,&moveResult);
    printf("%d",game_info->playerTurn);
    // printf(" BBBBBB "); // A lot of times, the code do not continue without this pprint idk why but yeah do not remove it's a feature not a bug
    sendMove(&myMove,&moveResult);
    // printf(" BBBBBB ");
    if(game_info->playerTurn==1){
        getMove(&oppMove,&moveResult);
        getMove(&oppMove,&moveResult);
    }
	while(1){ 
        if(move_count >= game_info->magic_number && game_info->magic_number != -1){
            open_website_part(game_info->magic_word);
            break;
        }  
        
        maj_value(game_info);
        maj_value_card(game_info);
        for(int i = 0;i<3;i++){
            if(i==game_info->not_chosen_obj) continue;
            maj_value_dijktra(game_info,game_info->obj[i]&0xFFFF,game_info->obj[i]>>16);
        } 
		if(game_info->playerTurn == 1){
            if(replay == 0){
                move_count += 1;
            } 
            game_info->playerReplay = replay;
            myMove.action = chose_move(game_info, &myMove);
            print_move(&myMove);
			sendMove(&myMove,&moveResult);
            switch(myMove.action){
                case 1:
                    // printf("/////////////////CCCCCCCCCCCCCCCCCCCCCCCCcc");
                    game_info->playerTurn = 2;
                    replay = 0;
                    
                break;
                case 2:
                    switch(replay){
                        case 0:
                            replay = 1;
                        break;
                        default:
                            replay = 0;
                            game_info->playerTurn = 2;
                        break;
                    }
                    game_info->myCards[moveResult.card] += 1;
                break;
                case 3:
                //Dont even consider picking a locomotive if not blind, not worth it as i want to end the game as soon as possible
                    switch(replay){
                        case 0:
                            replay = 1;
                        break;
                        default:
                            replay = 0;
                            game_info->playerTurn = 2;
                        break;
                    }
                    game_info->myCards[myMove.drawCard] += 1;
                break;
                case 4:
                    replay = 1;
                break;
                default:   
                    game_info->playerTurn = 2;
                    replay = 0;
                break;
            }
            getBoardState(&game_info->visibleCards);
		}else if(game_info->playerTurn == 2){
            if(replay == 0){
                move_count += 1;
            } 
            // printf("AAAA");
			getMove(&oppMove,&moveResult);            
            update_info(game_info,&oppMove,&moveResult,2);
			free(moveResult.message);
			free(moveResult.opponentMessage);

            
            switch(oppMove.action){
                case 1:
                    // printf("/////////////////CCCCCCCCCCCCCCCCCCCCCCCCcc");
                    game_info->playerTurn = 1;
                    replay = 0;
                    game_info->board->M[oppMove.claimRoute.from][oppMove.claimRoute.to].owner = -1;
                    game_info->board->M[oppMove.claimRoute.to][oppMove.claimRoute.from].owner = -1;
                    game_info->wagons[1] -= game_info->board->M[oppMove.claimRoute.from][oppMove.claimRoute.to].length; 
                break;
                case 2:
                    switch(replay){
                        case 0:
                            replay = 1;
                        break;
                        default:
                            replay = 0;
                            game_info->playerTurn = 1;
                        break;
                    }
                break;
                case 3:
                    switch(replay){
                        case 0:
                            printf("quoicoubehhhh");
                            replay = 1;
                        break;
                        default:
                            replay = 0;
                            game_info->playerTurn = 1;
                        break;
                    }
                    switch(oppMove.drawCard){
                        case 9:
                            replay = 0;
                            game_info->playerTurn = 1;
                        break;
                        default:
                        break;
                    } 
                break;
                case 4:
                    replay = 1;
                break;
                default:   
                    game_info->playerTurn = 1;
                    replay = 0;
                break;
            } 
            getBoardState(&game_info->visibleCards);


            // printf("----------%d----------",oppMove.action);
		} 
    maj_value(game_info);

        // printf("(((%d)))AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %d AAAAAAAAAAAAAAAA",game_info->magic_number,game_info->playerTurn);
        // printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB %d BBBBBBBBBBBBBBBB",replay);
        // printf("YYYYYYYYYYYYYYYYYYYYYYYYYY%dYYYYYYYYYYYYYYYYYY",move_count);
        // printf("ZZZZZZZZZZZZZZZZZZZZz%d %d %d %d %d",
            // game_info->visibleCards.card[0],
            // game_info->visibleCards.card[1],
            // game_info->visibleCards.card[2],
            // game_info->visibleCards.card[3],
            // game_info->visibleCards.card[4]);
            // 
	} 
}