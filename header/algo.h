#ifndef ALGO_H
#define ALGO_H
#include "struct.h"

int is_placable(t_game_info * game_info, t_track * track);
uint32 track_value_dijktra(const void * e1, int mode);
uint32 track_value(t_matrix_track * matrix, t_dijktra_output * best_path);
uint32 score(int length);
uint32 cost_track(t_game_info * game_info, t_track * track, int dist_from_start);
void dijktra(t_matrix_track * matrix, t_dijktra_output * ret, int cit1, int cit2, int (*track_value_dijktra)(const void *, int));
uint32 choose_biggest(t_game_info * game_info);
t_track * uint_city_to_track(t_game_info * game_info, uint32 cit);

#endif