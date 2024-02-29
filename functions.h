#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define MAX_ARTISTS 4
#define MAX_SONGS 3
#define MAX_LEN 50
// Extreme values to avoid errors with cross contamination
#define ARTIST 2002
#define SONG 4004

// Variables to keep track of the number of inputted songs/artists
// extern to ensure that the program recognises the vars here, but only declares them once between the 3 files
extern int num_artists,num_songs;
extern int songs_per_artist[4];
extern int num_strs_in_shuffle_array;

// Used to fill empty slots in array, making it easier to identify when displaying output
// Ensured that first chr has an ascii value above the letters range to ensure blanks get sorted to end to avoid early exits in displayArray
extern char empty[1];

// Function to swap two given rows of a 3D array, useful for sorting the artists alphabetically while bringing their associated songs with them
void row_swap(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN], int row1, int row2);

// Function to display a 3D array, makes the code cleaner and more readable instead of using a loop everytime i want to view the array during development
void displayArray(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN]);

// Function to sort a given chunk of a 3D array, with a helper function used by quicksort
void quickSort(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int lower_index,int upper_index,int constant_index,int artists_OR_songs);

// Helper function for quicksort that rearranges the items in an array into items < or > the chosen pivot, and returns the index of the pivot in the new state of the array
int pivot_split(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int lower_index,int upper_index,int constant_index,int artists_OR_songs);

// This function concatenates the artist name to their coressponding songs, while also adding tabs for the formatted output
void prep_strings_for_shuffle(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN]);

// Function to iterate thru the 3D array and load all the songs into a 2D array for shuffling, loads them twice to meet the specs for shuffled playlist
void load_shuffling_array(char arr[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],char arr_for_shuffling[24][MAX_LEN]);

// As described, shuffles a 2D array randomly
void fisher_yates_shuffle(char arr_for_shuffling[24][MAX_LEN],int len);

// As described, swaps the contents of 2 strings
void swap_strings(char str1[MAX_LEN],char str2[MAX_LEN]);

// This algorithm adds to the random shuffle by ensuring that duplicate songs are spaced at least 5 apart. It doesn't look where it puts songs when swapping with
// the front of the array as it nears the back, hence the valid_state fucntion to allow this function to run until valid state is achieved. Ususall just requires two
// iterations of the shuffled_strict function
void shuffled_strict(char array[24][MAX_LEN],int max_iterations);

// As described, checks if a 2D array satisfies the conditions given in the spec, namely duplicate songs being at least 5 songs apart
bool valid_state(char arr[24][MAX_LEN],int len);

// Function to get user input
void get_input(char array[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],char array_not4_sorting[MAX_ARTISTS][MAX_SONGS + 1][MAX_LEN],int frequency_of_songs_4artists[4]);



#endif /* FUNCTIONS_H_ */


