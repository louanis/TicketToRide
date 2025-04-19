#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

int is_placable(t_game_info * game_info, t_track * track){ //returns 0 if not, 1 if possible with col1, 2 if possible with col2 ; takes into account loco
    int wagon_placable1 = game_info->myCards[track->col1] + game_info->myCards[9];
    int wagon_placable2 = 0;
    if(track->col2!=0){
        wagon_placable2 = game_info->myCards[track->col2] + game_info->myCards[9];
    }   

    if(wagon_placable1 >= track->length){
        return 1;
    } else if(wagon_placable2 >= track->length){
        return 2;
    } 
    return 0;
} 



/*Gives us the value for 1 track targeted to the building of the dijktra*/
uint32 track_value_dijktra(const void * e1, int mode){
    return ((t_track*) e1) -> length;
}

/*Gives us the total track value after considering the dijktra*/
uint32 track_value(t_matrix_track * matrix, t_dijktra_output * best_path){
    return 1;
}

uint32 score(int length){
    switch(length){
        case 1:
        return 1;

        case 2:
        return 2;

        case 3:
        return 4;

        case 4:
        return 7;

        case 5:
        return 10;

        default:
        return 15;
    } 
} 

uint32 cost_track(t_game_info * game_info, t_track * track, int dist_from_start){
    /*The assignations of the value variable in comments is for me to keep up to what i have in mind before forgeting it, so not pay to much attention to it*/

    uint32 cost = ((uint32) -1)/2 + dist_from_start * WEIGHT_TRACK_DISTANCE_FROM_START;
    // uint32 value = ((uint32) -1)/2 - dist_from_start * WEIGHT_TRACK_DISTANCE_FROM_START;
    // value += WEIGHT_TRACK_LENGTH * score(track->length);
    cost -= WEIGHT_TRACK_LENGTH * score(track->length);
    if(track->length-game_info->myCards[track->col1] < track->length-game_info->myCards[track->col2]){
        cost += track->length-game_info->myCards[track->col1]; 
        // value -= track->length-game_info->myCards[track->col1]; 
    } else{
        cost += track->length-game_info->myCards[track->col2]; 
        // value -= track->length-game_info->myCards[track->col2]; 
    } 

    return 0;
} 

/*Dijktra*/
void dijktra(t_matrix_track * matrix, t_dijktra_output * ret, int cit1, int cit2, int (*track_value_dijktra)(const void *, int)){
    int * track_value_arr = (int*) malloc(matrix->nbTrack * sizeof(int));
    int * is_in_path = (int*) malloc(matrix->nbTrack*sizeof(int)); //0 no 1 yes

    t_track * tracks;
    construct_track_list(matrix, &tracks);


    t_track * track_from = (t_track*) malloc(matrix->nbTrack*sizeof(t_track));
    track_from[1] = matrix->nullTrack;

    for(int i = 0; i<matrix->size;i++){
        track_value_arr[i] = 0;
        is_in_path[i] = 0;
    }

    /*
    dist[src] = 0;

    // Find the shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update the distance value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] if and only if the current distance is greater than the new distance,
            // and v is not in the shortest path tree
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the calculated shortest distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
    */

    free(tracks);

}