#ifndef GESTIONDATA_H
#define GESTIONDATA_H
#include "struct.h"

t_matrix_track * init_matrix_track(GameData data);
void free_matrix_track(t_matrix_track * matrix);
void claim_track_board(t_matrix_track * matrix, int player, ClaimRouteMove claimed_track);
void construct_track_list(t_matrix_track * matrix, t_track ** track_list);
unsigned int is_in(int a, int * b, int size);
int track_to_claimRouteMove(ClaimRouteMove * claim_route, t_game_info * game_info, int color, int cit1, int cit2);
void update_info(t_game_info * game_info, MoveData * dmove,MoveResult * rmove, int playerNumber);
#endif