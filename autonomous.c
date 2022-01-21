//
// Created by timur on 1/3/22.
//
#include "structures.h"
#include "defines.h"
#include "bots.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void execute_autonomous_command(struct GameState* state, int argc, char **argv) {

}

void invalid_cla_check(int argc, char **argv) {
	if (argc == 2) {
		if (strcmp(argv[1], "name") != 0) {
			fprintf(stderr, "[ERROR] Invalid command arguments! For the program to return player name first argument should be name.\n");
            exit( CLA_FAILURE );
        }
	}
	//placement
	else if (argc == 5) {
		if (strcmp(argv[1], "phase=placement") != 0) {
			fprintf(stderr, "[ERROR] Invalid command arguments! First argument is should be phase=placement.Possibly too many arguments.\n");
            exit( CLA_FAILURE );
		}
		char* nptr = strstr(argv[2], "penguins=");
		if (nptr == NULL) {
			fprintf(stderr, "[ERROR] Invalid command arguments! The number of penguins is incorrect!\n");
            exit( CLA_FAILURE );
		}
	}
	//movement
	else if (argc == 4) {
		if (strcmp(argv[1], "phase=movement") != 0) {
			fprintf(stderr, "[ERROR]Invalid command arguments! First argument is should be phase=movement.Possibly too few arguments.\n");
            exit( CLA_FAILURE );
		}
	}
    else {
        fprintf(stderr, "[ERROR]Invalid command arguments!\n");
        exit( CLA_FAILURE );
    }
}

int find_id_by_name(struct player* players, int n, char *nick) {
    for (int i=0; i<n; ++i) {
        if (strcmp(players[i].full_name, nick) == 0)
            return players[i].id;
    }
    return 0;
}

void add_new_player(struct player** players, int *n, int id, char name, char *full_name, int fish_collected, int penguins, int pen_not_placed, int movement_status, int bot, int bot_level) {
    *players = realloc(*players, sizeof(struct player)*(*n+1));
    if (*players == NULL)
        exit( MEMORY_FAILURE );
    (*players)[*n].id = id;
    (*players)[*n].name = name;
    sscanf(full_name, "%s", (*players)[*n].full_name);
    (*players)[*n].fish_collected = fish_collected;
    (*players)[*n].penguins = penguins;
    (*players)[*n].pen_not_placed = pen_not_placed;
    (*players)[*n].movement_status = movement_status;
    (*players)[*n].bot = bot;
    (*players)[*n].bot_level = bot_level;
    (*n)++; 
}

int next_free_id(struct player* players, int n) {
    int ids[256];
    int i;
    for (i=0; i<256; ++i)
        ids[i] = 0;
    for (i=0; i<n; ++i) {
        ids[players[i].id] = 1;
    }
    for (i=1; i<7; ++i)
        if (ids[i] == 0)
            return i;
    return 0;
}
