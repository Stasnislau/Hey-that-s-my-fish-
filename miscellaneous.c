#include "structures.h"
#include "miscellaneous.h"
#include <stdlib.h>
#include <stdio.h>

int choose_first_player(int n) {
	int first_player = 1;
	return first_player;
}

void next_player(int* curr_player, int n) {
	*curr_player = (*curr_player - 1 + 1) % n + 1;
}

void placement_init() {
#if INTERACTIVE_MODE
    printf("-------------------\n");        
    printf("| PLACEMENT PHASE |\n");    
    printf("-------------------\n");    
#endif
}

void movement_init(struct board_tile** board, int x, int y, struct player* players, int n) {
#if INTERACTIVE_MODE
    printf("------------------\n");        
    printf("| MOVEMENT PHASE |\n");    
    printf("------------------\n");    
#endif
    int i, j;
    for (i=1; i<y-1; ++i) 
        for (j=1; j<x-1; ++j) 
            if (board[i][j].occupied) 
                if (board[i-1][j].fishes || board[i][j-1].fishes || board[i+1][j].fishes || board[i][j+1].fishes)
                    players[board[i][j].occupied-1].movement_status = 1;
}

int movement_null(struct movement m) {
    return m.from.x == -1 || m.from.y == -1 || m.to.x == -1 || m.to.y == -1;
}
int coords_checker(int x, int y, int x_check, int y_check)
    {
        if ((x_check < 0) || (y_check < 0) || (x_check > x - 1) || (y_check > y - 1))
            return 0;
        else
            return 1;
    }

void *new_players(struct player *players, int n) {
    return realloc(players, sizeof(struct player)*n);
}

// IMPORTANT! in 2D array of the map first [] is for y, second [] is for x
struct board_tile** new_board(int x, int y) {
    struct board_tile** board = (struct board_tile**)malloc(y * sizeof(struct board_tile*));
    int i;
    for (i = 0; i < y; i++)
        board[i] = (struct board_tile*)malloc(x * sizeof(struct board_tile));

    return board;
}

void free_board(struct board_tile** board, int x, int y) {
    int i;
    for (i = 0; i < y; i++)
        free(board[i]);

    free(board);
}

void free_game_state(struct GameState* state) {
    free(state->players);
    free_board(state->board, state->board_x, state->board_y);
    free(state);
}

void init_game() {}
void end_game() {}
