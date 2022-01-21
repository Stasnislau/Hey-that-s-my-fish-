#ifndef MAPFUNCTIONS
#define MAPFUNCTIONS
// displays the board to command line
void show_board(struct board_tile** board, int x, int y, struct player* players);
// each tile for the board is filled with new values, with at least n ice floes with 1 fish on them
// arguments: board, board's x and y dimension
// returns: -1 if it is imposible to generate a board (for example more players than the number of tiles, otherwise 1
void generate_board(struct board_tile** board, int x, int y, int n);
// checks if there are enough tiles with 1 fish on it for the game to be playable 
void board_gen_check(struct board_tile **board,struct player* players, int x_size, int y_size,int n);
#endif
