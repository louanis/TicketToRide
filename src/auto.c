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
    sendMove(&myMove,&moveResult);
    if(game_info->playerTurn==2){
        getMove(&oppMove,&moveResult);
        getMove(&oppMove,&moveResult);
    }

	while(1){ 
        printf("%d",game_info->playerTurn);


		if(game_info->playerTurn == 2){
            myMove.action = chose_move(game_info);
			sendMove(&myMove,&moveResult);
            switch(myMove.action){
                case 1:
                    game_info->playerTurn = 1;
                    replay = 0;
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

		}else if(game_info->playerTurn == 1){
			getMove(&oppMove,&moveResult);
			free(moveResult.message);
			free(moveResult.opponentMessage);

			if((int)oppMove.action == 2 || (int)oppMove.action == 4 ){ //%2 == 0

				switch(replay){
					case 0:
						game_info->playerTurn = 1;
						replay = 1;
					break;

					default:
						game_info->playerTurn = 2;
						replay = 0;
					break;
				} 

			} else if ((int)oppMove.action == 3){ // if in another if to prevent wrongful acess of 
				if( (int)oppMove.drawCard == 9){
					game_info->playerTurn = 1;
                    replay = 0;

				} else{
                    switch(replay){
                        case 0:  
					        game_info->playerTurn = 1;
                            replay = 1;
                        break;

                        default:
					        game_info->playerTurn = 2;
                            replay = 0;
                        break;
                    }

				} 
			}  else{
				game_info->playerTurn = 2;
                replay = 0;
			} 
		} 
	} 
}