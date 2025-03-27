#include <stdio.h>
#include <stdlib.h>
#include "../header/all.h"

/*Gives us the value for 1 track targeted to the building of the dijktra*/
int track_value_dijktra(const void * e1, int mode){
    return ((t_track*) e1) -> length;
}

/*Gives us the total track value after considering the dijktra*/
int  track_value(t_matrix_track * matrix, t_dijktra_output * best_path){
    return 1;
}

/*Dijktra*/
void dijktra(t_matrix_track * matrix, t_dijktra_output * ret, int cit1, int cit2, int (*track_value_dijktra)(const void *, int)){
    int * track_value_arr = (int*) malloc(matrix->nbTrack * sizeof(int));
    int * is_in_path = (int*) malloc(matrix->nbTrack*sizeof(int)); //0 no 1 yes
    t_track ** tracks;
    void construct_track_list(matrix, tracks);
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