#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

// Variables to keep track of the number of inputted songs/artists
int num_artists,num_songs;
int songs_per_artist[4];
int num_strs_in_shuffle_array;

// Used to fill empty slots in array, making it easier to identify when displaying output
// Ensured that first chr has an ascii value above the letters range to ensure blanks get sorted to end to avoid early exits in displayArray
char empty[1] = {'|'};

int main(void)
{
    // This 3D array has MAX_ARTISTS rows and MAX_SONGS + 1 columns to allow for name storage
    char array[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN];
    char array_for_shuffling[24][MAX_LEN];
    char array_not_sorted[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN];

    // Rules for the input
    puts("You may only enter 'Q' after entering at least one song for each artist!");
    fflush(stdout);
    // Getting input from the user
    get_input(array,array_not_sorted,songs_per_artist);

    // Sorting the songs
    for(int i = 0; i < 4; i++)
    {
        // Using the upper bound as the num songs to prevent quicksort sorting null values, improving efficiency marginally
        // When artists are suffled, the array with songs per artists is wrong
        quickSort(array,1,songs_per_artist[i],i,SONG);
    }

    // Sorting the artists
    quickSort(array,0,num_artists-1,0,ARTIST);

    // Output after sorting
    puts("Array after sorting:\n");
    fflush(stdout);
    displayArray(array);

    // Shuffling process
    prep_strings_for_shuffle(array_not_sorted);
    load_shuffling_array(array_not_sorted,array_for_shuffling);
    fisher_yates_shuffle(array_for_shuffling,num_strs_in_shuffle_array);

    // If the total unique songs < 6, strict shuffle cant work
    if(num_strs_in_shuffle_array < 12){
        puts("You have to enter at least 6 unique songs for the shuffling to occur, please run the program again if you wish to retry\n");
        fflush(stdout);
    }
    // Else sort the songs, as there is enough to satisfy the conditions
    else{

        shuffled_strict(array_for_shuffling,num_strs_in_shuffle_array);
        // Repeats the cleanup function until the array is sorted accordingly
        while( !(valid_state(array_for_shuffling,num_strs_in_shuffle_array)) )
        {
            shuffled_strict(array_for_shuffling,num_strs_in_shuffle_array);
        }
        // Output after alll the shuffling
        puts("\nShuffled Playlist:\n");
        fflush(stdout);
        for(int j = 0; j < num_strs_in_shuffle_array; j++)
        {
            printf("%s\n",array_for_shuffling[j]);
        }
    }

    return 0;
}



