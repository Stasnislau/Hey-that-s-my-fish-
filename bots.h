#ifndef BOTS
#define BOTS
// find which tiles the bot can place its penguins on
int bot12_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size);
// place bot's penguins
void bot_placement_execution(struct board_tile **board, struct player *players, struct bot_placement *placements, struct placement p, int curr_player, int place_counter);
// find all penguins the bot can move and store them in an array
int bot123_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player);
// choose penguin which the bot will operate next and store penguins cords
struct movement bot_choosing_execution(struct board_tile **board, struct player *players, struct bot_choosing *choice, struct movement m, int curr_player, int penguin_decision);
// find all the tiles the penguin could move onto
int bot1_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
// apply the tile the bot choose to go onto
struct movement bot_mov_choosing_execution(struct board_tile **board, struct player *players, struct bot_movement *mov_choice, struct movement m, int curr_player, int movement_decision);
// executes the placement of the bot, changes values on the board - board is passed by reference
void execute_placement_bot(struct board_tile **board, int x, int y, struct player *players, int n, int curr_player);
// executes the movement of the bot, changes values on the board - board is passed by reference
void execute_movement_bot(struct board_tile **board, int x, int y, struct player *players, int n, int curr_player);
// choosing a place for a penguin in the placement phase, used by bots with 3rd and 4th levels of difficulty
int bot34_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size);
// choosing a tile for a penguin to move the movement phase, used by bot with 2nd level of difficulty
int bot2_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
// choosing a tile for a penguin to move the movement phase, used by bot with 3rd level of difficulty
int bot3_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
// choosing a tile for a penguin to move the movement phase, used by bot with 4th level of difficulty
int bot4_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player);
// choosing a tile for a penguin to move the movement phase, used by bot with 4th level of difficulty
int bot4_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
// placement of penguins by the 5th bot
int bot5_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size, int curr_player);
// choosing penguins to move by the 5th bot in case of being up againts only 1 player
int bot5_1_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player);
// choosing penguins to move by the 5th bot in case of being up againts more than 1 player
int bot5_2_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player);
// choosing penguins to move by the 5th bot in case of being up againts only 1 player
int bot5_1_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
// choosing penguins to move by the 5th bot in case of being up againts more than 1 player
int bot5_2_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player);
#endif
