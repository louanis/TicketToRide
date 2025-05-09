#ifndef DEBUG_FUNC_H
#define DEBUG_FUNC_H
#include "all.h"

void print_board_data(GameData data);
void is_all_good(ResultCode actionResult);

void AfficherEtatPlateau(BoardState * EtatPlateau);
void AfficherAction(MoveData * moveData);
void AfficherObjectif(MoveResult * mresult);
void print_move(MoveData * playMove);


#endif