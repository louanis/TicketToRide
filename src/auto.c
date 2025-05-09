#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"


void auto_loop(t_game_info * game_info){
    MoveData oppMove;
	MoveData myMove;
	MoveResult moveResult;



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
    printf(" BBBBBB "); // A lot of times, the code do not continue without this pprint idk why but yeah do not remove it's a feature not a bug
    sendMove(&myMove,&moveResult);
    printf(" BBBBBB ");
    if(game_info->playerTurn==1){
        getMove(&oppMove,&moveResult);
        getMove(&oppMove,&moveResult);
    }
	while(1){ 

		if(game_info->playerTurn == 1){
            myMove.action = chose_move(game_info, &myMove);
            print_move(&myMove);
			sendMove(&myMove,&moveResult);
            switch(myMove.action){
                case 1:
                    printf("/////////////////CCCCCCCCCCCCCCCCCCCCCCCCcc");
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
		}else if(game_info->playerTurn == 2){
            printf("AAAA");
			getMove(&oppMove,&moveResult);            
            update_info(game_info,&oppMove,&moveResult,2);
			free(moveResult.message);
			free(moveResult.opponentMessage);

            
            switch(oppMove.action){
                case 1:
                    printf("/////////////////CCCCCCCCCCCCCCCCCCCCCCCCcc");
                    game_info->playerTurn = 1;
                    replay = 0;
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
                break;
                case 4:
                    replay = 1;
                break;
                default:   
                    game_info->playerTurn = 1;
                    replay = 0;
                break;
            } 


            printf("----------%d----------",oppMove.action);
		} 

        printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %d AAAAAAAAAAAAAAAA",game_info->playerTurn);
        printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB %d BBBBBBBBBBBBBBBB",replay);
	} 
}