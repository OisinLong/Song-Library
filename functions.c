#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

// Important to note that i regard the rows starting at 0 with this function, so the first row is row 0 not row 1
void row_swap(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN], int row1, int row2)
{
    // Medium is used as a medium to temporarily hold a row of data while swapping the two of them to ensure no values are lost
    char medium[MAX_SONGS + 1][MAX_LEN];
    // Iterates across the width of a row
    for(int i = 0; i < MAX_ARTISTS; i++)
    {
        strcpy(medium[i], arr[row1][i]);
        strcpy(arr[row1][i], arr[row2][i]);
        strcpy(arr[row2][i], medium[i]);
    }
}

void displayArray(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN])
{
    for(int i = 0; i < MAX_ARTISTS; i++)
    {
        // Displays the artist as [i][0] will always be an artist
        // Conditional to avoid printing null strings in cases where array isnt completely full
        if ((strcmp(arr[i][0],empty) == 0)){
            break;
        }
        // Else display output
        printf("%s:\n",arr[i][0]);
        fflush(stdout);
        // Inner i starts at 1 to avoid printing the artist, as the outer loop deals with that
        for(int inner_i = 1; inner_i <= MAX_SONGS; inner_i++)
        {
            // Displays each song for the corresponding [i] indexed artist
            // Inner i iterates while i stays constant, thus printing everything on the given row (i)
            // Conditional to avoid printing null strings in cases where array isnt completely full
            if ((strcmp(arr[i][inner_i],empty) == 0)){
                break;
            }
            // Else display output
            printf("\t%s\n",arr[i][inner_i]);
            fflush(stdout);
        }
    }
}

// Two varying modes, depending on if artists or songs are being sorted
void quickSort(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int lower_index,int upper_index,int constant_index,int artists_OR_songs)
{
    if(artists_OR_songs == ARTIST){
        // Base case to stop stack overflow when it isn't satisfied
        if(lower_index < upper_index){
            int pivot_index = pivot_split(arr,lower_index,upper_index,constant_index,artists_OR_songs);

            // Recursive calls for each side of the pivot, pivot_index is ignored as it's in the correct position
            quickSort(arr,lower_index,pivot_index - 1,constant_index,artists_OR_songs);
            quickSort(arr,pivot_index + 1,upper_index,constant_index,artists_OR_songs);
        }
    // Else sorting is done, thus no need for any code
    }

    else if(artists_OR_songs == SONG){
        // Base case to stop stack overflow when it isn't satisfied
        if(lower_index < upper_index){
            int pivot_index = pivot_split(arr,lower_index,upper_index,constant_index,artists_OR_songs);

            // Recursive calls for each side of the pivot, pivot_index is ignored as it's in the correct position
            quickSort(arr,lower_index,pivot_index - 1,constant_index,artists_OR_songs);
            quickSort(arr,pivot_index + 1,upper_index,constant_index,artists_OR_songs);
        }
        // Else sorting is done, thus no need for any code
    }
}


// Two varying modes, depending on if artists or songs are being sorted
// This function sorts the items in the given array bounds into two sides of the pivot, less than or more than
// It returns the inex of the pivot for use in the recursive calls to quicksort
int pivot_split(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int lower_index,int upper_index,int constant_index,int artists_OR_songs)
{
    if(artists_OR_songs == SONG){
        // First item in given constraints is my pivot
        char pivot[50];
        strcpy(pivot, arr[constant_index][lower_index]);

        int index_less_than_pivot = lower_index;

        // This loops thru the array, swapping items with the pivot to ensure that evey item < pivot is to the left and every item > pivot is to the right
        for (int i = lower_index + 1; i <= upper_index; i++)
        {
            if(strcasecmp(arr[constant_index][i],pivot) < 0){
                swap_strings(arr[constant_index][++index_less_than_pivot],arr[constant_index][i]);
            }
        }

        // After done iterating through the array, pivot must be moved to the correct position
        swap_strings(arr[constant_index][index_less_than_pivot],arr[constant_index][lower_index]);
        // The index of the pivot is returned to the program so it can be avoided in recursive calls
        return index_less_than_pivot;
    }

    else if(artists_OR_songs == ARTIST){

        // First item in given constraints is my pivot
        char pivot[50];
        strcpy(pivot, arr[lower_index][constant_index]);

        int index_less_than_pivot = lower_index;

        // This loops thru the array, swapping items with the pivot to ensure that evey item < pivot is to the left and every item > pivot is to the right
        for (int i = lower_index + 1; i <= upper_index; i++)
        {
            if(strcasecmp(arr[i][constant_index],pivot) < 0){
                row_swap(arr,++index_less_than_pivot,i);
                }
        }

        // After done iterating through the array, pivot must be moved to the correct position
        row_swap(arr,lower_index,index_less_than_pivot);
        // The index of the pivot is returned to the program so it can be avoided in recursive calls
        return index_less_than_pivot;

    }
    else{
        // This case should never be hit, but warnings are given for a function with no return value, thus this irrelevant case exists
        return 0;
    }

}

void prep_strings_for_shuffle(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN])
{
    char fancy_format[] = {"  -  "};
    for(int row = 0; row < num_artists; row++)
    {
        for(int col = 1; col <= songs_per_artist[row]; col++)
        {
            // Grabbing the artist name
            char temp_name[MAX_LEN];
            strcpy(temp_name,arr[row][0]);
            // Adding the gap between artist and song
            strcat(temp_name,fancy_format);
            // Adding current song to formatted artist string
            strcat(temp_name,arr[row][col]);
            // Rewriting the formatted string of artist + song in the spot where the song originally was
            strcpy(arr[row][col],temp_name);
        }
    }
}

