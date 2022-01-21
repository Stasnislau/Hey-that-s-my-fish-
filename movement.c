#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structures.h"
#include "movement.h"


int movement_game_status(struct board_tile **board, struct player *players, int amount_of_players) // check if there are tiles left to go onto
{
    int status_counter = 0;
    int status = 1;
    for (int i = 0; i < amount_of_players; i++)
    {
        if (players[i].movement_status == 0)
        {
            status_counter++;
        }
    }
    if (status_counter == amount_of_players)
    {
        status = 0;
    }
    return status;
}
int movement_possible(struct board_tile **board, int x, int y, struct player *players, int curr_player) // check if the player has a tile to go onto
{
    int id = players[curr_player - 1].id;
    int result = 0;
    if (players[curr_player - 1].movement_status == 1)
    {
        for (int j = 1; j < x - 1; j++)
        {
            for (int i = 1; i < y - 1; i++)
                if (board[i][j].occupied == id)
                {
                    if (((board[i + 1][j].fishes != 0) && ((board[i + 1][j].occupied == 0))) || ((board[i - 1][j].fishes != 0) && (board[i - 1][j].occupied == 0)) || ((board[i][j + 1].fishes != 0) && (board[i][j + 1].occupied == 0)) || ((board[i][j - 1].fishes != 0) && (board[i][j - 1].occupied == 0)))
                    {
                        // printf("yes\n");
                        result = 1;
                        return result;
                    }
                }
        }
        players[curr_player - 1].movement_status = 0;
    }
    return result;
}
int valid_movement(struct board_tile **board, struct player *players, struct movement m, int curr_player) // check if it is possible to move onto this tile
{
    int flag = 0;
    if (board[m.from.y][m.from.x].occupied == players[curr_player - 1].id)
    {
        if ((m.from.x == m.to.x) && (m.from.y == m.to.y))
        {
        }
        else
        {
            if ((m.from.x == m.to.x) || (m.from.y == m.to.y))
            {
                if (board[m.to.y][m.to.x].fishes != 0)
                {
                    flag = 1;
                    if (m.from.x == m.to.x)
                    {
                        for (int i = 1; i <= (abs(m.from.y - m.to.y)); i++)
                        {
                            if ((m.from.y - m.to.y) > 0)
                            {
                                if ((board[m.from.y - i][m.to.x].fishes == 0))
                                {
                                    flag = 0;
                                }
                            }
                            else
                            {
                                if (board[m.from.y + i][m.to.x].fishes == 0)
                                {
                                    flag = 0;
                                }
                            }
                        }
                    }
                    else
                    {
                        for (int i = 1; i <= (abs(m.from.x - m.to.x)); i++)
                        {
                            if ((m.from.x - m.to.x) > 0)
                            {
                                if ((board[m.from.y][m.from.x - i].fishes == 0))
                                {
                                    flag = 0;
                                }
                            }
                            else
                            {
                                if (board[m.from.y][m.from.x + i].fishes == 0)
                                {
                                    flag = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return flag;
}
void execute_movement(struct board_tile **board, struct player *players, int curr_player, struct movement m) // move the penguin to a tile, collect fish, remove the tile the penguin was on before
{
    board[m.from.y][m.from.x].occupied = 0;
    board[m.to.y][m.to.x].occupied = players[curr_player - 1].id;
    players[curr_player - 1].fish_collected = players[curr_player - 1].fish_collected + board[m.to.y][m.to.x].fishes;
    board[m.to.y][m.to.x].fishes = 0;
}

