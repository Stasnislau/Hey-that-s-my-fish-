#ifndef PLCFUNCTIONS
#define PLCFUNCTIONS
// check if there is left some penguins and if there is left some tiles with 1 fish
// arguments: board, array of players and its size
// returns: 1 if number of penguins equals 0; 0 otherwise 
int placement_game_status(struct board_tile** board, int x, int y, struct player* players, int amount_of_players);

// check if current_player has penguins and if board has tiles with 1 fish
// arguments: board and its x and y size, array of players and its size, current player
// returns: 1 if current players has penguins, 0 otherwise
int placement_possible(struct board_tile** board, int x, int y, struct player* players, int curr_player);

// check if player entered valid coordinate
// arguments: board, coordinates
// returns 1 if coords valid, 0 otherwise
int valid_placement(struct board_tile** board, int x, int y, struct placement p);

// based on the premise that placement p is valid, places the penguin on board at coordinates specified in p, updates score of current player
// arguments: board, array of players, current player, valid placement
// returns: no value
void execute_placement(struct board_tile** board, struct player* players, int curr_player, struct placement p);
#endif



/* // asks user for coordinates of placement of one of their penguins
// arguments: none
// returns: placement type 
struct placement get_placement(); */
