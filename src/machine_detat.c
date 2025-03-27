#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"  

// Returns 0 if illegal move, else 1
int machine_detat(t_state * state, MoveData move){
    switch(*state){
        case 0:
            if(move.action == 0x3){
                if(move.drawCard == 9){
                    *state = 1;
                }else{
                    *state = 4;
                } 
            }else if(move.action == 0x2){
                *state = 4;
            }else {
                *state = 1;
            }
        return 1;

        case 1:
        return 0;

        case 2:
            if(move.action == 0x5){
                *state = 1;
                return 1;
            }else{
                return 0; 
            } 

        break;

        case 3:
        return 0;

        case 4:
            if(move.action == 0x3){
                if(move.drawCard == 9){
                    return 0;
                } else{
                    *state = 1;
                    return 1;
                } 
            } else if(move.action == 0x2){
                *state = 1;
                return 1;
            } else{
                return 0;
            }
        break;
        
        default:
        return 0;
    } 

    return 0;

} 