void load_shuffling_array(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],char arr_for_shuffling[24][MAX_LEN])
{
    // Puts every song in the shuffling array twice, to allow for the shuffled list to contain every item twice
    for(int x = 0; x < 2; x++)
    {
        for(int row = 0; row < num_artists; row++)
        {
            for(int col = 1; col <= songs_per_artist[row]; col++)
            {
                strcpy(arr_for_shuffling[num_strs_in_shuffle_array++],arr[row][col]);
            }
        }
    }

}

void fisher_yates_shuffle(char arr_for_shuffling[24][MAX_LEN],int len)
{
    // Seeding the random number
    srand(time(NULL));

    // Iterates thru array
    for (int i = 0; i < len; i++)
    {
        // Generate a random index
        int random_index = rand() % len;

        // Swap the current element with the randomly selected element
        swap_strings(arr_for_shuffling[i], arr_for_shuffling[random_index]);
    }
}

void swap_strings(char str1[MAX_LEN],char str2[MAX_LEN])
{
    // Medium is used to ensure that no data is overwritten when swapping values, ie all the data is retained while swapping
    char medium[MAX_LEN];
    strcpy(medium,str1);
    strcpy(str1,str2);
    strcpy(str2,medium);
}

void shuffled_strict(char array[24][MAX_LEN],int max_iterations)
{
    // iterates from 0 to the end of the songs in the array, max iterations is the number of item in the array
    for(int x = 0; x < max_iterations; x++)
    {
        // Inner loop checks song[x] against the 5 songs after it in the array
        for(int i = (x + 1); i < (x + 6); i++)
        {
            // First position that a dupe can be swapped to so its outside the range of 5 songs from song[x]
            int swap_index = (x + 6);
            // Will keep swapping from a postion until string[x] doesn't have a dupe in string[i]
            while(strcasecmp(array[x],array[i]) == 0)
            {
                // Using % so the actual index value is locked in the range 0-23
                swap_strings(array[i],array[swap_index % max_iterations]);
                // incrementing for cases when it needs more than one swap
                swap_index++;
            }
        }
    }
}

bool valid_state(char arr[24][MAX_LEN],int len)
{
    // Default state is assuming its sorted, unless proven otherwuse with cases below
    bool state_of_arr = true;
    // Iterated across the array
    for(int x = 0; x < len; x++)
    {
        // Condition to prevent looking at memory outside array bounds
        if(x >= (len-5)){
            // Decrements the range in which i look ahead for dupe songs, to ensure im only looking within the bounds of the array
            for(int y = (x+1); y < len; y++)
            {
                // Case where two songs are the same within the limit, thus change state to false to show not sorted
                if(strcasecmp(arr[x],arr[y]) == 0){
                    state_of_arr = false;
            }

            }
        }
        // Condition for normal iterations of the array, until the last 5 elements are reached
        else{
            // Always looks 5 ahead
            for(int z = (x+1); z <= (x + 5); z++)
            {
                // Case where songs are the same, thus false is amended to state of the arr
                if(strcasecmp(arr[x],arr[z]) == 0){
                    state_of_arr = false;
                }
            }
        }
    }
    // Returns true if the array is sorted accordingly, or false if one of the conditions was triggered
    return state_of_arr;
}

void get_input(char array[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],char array_not4_sorting[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int frequency_of_songs_4artists[4])
{

    // Variables to transfer user input to the array
    char artist[MAX_LEN];
    char song[MAX_LEN];

    // This loop should only allow for a max of 4 iterations to accomodate max 4 artists per the program specs
    for(num_artists = 0; num_artists < MAX_ARTISTS; num_artists++)
    {
        // User input
        printf("Insert an artist/group name or Q to quit:\n");
        fflush(stdout);

        // fgets allows me to grab the entire input, which is more convenient than scanf which was finnicky in earlier iterations
        fgets(artist, sizeof(artist), stdin);

        // Removing the \n chr from my string so its not put in the array with \n
        artist[strcspn(artist,"\n")] = '\0';

        // Break condition to exit the input loop
        if(strcasecmp(artist,"Q") == 0){
            strcpy(array[num_artists][0],empty);
            strcpy(array_not4_sorting[num_artists][0],empty);
            break;
        }
        // Copying my string over to my array where it will b stored
        strcpy(array[num_artists][0],artist);
        strcpy(array_not4_sorting[num_artists][0],artist);


        // Inner loop to get songs for each artist, max 3 iterations and min 1 iteration
        // Same logic as outer loop, see comments for each corresponding line in outer loop
        // This loop starts at 1 so that i can index all the songs correctly, as the index [0] is taken by the artist name
        for(num_songs = 1; num_songs <= MAX_SONGS; num_songs++)
        {
            // This do while loop repeats the question to allow the user to reenter a valid song1 if they try to quit immediately
            do{
                printf("Enter song %d for %s or Q to quit\n",num_songs,artist);
                fflush(stdout);
                fgets(song, sizeof(song), stdin);
                song[strcspn(song,"\n")] = '\0';
            } while(num_songs < 2 && strcasecmp(song,"Q") == 0);

            // Rechecking both conditions for every break attempt just to be sure
            if(strcasecmp(song,"Q") == 0 && num_songs > 1){
                strcpy(array[num_artists][num_songs],empty);
                strcpy(array_not4_sorting[num_artists][num_songs],empty);
                break;
            }
            strcpy(array[num_artists][num_songs],song);
            strcpy(array_not4_sorting[num_artists][num_songs],song);

            // Keeps track of the number of songs each artist has stored
            frequency_of_songs_4artists[num_artists] = num_songs;
        }
    }
}

   