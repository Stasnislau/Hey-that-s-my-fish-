#ifndef MOVFUNCTIONS
#define MOVFUNCTIONS
// for a given state of the game, decides if movement phase should be stopped = none of the players can move one of their penguins
// arguments: board, array of players
// returns: 0 if none of the players can move one of their penguins, 1 otherwise 
int movement_game_status(struct board_tile** board, struct player* players, int amount_of_players);

// for a given state of the game, decides if current player can move one of their penguins 
// arguments: board, array of players and its x and y dims, array of players and the number of players n, id of current players
// returns: 1 if current players can move one of their penguins, 0 otherwise
int movement_possible(struct board_tile** board, int x, int y, struct player* players, int curr_player);

// decides if the movement m is possible = origin tile is occupied by one of current player's penguins, ther is no other penguins on a second tile and secone tile must be an ice floe
// agruments: movement m, current player number
// returns: 1 if movement is valid, 0 otherwise
int valid_movement(struct board_tile** board, struct player* players, struct movement m, int curr_player);

// based on the premise that movement m is valid, places the penguin on board at coordinates specified in m, remove the ice floe the penguin was standing on, update score of current player
// arguments: board, array of players, current player, valid movement
// returns: no value
void execute_movement(struct board_tile** board, struct player* players, int curr_player, struct movement m);

#endif
