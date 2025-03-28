#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"
//#define V1 

#ifdef V1

void manual_loop(t_game_info * game_info, int me, int opp, GameData * Gdat){
    MoveData move_data;

    MoveResult move_result;
    MoveData * myMove = (MoveData*)malloc(sizeof(MoveData));
    MoveData * curr_move;

    int gameFinished = 0;
    int exept;

    t_state state = (Gdat -> starter - 1)^1;
    
    
    printf("state : %d\n",state);

    fflush(stdout);
    printf("move : %d\n",myMove->action);

    //---------Choix OBJ---------
    if(state==1){
        printf(" ");
        getMove(&move_data,&move_result);
        getMove(&move_data,&move_result);
    }
    myMove->action = 4;
    sendMove(myMove,&move_result);
    printf("selection ? :");
    scanf("%d %d %d",(int*)&myMove->chooseObjectives[0],(int*)&myMove->chooseObjectives[1],(int*)&myMove->chooseObjectives[2]);
    myMove->action = 5; 
    sendMove(myMove,&move_result);
    if(state==0){
        printf(" ");
        getMove(&move_data,&move_result);
        getMove(&move_data,&move_result);
    }
    //---------Fin Choix OBJ---------

    printf("-----");
    state = (Gdat -> starter - 1)^1;
    t_state prec_state = state;
    while(gameFinished == 0){

        while(1){
            printf("Boucle\n");
            printf("state : %d \n",state);
            printf("last move : %d\n",curr_move->action);
            
            if(state%2 == 0){
                if(state == 2){
                    printf("Choisir a piocher : ");
                    scanf("%d %d %d",(int*)&myMove->chooseObjectives[0],(int*)&myMove->chooseObjectives[1],(int*)&myMove->chooseObjectives[2]);
                }else if(state == 0){
                    printf("Choisir move : ");
                    scanf("%d",(int*)&myMove->action);
                    if(myMove->action == 1){

                    } else if(myMove -> action == 3){
                        printf("Quelle couleur");
                        scanf("%d",(int*)&myMove->drawCard);
                    } 
                    printf("BBBB");
                }else if(state == 4){
                    printf("Choisir move : ");
                    scanf("%d",(int*)&myMove->action);
                    if(myMove -> action == 3){
                        printf("Quelle couleur");
                        scanf("%d",(int*)&myMove->drawCard);
                    } 
                } 
            } 

            if(state%2 == 1){
                getMove(&move_data,&move_result);
                curr_move = &move_data;
            } 

            if(machine_detat(&state,curr_move,&move_result,game_info) == 1){
                break;
            } 

            printf("exept:");
            scanf("%d",&exept);
            if(exept == 52){
                return;
            }
            prec_state = state;
        }

        printf("Sortie de Boucle\n");
        printf("state : %d \n",state);
        printf("last move : %d\n",curr_move->action);

        if( prec_state%2 == 0 ){;
            curr_move = myMove;
            sendMove(curr_move,&move_result);
            printf("sendmove\n");
        }else if(prec_state%2 == 1){
            curr_move = &move_data;
        }



    }


    free(myMove);
    return;
}

void choice_move(MoveData * move_data, t_game_info * game_info){
    int action;
    choix:
    scanf("%d",&action);
    move_data->action = action;

    switch(action){
        case 0x1:
            int cit1,cit2;
            scanf("%d %d",&cit1,&cit2);
            move_data->claimRoute.from = MIN(cit1,cit2);
            move_data->claimRoute.to = MAX(cit1,cit2);
        break;

        case 0x2:
            return;
        break;

        case 0x4:
            printf("----");
            return;
        break;

        case 0x5:
            printf("----");
            scanf("%d %d %d",(int*)&move_data -> chooseObjectives[0],
                             (int*)&move_data -> chooseObjectives[1],
                             (int*)&move_data -> chooseObjectives[2]
                 );
            printf("%d %d %d",(int)move_data -> chooseObjectives[0],(int)move_data -> chooseObjectives[1],(int)move_data -> chooseObjectives[2]);
            return;

        break;

        default:
        break;
    } 
    goto choix;
    return;
} 

#else




#endif

