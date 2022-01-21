#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
void generate_board(struct board_tile **board, int x_size, int y_size,int n)
{
    if (x_size < 6 && y_size < 6)
        for (int i = 0; i < y_size; i++) // Map generation
        {
            for (int j = 0; j < x_size; j++)
            {
                board[i][j].fishes = (rand() % 3 + 1); // random value for fish on a tile
                board[i][j].occupied = 0;
                if ((j == 0) || (j == (x_size - 1)) || (i == 0) || (i == (y_size - 1)))
                {
                    board[i][j].fishes = 0; // making tiles on the perimetr ocean
                }
            }
        }
    else
    {
        int center_x, center_y, radius;
        center_x = x_size - (x_size / 2);
        center_y = y_size - (y_size / 2);
        if (center_x > center_y)
        {
            radius = center_x;
        }
        else
        {
            radius = center_y;
        }
        for (int i = 0; i < y_size; i++) // Map generation for big maps
        {
            for (int j = 0; j < x_size; j++)
            {
                int caser = (rand() % 3 + 1);
                float mod = 0;
                switch (caser)
                {
                case 1:
                    mod = 1;
                    break;
                case 2:
                    mod = 0.9;
                    break;
                case 3:
                    mod = 0.85;
                    break;
                }
                board[i][j].fishes = 0; // random value for fish on a tile
                board[i][j].occupied = 0;
                if ((((i - center_y) * (i - center_y)) + (j - center_x) * (j - center_x)) <= radius * radius * mod * mod)
                {
                    board[i][j].fishes = (rand() % 3 + 1);
                }
                if ((j == 0) || (j == (x_size - 1)) || (i == 0) || (i == (y_size - 1)))
                {
                    board[i][j].fishes = 0; // making tiles on the perimetr ocean
                }
            }
        }
    }
}
void show_board(struct board_tile **board, int x_size, int y_size, struct player* players)
{
    printf("   ");
    for (int j = 0; j < x_size; j++)
    {
        printf("%4d", j); // x counter
        if (j == x_size - 1)
        {
            printf("\n");
        }
    }
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            int occupied = board[i][j].occupied;
            int fishes = board[i][j].fishes;
            if ((i == 0) && (j == 0))
            {
                printf("%-4d", j); // first line, index
                int occupied = board[i][j].occupied;
                int fishes = board[i][j].fishes;
                if (occupied != 0)
                    printf("|- %c", players[occupied].name);
                else if (occupied == 0 && fishes == 0)
                    printf("|   ");
                else
                    printf("|%d -", fishes);
            }
            else
            {
                if (occupied != 0)
                    printf("|- %c", players[occupied-1].name);
                else if (occupied == 0 && fishes == 0)
                    printf("|   ");
                else
                    printf("|%d -", fishes);
            }
            if (j == x_size - 1)
            {
                printf("|\n");
                if (i != (y_size - 1))
                {
                    printf("%-4d", i + 1);
                }
            }
        }
    }
}
void board_gen_check(struct board_tile **board, struct player *players, int x_size, int y_size, int n)
{
    int one_counter = 0;
    int zero_counter = 0;
    int x_ran = 0;
    int y_ran = 0;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].fishes == 0)
            {
                zero_counter++;
            }
        }
    }
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].fishes == 1)
            {
                one_counter++;
            }
        }
    }
    while (one_counter < n * players[0].penguins)
    {
        y_ran = rand() % (y_size - 2) + 1;
        x_ran = rand() % (x_size - 2) + 1;
        if ((board[y_ran][x_ran].fishes != 1) && (board[y_ran][x_ran].fishes != 0))
        {
            board[y_ran][x_ran].fishes = 1;
            one_counter++;
        }
    }
}
