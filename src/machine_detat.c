#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"  
//#define DEBUG_ETAT_H

// Returns 0 if illegal move, else 1
int machine_detat(t_state * state, MoveData * move_data,MoveResult * move_result, t_game_info * info){
    switch(*state){
        case 0:
            if(move_data->action == 0x3){
                if(move_data->drawCard == 9){
                    *state = 1;
                }else{
                    if(is_in((int)move_data->drawCard,(int*)info->visibleCards,5)){
                        *state = 4;
                    }else{
                        return 0;
                    } 
                } 
            }else if(move_data->action == 0x2){
                *state = 4;
            }else if(move_data->action == 0x4){
                *state = 2;
            }else if(move_data->action == 0x5 || move_data->action == 0x1){
                *state = 0;
            }else{
                return 0;
            }
        return 1;
            
        case 1:
            if(move_data->action == 0x3){
                if(move_data->drawCard == 9){
                    *state = 0;
                }else{
                    *state = 5;
                } 
            }else if(move_data->action == 0x2){
                *state = 5;
            }else if(move_data->action == 0x4){
                *state = 3;
            }else if(move_data->action == 0x5 || move_data->action == 0x1){
                *state = 0;
            }else{
                return 0;
            }
        return 1;

        case 2:
            if(move_data->action == 0x5){
                *state = 1;
                return 1;
            }else{
                return 0; 
            } 

        break;

        case 3:

            if(move_data->action == 0x5){
                *state = 0;
                return 1;
            }else{
                return 0; 
            } 
        return 0;
        
        case 4:
            if(move_data->action == 0x3){
                if(move_data->drawCard == 9){
                    return 0;
                } else{
                    if(is_in((int)move_data->drawCard,(int*)info->visibleCards,5)){
                        *state = 4;
                    } 
                    *state = 1;
                    return 1;
                } 
            } else if(move_data->action == 0x2){
                printf("mmmmm");
                *state = 1;
                return 1;
            } else{
                return 0;
            }
        break;
        
        default:
            if(move_data->action == 0x3){
                if(move_data->drawCard == 9){
                    return 0;
                } else{
                    *state = 0;
                    return 1;
                } 
            } else if(move_data->action == 0x2){
                *state = 0;
                return 1;
            } else{
                return 0;
            }
        return 0;
    } 

    return 0;

} 

#ifdef DEBUG_ETAT_H
int main(){
    t_state state = 0;
    MoveData * myMove = (MoveData*)malloc(sizeof(MoveData));
    myMove -> action = 4;
    while(1){
        machine_detat(&state,myMove);
        printf("%d",state);
        scanf("%d",(int*)&myMove->action); 
    }
}   
#endif