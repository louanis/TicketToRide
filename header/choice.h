#ifndef CHOICE_H
#define CHOICE_H
#include "all.h"

int costTurnNumber(int city1, int city2, t_matrix_track board); //
int chose_move(t_game_info * game_info);
int chose_obj(t_game_info * game_info,MoveData * myMove, MoveResult * mresult);
uint32 choose_biggest(t_game_info * game_info);
#endif