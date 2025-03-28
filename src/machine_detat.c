#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"  
//#define DEBUG_ETAT_H

// Returns 0 if illegal move, else 1
int machine_detat(t_state * state, MoveData * move){
    switch(*state){
        case 0:
            printf("je suis en plein dedans la \n");
            if(move->action == 0x3){
                if(move->drawCard == 9){
                    *state = 1;
                }else{
                    *state = 4;
                } 
            }else if(move->action == 0x2){
                *state = 4;
            }else if(move->action == 0x4){
                *state = 2;
            }else if(move->action == 0x5 || move->action == 0x1){
                *state = 0;
            }else{
                return 0;
            }
        return 1;
            
        case 1:
            if(move->action == 0x3){
                if(move->drawCard == 9){
                    *state = 0;
                }else{
                    *state = 5;
                } 
            }else if(move->action == 0x2){
                *state = 5;
            }else if(move->action == 0x4){
                *state = 3;
            }else if(move->action == 0x5 || move->action == 0x1){
                *state = 0;
            }else{
                return 0;
            }
        return 1;

        case 2:
            if(move->action == 0x5){
                *state = 1;
                return 1;
            }else{
                return 0; 
            } 

        break;

        case 3:

            if(move->action == 0x5){
                *state = 0;
                return 1;
            }else{
                return 0; 
            } 
        return 0;
        
        case 4:
            if(move->action == 0x3){
                if(move->drawCard == 9){
                    return 0;
                } else{
                    *state = 1;
                    return 1;
                } 
            } else if(move->action == 0x2){
                *state = 1;
                return 1;
            } else{
                return 0;
            }
        break;
        
        default:
            if(move->action == 0x3){
                if(move->drawCard == 9){
                    return 0;
                } else{
                    *state = 0;
                    return 1;
                } 
            } else if(move->action == 0x2){
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