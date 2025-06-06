#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <curl/curl.h>
#include "../header/all.h"

/*I used copilot to find the alternative to the windows version on :
https://stackoverflow.com/questions/58467675/how-to-open-web-urls-using-c-language 
*/
void open_website_part(char *magic_word) {
    CURL *curl;
    CURLcode res;

    // Initialize a CURL session
    curl = curl_easy_init();
    if (curl) {
        // Format the URL with the provided magic_word
        char url[256];
        snprintf(url, sizeof(url), "http://82.29.170.160:8889/player/disconnect/%s", magic_word);

        // Set the URL for the CURL request
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Clean up the CURL session
        curl_easy_cleanup(curl);
    }
}

int is_placable(t_game_info * game_info, t_track * track){ //returns 0 if not, the color number, takes into account locomotives but the number needs to be calculated afterwards
    

    if(track->owner != 0){ //We only look at free tracks
        return 0;
    } 

    if(track->col1 == 9){
        int currmin = 0;
        // TODO : list of color by least important to most important to chose the less important as possible
        for(int i = 1;i<9;i++){
            if(game_info->myCards[i] + game_info->myCards[9] >= track->length){
                currmin = i;
                break;
            } 
        } 
        if(currmin == 0){
            return 0;
        } 
        return min_presence_col(game_info,game_info->myCards[currmin]);
    } 
    
    int wagon_placable1 = game_info->myCards[track->col1] + game_info->myCards[9]; //Number of cards of col1
    int wagon_placable2 = 0;
    if(track->col2!=0){
        wagon_placable2 = game_info->myCards[track->col2] + game_info->myCards[9]; //Number of cards of col2
    }   

    if(wagon_placable1 >= track->length){   // This will be changed at one point to use the card the less needed in the globality of the game
        return track->col1;
    } else if(wagon_placable2 >= track->length){
        return track->col2;
    } 
    return 0;
} 


t_track * uint_city_to_track(t_game_info * game_info, uint32 cit){
    return &(game_info->board->M[cit&0xFFFF][cit>>16]);
} 

/*Gives us the value for 1 track targeted to the building of the dijktra*/
uint32 track_value_dijktra(const void * e1, int mode){
    return score(((t_track*) e1) -> length);
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


