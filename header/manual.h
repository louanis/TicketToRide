#ifndef MANUAL_H
#define MANNUAL_H
#include "struct.h"

void manual_loop(t_game_info * game_info, int me, int opp, GameData * Gdat);
void interpret_data(MoveData * move_data, MoveResult * move_result);
void choice_move(MoveData * move_data, t_game_info * game_info);

#endif