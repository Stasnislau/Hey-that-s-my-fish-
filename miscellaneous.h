#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H
// chooses the first player to start a game
// arguments: number of players
// returns: random number from range 0..n-1
int choose_first_player(int n);

// changes index of curr_player at given memory adress, for example (curr_player+1)%n
// arguments: address to current player index, number of players in the game
// returns: no value
void next_player(int *curr_player, int n);

// check if the movmeent is not composed only of values of -1
// arguments: movement
// return: 1 or 0
int movement_null(struct movement m);
// checks if cords used in functions move beoynd the boarders of the map
int coords_checker(int x, int y, int x_check, int y_check);

// (re)allocate memeory block for an array of players
// arguments: pointer to array to players, number of players
// returns: an address to memory block with the array 
void *new_players(struct player *players, int n);

// returns: 2D array of dimensions x, y
// IMPORTANT! board[i][j], where i<y and j<x
struct board_tile** new_board(int x, int y);

// frees memory takes by the 2D array
void free_board(struct board_tile** board, int x, int y);

// frees memory occupied by state and its arrays
void free_game_state(struct GameState* state);
// To-do
void placement_init();
// sets movment_status of each players
// arguemtns: board, its x and y sizes, array of players and its length n
void movement_init(struct board_tile** board, int x, int y, struct player* players, int n);

// TO-DO
void init_game();
void end_game();
#endif
