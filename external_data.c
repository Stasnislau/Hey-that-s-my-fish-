//
// Created by timur on 1/3/22.
//
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
//#include "external_data.h"
#include "miscellaneous.h"
#include "map.h"
#include "defines.h"

// reads content of the file given in name, fills game state with date from a text file which path is specified in name
// arguments: game state, name of the file
// return: no value 
void read_board(struct GameState* gs, char* name) {
    FILE *fp;
    char buff[255];
    if ( (fp = fopen(name, "r")) == NULL) {
        fprintf(stderr, "[ERROR] Input file not found.\n");
        exit( TXT_FAILURE );
    }

    //reads the number of columns from the file and assigns it
    int board_y;
    fscanf(fp, "%d", &board_y);
    gs->board_y = board_y + 2;

    //reads the number of rows from the file and assigns it
    int board_x;
    fscanf(fp, "%d", &board_x);
    gs->board_x = board_x + 2;

    //assigning map to board_tile**
    gs->board = new_board(gs->board_x, gs->board_y);

    for(int i = 1; i < gs->board_y - 1; i++) {
        for (int j = 1; j < gs->board_x - 1; j++) {
            char tile[3];
            if (!fscanf(fp,"%s", tile)) 
                exit( TXT_FAILURE );
            gs->board[i][j].fishes = tile[0] - '0';
            gs->board[i][j].occupied = tile[1] - '0';
        }
    }

    for (int i = 0; i < gs->board_y; i++) {
        gs->board[i][0].fishes = 0;
        gs->board[i][0].occupied = 0;
    }
    for (int i = 0; i < gs->board_x; i++) {
        gs->board[0][i].fishes = 0;
        gs->board[0][i].occupied = 0;
    }

    for (int i = 0; i < gs->board_y; i++) {
        gs->board[i][gs->board_x - 1].fishes = 0;
        gs->board[i][gs->board_x - 1].occupied = 0;
    }

    for (int i = 0; i < gs->board_x; i++) {
        gs->board[gs->board_y - 1][i].fishes = 0;
        gs->board[gs->board_y - 1][i].occupied = 0;
    }
    //reading information about player and assigning it to players*
    int n = 0;  // number of players
    struct player* players_array = malloc(sizeof(struct player));
    while (!feof(fp)) {
        struct player pl;
        char player_name[32];
        int player_id, player_score;
        if (fscanf(fp, "%s %d %d", pl.full_name, &pl.id, &pl.fish_collected) == EOF) {
            break;
        }
        players_array = realloc(players_array, sizeof(struct player)*(n+1));
        players_array[n++] = pl;
    }
    gs->n = n;
    gs->players = players_array;

    fclose(fp);
}

// input parameters: struct GameState* state, char* name
// return: none
// writes a new file to location specified in name
void write_board(struct GameState* gs, char* name) {
    FILE *fp;
    fp = fopen(name, "w");

    //writing number of columns
    char board_y_array[255];
    int board_y = gs->board_y - 2;
    sprintf(board_y_array,"%d",board_y);
    fputs(board_y_array, fp);

    //space
    fputc(' ',fp);

    //writing number of rows
    char board_x_array[255];
    int board_x = gs->board_x - 2;
    sprintf(board_x_array,"%d",board_x);
    fputs(board_x_array, fp);

    //new line
    fputc('\n',fp);

    //writing the map
    for(int i = 1; i < gs->board_y - 1; i++) {
        for (int j = 1; j < gs->board_x - 1; j++) {
            int number_of_fishes = gs->board[i][j].fishes;
            int occupied = gs->board[i][j].occupied;

            fputc('0' + number_of_fishes,fp); //adding '0' to convert int to char
            fputc('0' + occupied,fp);

            fputc(' ', fp);
        }
        fputc('\n',fp);
    }

    //writing player's name, number of collected fish and id
    int number_of_players = gs->n;
    for (int i = 0; i < number_of_players; i++) {
        fputs(gs->players[i].full_name, fp);
        fputc(' ', fp);

        int player_id = gs->players[i].id;
        char player_id_array[255];
        sprintf(player_id_array,"%d",player_id);
        fputs(player_id_array,fp);
        fputc(' ', fp);
        
        int fish_collected = gs->players[i].fish_collected;
        char fish_collected_array[255];
        sprintf(fish_collected_array,"%d",fish_collected);
        fputs(fish_collected_array,fp);
        fputc('\n', fp);
    }

    fclose(fp);
}

