#ifndef STRUCT_H
#define STRUCT_H
#include "../tickettorideapi/ticketToRide.h"
#include "uint.h" 


typedef int t_state;
/*
* My turn = 0
* Opp turn = 1
* I draw objectives = 2
* Opp draw objectives = 3
* I drawed a non visible loc card = 4
* Opp drawed a non visible loc card = 5
*/

typedef struct t_matrix_{
    int ** M;
    int size;
}t_matrix;

typedef struct t_dijktra_output_{
    int * listeDistance;
    int * listeEtapePrec;
}t_dijktra_output;

typedef struct t_track_{
    int length;
    int owner; // 1 me -1 adv 0 no one
    int col1;
    int col2;
    uint32 value;
    int dijktra;
}t_track;

typedef struct t_matrix_track_{
    t_track ** M;
    t_track nullTrack;
    int size;
    int nbTrack;
}t_matrix_track;


typedef struct t_objective_{
    int cit1;
    int cit2;
    int points;
}t_objective;

typedef struct t_player_{
    int nbCars;
    int nbCards;
    int * tabCards;
    int nbObjectives;
    t_objective * tabObjectives;
}t_player;

typedef struct t_game_info_{
    int playerTurn; //1 me 2 op
    int playerReplay;
    int myNumber;
    BoardState visibleCards;
    t_track bestTracks[10];
    int myCards[10]; //The cards will be set to 0 and the 0th element will stay 0 forever to not burden myself with verification of color index later on
    int availableCardsMajoration[10];
    uint32 chosenCol; //The color i chose to focus on, if &(1<<x) >0 then i am focusing on the x color
    int wagons[2]; //wagons[0] my wagons, wagons[1] opp wagons,  
    t_matrix_track * board;
    GameData * gData;
    int oppCardCounter;
    char * magic_word;
    int magic_number;
    int obj[3]; // cit1<<16+cit2 for each element of the array
    int not_chosen_obj; 
}t_game_info;


// typedef struct t_matrix_board_{
//     t_matrix * matrixTrackLength;
//     t_matrix * matrixTrackOwner; // 1 me -1 adv 0 no one
//     t_matrix * matrixTrackCol1;
//     t_matrix * matrixTrackCol2;
// }t_matrix_board;

#endif