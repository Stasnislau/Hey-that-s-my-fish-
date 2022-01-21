#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "movement.h"
#include "placement.h"

// Bot level 1
// completly random bot, placement randomly, choosing penguins to move randomly, moving randomly

int bot12_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size)
{
    // srand(time(0));
    int place_counter = 0;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].fishes == 1)
            {
                placements[place_counter].x = j;
                placements[place_counter].y = i;
                place_counter++;
            }
        }
    }
    int placement_decision = (rand() % (place_counter));
    return placement_decision;
}
void bot_placement_execution(struct board_tile **board, struct player *players, struct bot_placement *placements, struct placement p, int curr_player, int placement_decision)
{
    p.to.x = placements[placement_decision].x;
    p.to.y = placements[placement_decision].y;
    board[p.to.y][p.to.x].occupied = players[curr_player - 1].id;
    players[curr_player - 1].fish_collected++; // show player's id on the board
    players[curr_player - 1].pen_not_placed--; // reduce number of penguins of current player after every successful placement
    board[p.to.y][p.to.x].fishes = 0;
}
int bot123_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player)
{
    int choosing_counter = 0;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].occupied == players[curr_player - 1].id)
            {
                if (((board[i + 1][j].fishes != 0) && ((board[i + 1][j].occupied == 0))) || ((board[i - 1][j].fishes != 0) && (board[i - 1][j].occupied == 0)) || ((board[i][j + 1].fishes != 0) && (board[i][j + 1].occupied == 0)) || ((board[i][j - 1].fishes != 0) && (board[i][j - 1].occupied == 0)))
                {
                    choice[choosing_counter].x = j;
                    choice[choosing_counter].y = i;
                    choosing_counter++;
                }
            }
        }
    }
    int penguin_decision = (rand() % (choosing_counter));
    return penguin_decision;
}
struct movement bot_choosing_execution(struct board_tile **board, struct player *players, struct bot_choosing *choice, struct movement m, int curr_player, int penguin_decision)
{
    m.from.x = choice[penguin_decision].x;
    m.from.y = choice[penguin_decision].y;
    return m;
}
int bot1_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    // srand(time(0));
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int movement_decision = (rand() % (movement_counter));
    return movement_decision;
}

// bot level 2
// Random placement, random choosing penguins, moving on tiles with 3 in prioritet, then on 2, then 1

int bot2_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    // srand(time(0));
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int *prior_tiles = calloc(movement_counter, sizeof(int)); // freed
    int prior_counter = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        if (board[mov_choice[i].y][mov_choice[i].x].fishes == 3)
        {
            prior_tiles[prior_counter] = i;
            prior_counter++;
        }
    }
    if (prior_counter != 0)
    {
        int preliminary_decision = (rand() % (prior_counter));
        int movement_decision = prior_tiles[preliminary_decision];
        free(prior_tiles);
        return movement_decision;
    }
    prior_counter = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        if (board[mov_choice[i].y][mov_choice[i].x].fishes == 2)
        {
            prior_tiles[prior_counter] = i;
            prior_counter++;
        }
    }
    if (prior_counter != 0)
    {
        int preliminary_decision = (rand() % (prior_counter));
        int movement_decision = prior_tiles[preliminary_decision];
        free(prior_tiles);
        return movement_decision;
    }
    int movement_decision = (rand() % (movement_counter));
    free(prior_tiles);
    return movement_decision;
}

// bot level 3
// places penguins accrording to the amount of tiles with 3 it would be able to reach, random choosing penguins, moving on tiles with 3 in prioritet, then on 2, then 1,
// escapes simple traps,places penguins accrording to the amount of tiles with 3 it would be able to reach
int bot34_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size)
{
    // srand(time(0));
    int place_counter = 0;
    // int position_counter = 0;
    int temp = 0;

    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].fishes == 1)
            {
                placements[place_counter].x = j;
                placements[place_counter].y = i;
                place_counter++;
            }
        }
    }
    int *potential_counter = calloc(place_counter, sizeof(int)); // freed
    for (int i = 0; i < place_counter; i++)
    {
        potential_counter[i] = 0;
    }
    for (int i = 0; i < place_counter; i++)
    {
        int up = 1;
        int down = 1;
        int right = 1;
        int left = 1;
        while ((board[placements[i].y + up][placements[i].x].fishes != 0) && (board[placements[i].y + up][placements[i].x].occupied == 0))
        {
            if (board[placements[i].y + up][placements[i].x].fishes == 3)
            {
                potential_counter[i]++;
            }
            up++;
        }
        while (board[placements[i].y - down][placements[i].x].fishes != 0 && (board[placements[i].y - down][placements[i].x].occupied == 0))
        {
            if (board[placements[i].y - down][placements[i].x].fishes == 3)
            {
                potential_counter[i]++;
            }
            down++;
        }
        while (board[placements[i].y][placements[i].x + right].fishes != 0 && board[placements[i].y][placements[i].x + right].occupied == 0)
        {
            if (board[placements[i].y][placements[i].x + right].fishes == 3)
            {
                potential_counter[i]++;
            }
            right++;
        }

        while (board[placements[i].y][placements[i].x - left].fishes != 0 && board[placements[i].y][placements[i].x - left].occupied == 0)
        {
            if (board[placements[i].y][placements[i].x - left].fishes == 3)
            {
                potential_counter[i]++;
            }
            left++;
        }
    }
    for (int i = 0; i < place_counter; i++)
    {
        if (potential_counter[i] > temp)
        {
            temp = potential_counter[i];
        }
    }
    for (int i = 0; i < place_counter; i++)
    {
        if (potential_counter[i] == temp)
        {
            temp = i;
            break;
        }
    }
    if (temp != 0)
    {
        int placement_decision = temp;
        return placement_decision;
    }
    else
    {
        for (int i = 0; i < place_counter; i++)
        {
            potential_counter[i] = 0;
        }
        for (int i = 0; i < place_counter; i++)
        {
            int up = 1;
            int down = 1;
            int right = 1;
            int left = 1;
            while (board[placements[i].y + up][placements[i].x].fishes != 0 && board[placements[i].y + up][placements[i].x].occupied == 0)
            {
                if (board[placements[i].y + up][placements[i].x].fishes == 2)
                {
                    potential_counter[i]++;
                }
                up++;
            }
            while (board[placements[i].y - down][placements[i].x].fishes != 0 && (board[placements[i].y - down][placements[i].x].occupied == 0))
            {
                if (board[placements[i].y - down][placements[i].x].fishes == 2)
                {
                    potential_counter[i]++;
                }
                down++;
            }
            while (board[placements[i].y][placements[i].x + right].fishes != 0 && board[placements[i].y][placements[i].x + right].occupied == 0)
            {
                if (board[placements[i].y][placements[i].x + right].fishes == 2)
                {
                    potential_counter[i]++;
                }
                right++;
            }
            while (board[placements[i].y][placements[i].x - left].fishes != 0 && board[placements[i].y][placements[i].x - left].occupied == 0)
            {
                if (board[placements[i].y][placements[i].x - left].fishes == 2)
                {
                    potential_counter[i]++;
                }
                left++;
            }
        }
        for (int i = 0; i < place_counter; i++)
        {
            if (potential_counter[i] > temp)
            {
                temp = potential_counter[i];
            }
        }
        for (int i = 0; i < place_counter; i++)
        {
            if (potential_counter[i] == temp)
            {
                temp = i;
                break;
            }
        }
        if (temp != 0)
        {
            int placement_decision = temp;
            return placement_decision;
        }
    }
    int placement_decision = (rand() % (place_counter));
    return placement_decision;
}
int bot3_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;
    int temp = 0;
    int temp1 = -1;
    int preliminary_decision = 0;

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int *amount_of_directions = calloc(movement_counter, sizeof(int)); // freed
    for (int i = 0; i < movement_counter; i++)
    {
        if (board[mov_choice[i].y][mov_choice[i].x].fishes != 0)
        {
            if ((board[mov_choice[i].y + 1][mov_choice[i].x].fishes != 0) && (mov_choice[i].y + 1 != m.from.y) && (mov_choice[i].x != m.from.x))
            {
                amount_of_directions[i]++;
            }
            if ((board[mov_choice[i].y - 1][mov_choice[i].x].fishes != 0) && (mov_choice[i].y - 1 != m.from.y) && (mov_choice[i].x != m.from.x))
            {
                amount_of_directions[i]++;
            }
            if ((board[mov_choice[i].y][mov_choice[i].x + 1].fishes != 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x + 1 != m.from.x))
            {
                amount_of_directions[i]++;
            }
            if ((board[mov_choice[i].y][mov_choice[i].x - 1].fishes != 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x - 1 != m.from.x))
            {
                amount_of_directions[i]++;
            }
        }
    }
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] > temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 3)
        {
            temp = amount_of_directions[i];
        }
    }
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] == temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 3)
        {
            temp1 = i;
        }
    }
    if (temp1 != -1)
    {
        int movement_decision = temp1;
        free(amount_of_directions);
        return movement_decision;
    }
    temp = 0;
    temp1 = -1;
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] > temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 2)
        {
            temp = amount_of_directions[i];
        }
    }
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] == temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 2)
        {
            temp1 = i;
        }
    }
    if (temp1 != -1)
    {
        int movement_decision = temp1;
        free(amount_of_directions);
        return movement_decision;
    }
    temp = 0;
    temp1 = -1;
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] > temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 1)
        {
            temp = amount_of_directions[i];
        }
    }
    for (int i = 0; i < movement_counter; i++)
    {
        if (amount_of_directions[i] == temp && board[mov_choice[i].y][mov_choice[i].x].fishes == 1)
        {
            temp1 = i;
        }
    }
    int movement_decision = temp1;
    free(amount_of_directions);
    return movement_decision;
}

// Bot level 4
// places penguins accrording to the amount of tiles with 3 it would be able to reach, chooses penguins with the least directions it go onto
// moves escaping more complicated traps
int bot4_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player)
{
    int choosing_counter = 0;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].occupied == players[curr_player - 1].id)
            {
                if (((board[i + 1][j].fishes != 0) && (board[i + 1][j].occupied == 0)) || ((board[i - 1][j].fishes != 0) && (board[i - 1][j].occupied == 0)) || ((board[i][j + 1].fishes != 0) && (board[i][j + 1].occupied == 0)) || ((board[i][j - 1].fishes != 0) && (board[i][j - 1].occupied == 0)))
                {
                    choice[choosing_counter].x = j;
                    choice[choosing_counter].y = i;
                    choosing_counter++;
                }
            }
        }
    }
    int *amount_of_directions = calloc(choosing_counter, sizeof(int)); // freed
    for (int i = 0; i < choosing_counter; i++)
    {
        if (board[choice[i].y + 1][choice[i].x].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y - 1][choice[i].x].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y][choice[i].x + 1].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y][choice[i].x - 1].fishes != 0)
        {
            amount_of_directions[i]++;
        }
    }
    int temp = amount_of_directions[0];
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_directions[i] < temp && amount_of_directions[i] != 1)
        {
            temp = amount_of_directions[i];
        }
    }
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_directions[i] == temp)
        {
            temp = i;
            int penguin_decision = temp;
            free(amount_of_directions);
            return penguin_decision;
        }
    }
    int penguin_decision = (rand() % (choosing_counter));
    free(amount_of_directions);
    return penguin_decision;
}
int bot4_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;
    int temp = -1; // amount of moves

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int *moves_possible = calloc(movement_counter, sizeof(int)); // freed
    for (int i = 0; i < movement_counter; i++)
    {
        up = 1;
        down = 1;
        right = 1;
        left = 1;
        while ((board[mov_choice[i].y + up][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y + up][mov_choice[i].x].occupied == 0) && (mov_choice[i].y + up != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            up++;
            moves_possible[i]++;
        }
        while ((board[mov_choice[i].y - down][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y - down][mov_choice[i].x].occupied == 0) && (mov_choice[i].y - down != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            down++;
            moves_possible[i]++;
        }
        while ((board[mov_choice[i].y][mov_choice[i].x + right].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x + right].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x + right != m.from.x))
        {
            right++;
            moves_possible[i]++;
        }
        while ((board[mov_choice[i].y][mov_choice[i].x - left].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x - left].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x - left != m.from.x))
        {
            left++;
            moves_possible[i]++;
        }
    }
    for (int i = 0; i < movement_counter; i++)
    {
        if (moves_possible[i] > temp)
        {
            temp = moves_possible[i];
        }
    }
    int *temp_ar = calloc(movement_counter, sizeof(int)); // freed
    int j = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        if (moves_possible[i] == temp)
        {
            temp_ar[j] = i;
            j++;
        }
    }
    if (j > 1)
    {
        int *board_prior = calloc(j, sizeof(int));
        int board_prior_counter = 0;
        for (int i = 0; i < j; i++)
        {
            if (board[mov_choice[temp_ar[i]].y][mov_choice[temp_ar[i]].x].fishes == 3)
            {
                board_prior[board_prior_counter] = i;
                board_prior_counter++;
            }
        }
        if (board_prior_counter != 0)
        {
            temp = (rand() % board_prior_counter);
            int movement_decision = temp_ar[board_prior[temp]];
            free(moves_possible);
            free(temp_ar);
            return movement_decision;
        }
        else
        {

            board_prior_counter = 0;
            for (int i = 0; i < j; i++)
            {
                if (board[mov_choice[temp_ar[i]].y][mov_choice[temp_ar[i]].x].fishes == 2)
                {
                    board_prior[board_prior_counter] = i;
                    board_prior_counter++;
                }
            }
            if (board_prior_counter != 0)
            {
                temp = (rand() % board_prior_counter);
                int movement_decision = temp_ar[board_prior[temp]];
                free(moves_possible);
                free(temp_ar);
                return movement_decision;
            }
            else
            {

                board_prior_counter = 0;
                for (int i = 0; i < j; i++)
                {
                    if (board[mov_choice[temp_ar[i]].y][mov_choice[temp_ar[i]].x].fishes == 1)
                    {
                        board_prior[board_prior_counter] = i;
                        board_prior_counter++;
                    }
                }
                temp = (rand() % board_prior_counter);
                int movement_decision = temp_ar[board_prior[temp]];
                free(moves_possible);
                free(temp_ar);
                return movement_decision;
            }
        }
    }
    else
    {
        for (int i = 0; i < movement_counter; i++)
        {
            if (moves_possible[i] == temp)
            {
                temp = i;
                break;
            }
        }
        int movement_decision = temp;
        free(moves_possible);
        free(temp_ar);
        return movement_decision;
    }
}

// Bot level 5
// places penguins accrording to the total amount of fish it would be able to reach, chooses penguins *IDK HOW*
// two options of movement: depending on how many players it is up against

int bot5_possible_placement(struct board_tile **board, struct player *players, struct bot_placement *placements, int x_size, int y_size, int curr_player)
{
    int place_counter = 0;
    int temp = 0;
    int temp1 = 0;

    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].fishes == 1)
            {
                placements[place_counter].x = j;
                placements[place_counter].y = i;
                place_counter++;
            }
        }
    }
    int *potential_counter = calloc(place_counter, sizeof(int)); // free
    for (int i = 0; i < place_counter; i++)
    {
        potential_counter[i] = 0;
    }
    for (int i = 0; i < place_counter; i++)
    {
        int up = 1;
        int down = 1;
        int right = 1;
        int left = 1;
        while ((board[placements[i].y + up][placements[i].x].fishes != 0) && (board[placements[i].y + up][placements[i].x].occupied == 0))
        {
            potential_counter[i] = potential_counter[i] + board[placements[i].y + up][placements[i].x].fishes;
            up++;
        }
        while (board[placements[i].y - down][placements[i].x].fishes != 0 && (board[placements[i].y - down][placements[i].x].occupied == 0))
        {
            potential_counter[i] = potential_counter[i] + board[placements[i].y - down][placements[i].x].fishes;
            down++;
        }
        while (board[placements[i].y][placements[i].x + right].fishes != 0 && board[placements[i].y][placements[i].x + right].occupied == 0)
        {
            potential_counter[i] = potential_counter[i] + board[placements[i].y][placements[i].x + right].fishes;
            right++;
        }

        while (board[placements[i].y][placements[i].x - left].fishes != 0 && board[placements[i].y][placements[i].x - left].occupied == 0)
        {
            potential_counter[i] = potential_counter[i] + board[placements[i].y][placements[i].x - left].fishes;
            left++;
        }
    }
    for (int i = 0; i < place_counter; i++)
    {
        if (potential_counter[i] > temp)
        {
            temp = potential_counter[i];
        }
    }
    int temp_counter = 0;
    for (int i = 0; i < place_counter; i++)
    {
        if (potential_counter[i] == temp)
        {
            temp1 = i;
            temp_counter++;
        }
    }
    if (temp_counter == 1)
    {
        int placement_decision = temp1;
        free(potential_counter);
        return placement_decision;
    }
    else
    {
        int *temp_ar = calloc(temp_counter, sizeof(int)); // freed
        temp_counter = 0;
        for (int i = 0; i < place_counter; i++)
        {
            if (potential_counter[i] == temp)
            {
                temp_ar[temp_counter] = i;
                temp_counter++;
            }
        }
        int *flag_ar = calloc(temp_counter, sizeof(int)); // freed
        for (int i = 0; i < temp_counter; i++)
        {
            int up = 1;
            int down = 1;
            int right = 1;
            int left = 1;
            int flag_wh = 0;
            while (flag_wh == 0)
            {
                if (board[placements[i].y + up][placements[i].x].fishes == 0 || board[placements[i].y + up][placements[i].x].occupied != 0)
                    flag_wh = 1;
                if ((board[placements[i].y + up][placements[i].x].occupied > 0) &&
                    (board[placements[i].y + up][placements[i].x].occupied != players[curr_player - 1].id))
                {
                    flag_ar[i]++;
                }
                up++;
            }
            flag_wh = 0;
            while (flag_wh == 0)
            {
                if (board[placements[i].y - down][placements[i].x].fishes == 0 || board[placements[i].y - down][placements[i].x].occupied != 0)
                    flag_wh = 1;
                if ((board[placements[i].y - down][placements[i].x].occupied > 0) &&
                    (board[placements[i].y - down][placements[i].x].occupied != players[curr_player - 1].id))
                {
                    flag_ar[i]++;
                }
                down++;
            }
            flag_wh = 0;
            while (flag_wh == 0)
            {
                if (board[placements[i].y][placements[i].x + right].fishes == 0 || board[placements[i].y][placements[i].x + right].occupied != 0)
                    flag_wh = 1;
                if ((board[placements[i].y][placements[i].x + right].occupied > 0) &&
                    (board[placements[i].y][placements[i].x + right].occupied != players[curr_player - 1].id))
                {
                    flag_ar[i]++;
                }
                right++;
            }
            flag_wh = 0;
            while (flag_wh == 0)
            {
                if (board[placements[i].y][placements[i].x - left].fishes == 0 || board[placements[i].y][placements[i].x - left].occupied != 0)
                    flag_wh = 1;
                if ((board[placements[i].y][placements[i].x - left].occupied > 0) &&
                    (board[placements[i].y][placements[i].x - left].occupied != players[curr_player - 1].id))
                {
                    flag_ar[i]++;
                }
                left++;
            }
        }
        temp = 0;
        temp1 = 0;
        int similar_pot_counter = 0;
        for (int i = 0; i < temp_counter; i++)
        {
            if (flag_ar[i] > temp)
            {
                temp = flag_ar[i];
            }
        }
        for (int i = 0; i < temp_counter; i++)
        {
            if (flag_ar[i] == temp)
            {
                temp1 = i;
                similar_pot_counter++;
            }
        }
        if (similar_pot_counter == 1)
        {
            int placement_decision = temp_ar[temp1];
            free(temp_ar);
            free(potential_counter);
            free(flag_ar);
            return placement_decision;
        }
        int *similar_ar = calloc(similar_pot_counter, sizeof(int)); // freed
        similar_pot_counter = 0;
        for (int i = 0; i < temp_counter; i++)
        {
            if (flag_ar[i] == temp)
            {
                similar_ar[similar_pot_counter] = i;
                similar_pot_counter++;
            }
        }
        temp = rand() % similar_pot_counter;
        int placement_decision = temp_ar[similar_ar[temp]];
        free(similar_ar);
        free(temp_ar);
        free(potential_counter);
        free(flag_ar);
        return placement_decision;
    }
} // ааа
int bot5_1_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player)
{
    int choosing_counter = 0;
    int temp = -1;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].occupied == players[curr_player - 1].id)
            {
                if (((board[i + 1][j].fishes != 0) && ((board[i + 1][j].occupied == 0))) || ((board[i - 1][j].fishes != 0) && (board[i - 1][j].occupied == 0)) || ((board[i][j + 1].fishes != 0) && (board[i][j + 1].occupied == 0)) || ((board[i][j - 1].fishes != 0) && (board[i][j - 1].occupied == 0)))
                {
                    choice[choosing_counter].x = j;
                    choice[choosing_counter].y = i;
                    choosing_counter++;
                }
            }
        }
    }
    int *amount_of_moves = calloc(choosing_counter, sizeof(int)); // freed
    int *block_potention = calloc(choosing_counter, sizeof(int)); // freed
    for (int i = 0; i < choosing_counter; i++)
    {
        int amount_of_directions = 0;
        int up = 1;
        int down = 1;
        int right = 1;
        int left = 1;
        while ((board[choice[i].y + up][choice[i].x].fishes != 0) && (board[choice[i].y + up][choice[i].x].occupied == 0))
        {
            amount_of_moves[i]++;
            if (board[choice[i].y + up + 1][choice[i].x].occupied != 0 && board[choice[i].y + up + 1][choice[i].x].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y + up + 2][choice[i].x].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up + 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up + 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y + up][choice[i].x + 1].occupied != 0 && board[choice[i].y + up][choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y + up + 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up][choice[i].x + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up - 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y + up][choice[i].x - 1].occupied != 0 && board[choice[i].y + up][choice[i].x - 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y + up + 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up - 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + up][choice[i].x - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            up++;
        }
        while (board[choice[i].y - down][choice[i].x].fishes != 0 && (board[choice[i].y - down][choice[i].x].occupied == 0))
        {
            amount_of_moves[i]++;
            if (board[choice[i].y - down - 1][choice[i].x].occupied != 0 && board[choice[i].y - down - 1][choice[i].x].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y - down - 2][choice[i].x].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down - 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down - 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y - down][choice[i].x + 1].occupied != 0 && board[choice[i].y - down][choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y - down - 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down][choice[i].x + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down + 1][choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y - down][choice[i].x - 1].occupied != 0 && board[choice[i].y - down][choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y - down - 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down + 1][choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - down][choice[i].x - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            down++;
        }
        while (board[choice[i].y][choice[i].x + right].fishes != 0 && board[choice[i].y][choice[i].x + right].occupied == 0)
        {
            amount_of_moves[i]++;
            if (board[choice[i].y + 1][choice[i].x + right].occupied != 0 && board[choice[i].y + 1][choice[i].x + right].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y + 1][choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 2][choice[i].x + right].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 1][choice[i].x + right - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y - 1][choice[i].x + right].occupied != 0 && board[choice[i].y + 1][choice[i].x + right].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y - 1][choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 2][choice[i].x + right].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 1][choice[i].x + right - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y][choice[i].x + right + 1].occupied != 0 && board[choice[i].y][choice[i].x + right + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y][choice[i].x + right + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 1][choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 1][choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            right++;
        }

        while (board[choice[i].y][choice[i].x - left].fishes != 0 && board[choice[i].y][choice[i].x - left].occupied == 0)
        {
            amount_of_moves[i]++;
            if (board[choice[i].y + 1][choice[i].x - left].occupied != 0 && board[choice[i].y + 1][choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y + 1][choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 1][choice[i].x - left + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 2][choice[i].x - left].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y - 1][choice[i].x - left].occupied != 0 && board[choice[i].y + 1][choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y - 1][choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 1][choice[i].x - left + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 2][choice[i].x - left].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            if (board[choice[i].y][choice[i].x - left - 1].occupied != 0 && board[choice[i].y][choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[choice[i].y][choice[i].x - left - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y + 1][choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[choice[i].y - 1][choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 35;
                else if (amount_of_directions == 2)
                    block_potention[i] += 10;
                else
                    block_potention[i] += 3;
            }
            left++;
        }
    }
    for (int i = 0; i < choosing_counter; i++)
    {
        if (block_potention[i] > temp)
            temp = block_potention[i];
    }
    int *same_potention = calloc(choosing_counter, sizeof(int)); // freed
    int same_potention_counter = 0;
    for (int i = 0; i < choosing_counter; i++)
    {
        if (block_potention[i] == temp)
        {
            same_potention[same_potention_counter] = i;
            same_potention_counter++;
        }
    }
    if (same_potention_counter == 1)
    {
        temp = same_potention[0];
        free(amount_of_moves);
        free(block_potention);
        free(same_potention);
        return temp;
    }
    temp = -1;
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_moves[same_potention[i]] > temp)
            temp = amount_of_moves[same_potention[i]];
    }
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_moves[same_potention[i]] == temp)
        {
            temp = same_potention[i];
            break;
        }
    }
    temp = same_potention[0];
    free(amount_of_moves);
    free(block_potention);
    free(same_potention);
    return temp;
}
int bot5_2_choosing_penguin(struct board_tile **board, struct player *players, struct bot_choosing *choice, int x_size, int y_size, int curr_player)
{
    int choosing_counter = 0;
    int temp = -1;
    for (int i = 0; i < y_size; i++)
    {
        for (int j = 0; j < x_size; j++)
        {
            if (board[i][j].occupied == players[curr_player - 1].id)
            {
                if (((board[i + 1][j].fishes != 0) && ((board[i + 1][j].occupied == 0))) || ((board[i - 1][j].fishes != 0) && (board[i - 1][j].occupied == 0)) || ((board[i][j + 1].fishes != 0) && (board[i][j + 1].occupied == 0)) || ((board[i][j - 1].fishes != 0) && (board[i][j - 1].occupied == 0)))
                {
                    choice[choosing_counter].x = j;
                    choice[choosing_counter].y = i;
                    choosing_counter++;
                }
            }
        }
    }
    int *amount_of_directions = calloc(choosing_counter, sizeof(int)); // freed
    for (int i = 0; i < choosing_counter; i++)
    {
        if (board[choice[i].y + 1][choice[i].x].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y - 1][choice[i].x].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y][choice[i].x + 1].fishes != 0)
        {
            amount_of_directions[i]++;
        }
        if (board[choice[i].y][choice[i].x - 1].fishes != 0)
        {
            amount_of_directions[i]++;
        }
    }
    int *amount_reacheble = calloc(choosing_counter, sizeof(int)); // freed
    for (int i = 0; i < choosing_counter; i++)
    {
        int amount_of_directions = 0;
        int up = 1;
        int down = 1;
        int right = 1;
        int left = 1;
        while ((board[choice[i].y + up][choice[i].x].fishes != 0) && (board[choice[i].y + up][choice[i].x].occupied == 0))
        {
            amount_reacheble[i] += board[choice[i].y + up][choice[i].x].fishes;
            up++;
        }
        while (board[choice[i].y - down][choice[i].x].fishes != 0 && (board[choice[i].y - down][choice[i].x].occupied == 0))
        {
            amount_reacheble[i] += board[choice[i].y - down][choice[i].x].fishes;
            down++;
        }
        while (board[choice[i].y][choice[i].x + right].fishes != 0 && board[choice[i].y][choice[i].x + right].occupied == 0)
        {
            amount_reacheble[i] += board[choice[i].y][choice[i].x + right].fishes;
            right++;
        }

        while (board[choice[i].y][choice[i].x - left].fishes != 0 && board[choice[i].y][choice[i].x - left].occupied == 0)
        {
            amount_reacheble[i] += board[choice[i].y][choice[i].x - left].fishes;
            left++;
        }
    }
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_reacheble[i] > temp)
            temp = amount_reacheble[i];
    }
    int *same_potention = calloc(choosing_counter, sizeof(int)); // free
    int same_potention_counter = 0;
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_reacheble[i] == temp)
            same_potention[same_potention_counter] = i;
        same_potention_counter++;
    }
    if (same_potention_counter == 1)
    {
        temp = same_potention[0];
        free(amount_reacheble);
        free(same_potention);
        return temp;
    }
    temp = 5;
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_directions[same_potention[i]] < temp)
            temp = amount_of_directions[same_potention[i]];
    }
    for (int i = 0; i < choosing_counter; i++)
    {
        if (amount_of_directions[same_potention[i]] == temp)
        {
            temp = same_potention[i];
            break;
        }
    }
    free(amount_of_directions);
    free(same_potention);
    return temp;
}
int bot5_1_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int *amount_of_moves = calloc(movement_counter, sizeof(int)); // free
    int *block_potention = calloc(movement_counter, sizeof(int)); // free
    for (int i = 0; i < movement_counter; i++)
    {
        int amount_of_directions = 0;
        int up = 1;
        int down = 1;
        int right = 1;
        int left = 1;
        while ((board[mov_choice[i].y + up][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y + up][mov_choice[i].x].occupied == 0))
        {
            amount_of_moves[i]++;
            if (board[mov_choice[i].y + up + 1][mov_choice[i].x].occupied != 0 && board[mov_choice[i].y + up + 1][mov_choice[i].x].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y + up + 2][mov_choice[i].x].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up + 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up + 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y + up][mov_choice[i].x + 1].occupied != 0 && board[mov_choice[i].y + up][mov_choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y + up + 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up][mov_choice[i].x + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up - 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y + up][mov_choice[i].x - 1].occupied != 0 && board[mov_choice[i].y + up][mov_choice[i].x - 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y + up + 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up - 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + up][mov_choice[i].x - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            up++;
        }
        while (board[mov_choice[i].y - down][mov_choice[i].x].fishes != 0 && (board[mov_choice[i].y - down][mov_choice[i].x].occupied == 0))
        {
            amount_of_moves[i]++;
            if (board[mov_choice[i].y - down - 1][mov_choice[i].x].occupied != 0 && board[mov_choice[i].y - down - 1][mov_choice[i].x].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y - down - 2][mov_choice[i].x].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down - 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down - 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y - down][mov_choice[i].x + 1].occupied != 0 && board[mov_choice[i].y - down][mov_choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y - down - 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down][mov_choice[i].x + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down + 1][mov_choice[i].x + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1) // ааа
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y - down][mov_choice[i].x - 1].occupied != 0 && board[mov_choice[i].y - down][mov_choice[i].x + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y - down - 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down + 1][mov_choice[i].x - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - down][mov_choice[i].x - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            down++;
        }
        while (board[mov_choice[i].y][mov_choice[i].x + right].fishes != 0 && board[mov_choice[i].y][mov_choice[i].x + right].occupied == 0)
        {
            amount_of_moves[i]++;
            if (board[mov_choice[i].y + 1][mov_choice[i].x + right].occupied != 0 && board[mov_choice[i].y + 1][mov_choice[i].x + right].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y + 1][mov_choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 2][mov_choice[i].x + right].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 1][mov_choice[i].x + right - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y - 1][mov_choice[i].x + right].occupied != 0 && board[mov_choice[i].y + 1][mov_choice[i].x + right].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y - 1][mov_choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 2][mov_choice[i].x + right].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 1][mov_choice[i].x + right - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y][mov_choice[i].x + right + 1].occupied != 0 && board[mov_choice[i].y][mov_choice[i].x + right + 1].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y][mov_choice[i].x + right + 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 1][mov_choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 1][mov_choice[i].x + right + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            right++;
        }

        while (board[mov_choice[i].y][mov_choice[i].x - left].fishes != 0 && board[mov_choice[i].y][mov_choice[i].x - left].occupied == 0)
        {
            amount_of_moves[i]++;
            if (board[mov_choice[i].y + 1][mov_choice[i].x - left].occupied != 0 && board[mov_choice[i].y + 1][mov_choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y + 1][mov_choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 1][mov_choice[i].x - left + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 2][mov_choice[i].x - left].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y - 1][mov_choice[i].x - left].occupied != 0 && board[mov_choice[i].y + 1][mov_choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y - 1][mov_choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 1][mov_choice[i].x - left + 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 2][mov_choice[i].x - left].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            if (board[mov_choice[i].y][mov_choice[i].x - left - 1].occupied != 0 && board[mov_choice[i].y][mov_choice[i].x - left].occupied != players[curr_player - 1].id)
            {
                amount_of_directions = 0;
                if (board[mov_choice[i].y][mov_choice[i].x - left - 2].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y + 1][mov_choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (board[mov_choice[i].y - 1][mov_choice[i].x - left - 1].fishes != 0)
                {
                    amount_of_directions++;
                }
                if (amount_of_directions == 0)
                    block_potention[i] += 1000;
                else if (amount_of_directions == 1)
                    block_potention[i] += 1;
            }
            left++;
        }
    }
    int temp = -1;
    for (int i = 0; i < movement_counter; i++)
    {
        if (block_potention[i] > temp)
            temp = block_potention[i];
    }
    int *same_potention = calloc(movement_counter, sizeof(int)); // freed
    int same_potention_counter = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        if (block_potention[i] == temp && block_potention[i] != 0)
        {
            same_potention[same_potention_counter] = i;
            same_potention_counter++;
        }
    }
    if (same_potention_counter == 1)
    {
        temp = same_potention[0];
        free(amount_of_moves);
        free(block_potention);
        free(same_potention);
        return temp;
    }
    //аа
    int *fish_possible = calloc(movement_counter, sizeof(int)); // freed
    struct bot_second_round *second_round = calloc(movement_counter * x_size * y_size, sizeof(struct bot_second_round));
    int second_round_counter = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        up = 1;
        while ((board[mov_choice[i].y + up][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y + up][mov_choice[i].x].occupied == 0) && (mov_choice[i].y + up != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y + up][mov_choice[i].x].fishes;
            second_round[second_round_counter].x = mov_choice[i].x;
            second_round[second_round_counter].y = mov_choice[i].y + up;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            up++;
        }
        down = 1;
        while ((board[mov_choice[i].y - down][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y - down][mov_choice[i].x].occupied == 0) && (mov_choice[i].y - down != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y - down][mov_choice[i].x].fishes;
            second_round[second_round_counter].x = mov_choice[i].x;
            second_round[second_round_counter].y = mov_choice[i].y - down;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            down++;
        }
        right = 1;
        while ((board[mov_choice[i].y][mov_choice[i].x + right].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x + right].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x + right != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y][mov_choice[i].x + right].fishes;
            second_round[second_round_counter].x = mov_choice[i].x + right;
            second_round[second_round_counter].y = mov_choice[i].y;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            right++;
        }
        left = 1;
        while ((board[mov_choice[i].y][mov_choice[i].x - left].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x - left].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x - left != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y][mov_choice[i].x - left].fishes;
            second_round[second_round_counter].x = mov_choice[i].x - left;
            second_round[second_round_counter].y = mov_choice[i].y;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            left++;
        }
    }
    for (int i = 0; i < second_round_counter; i++)
    {
        second_round[i].direct = 0;
        second_round[i].prof = 0;
    }
    for (int i = 0; i < second_round_counter; i++)
    {
        int dir_temp = -1;
        int dir_tile = 0;
        up = 1;
        down = 1;
        right = 1;
        left = 1;

        while ((board[second_round[i].y + up][second_round[i].x].fishes != 0) && (board[second_round[i].y + up][second_round[i].x].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up + up1][second_round[i].x].fishes != 0) && (board[second_round[i].y + up + up1][second_round[i].x].occupied == 0) && ((second_round[i].y + up + up1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + up1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y + up + up1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y + up + up1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1][second_round[i].x + 1].fishes != 0) && (second_round[i].y + up + up1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1][second_round[i].x - 1].fishes != 0) && (second_round[i].y + up + up1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y + up - down1][second_round[i].x].fishes != 0) && (board[second_round[i].y + up - down1][second_round[i].x].occupied == 0) && ((second_round[i].y + up - down1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up - down1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y + up - down1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y + up - down1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1][second_round[i].x + 1].fishes != 0) && (second_round[i].y + up - down1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1][second_round[i].x - 1].fishes != 0) && (second_round[i].y + up - down1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y + up][second_round[i].x + right1].fishes != 0) && (board[second_round[i].y + up][second_round[i].x + right1].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y + up + 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y + up - 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x + right1 + 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x + right1 - 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y + up][second_round[i].x - left1].fishes != 0) && (board[second_round[i].y + up][second_round[i].x - left1].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y + up + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y + up - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x - left1 + 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x - left1 - 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            up++;
        }
        while ((board[second_round[i].y - down][second_round[i].x].fishes != 0) && (board[second_round[i].y - down][second_round[i].x].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y - down + up1][second_round[i].x].fishes != 0) && (board[second_round[i].y - down + up1][second_round[i].x].occupied == 0) && ((second_round[i].y - down + up1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + up1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y - down + up1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y - down + up1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1][second_round[i].x + 1].fishes != 0) && (second_round[i].y - down + up1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1][second_round[i].x - 1].fishes != 0) && (second_round[i].y - down + up1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down - down1][second_round[i].x].fishes != 0) && (board[second_round[i].y - down - down1][second_round[i].x].occupied == 0) && ((second_round[i].y - down - down1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down - down1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y - down - down1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y - down - down1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1][second_round[i].x + 1].fishes != 0) && (second_round[i].y - down - down1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1][second_round[i].x - 1].fishes != 0) && (second_round[i].y - down - down1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y - down][second_round[i].x + right1].fishes != 0) && (board[second_round[i].y - down][second_round[i].x + right1].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y - down + 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y - down - 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x + right1 + 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x + right1 - 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y - down][second_round[i].x - left1].fishes != 0) && (board[second_round[i].y - down][second_round[i].x - left1].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y - down + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y - down - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x - left1 + 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x - left1 - 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            down++;
        }
        while ((board[second_round[i].y][second_round[i].x + right].fishes != 0) && (board[second_round[i].y][second_round[i].x + right].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up1][second_round[i].x + right].fishes != 0) && (board[second_round[i].y + up1][second_round[i].x + right].occupied == 0) && ((second_round[i].y + up1 != m.from.y) && (second_round[i].x + right != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up1 + 1][second_round[i].x + right].fishes != 0) && (second_round[i].y + up1 + 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1 - 1][second_round[i].x + right].fishes != 0) && (second_round[i].y + up1 - 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x + right + 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x + right + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x + right - 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x + right - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down1][second_round[i].x + right].fishes != 0) && (board[second_round[i].y - down1][second_round[i].x + right].occupied == 0) && ((second_round[i].y - down1 != m.from.y) && (second_round[i].x + right != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down1 + 1][second_round[i].x + right].fishes != 0) && (second_round[i].y - down1 + 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1 - 1][second_round[i].x + right].fishes != 0) && (second_round[i].y - down1 - 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x + right + 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x + right + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x + right - 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x + right - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y][second_round[i].x + right + right1].fishes != 0) && (board[second_round[i].y][second_round[i].x + right + right1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x + right + right1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x + right + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x + right + right1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x + right + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right + right1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x + right + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right + right1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x + right + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y][second_round[i].x + right - left1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x + right - left1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x + right - left1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right - left1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right - left1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            right++;
        }
        while ((board[second_round[i].y][second_round[i].x - left].fishes != 0) && (board[second_round[i].y][second_round[i].x - left].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left != m.from.x))) // left
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up1][second_round[i].x - left].fishes != 0) && (board[second_round[i].y + up1][second_round[i].x - left].occupied == 0) && ((second_round[i].y + up1 != m.from.y) && (second_round[i].x - left != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up1 + 1][second_round[i].x - left].fishes != 0) && (second_round[i].y + up1 + 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1 - 1][second_round[i].x - left].fishes != 0) && (second_round[i].y + up1 - 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x - left + 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x - left + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x - left - 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x - left - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down1][second_round[i].x - left].fishes != 0) && (board[second_round[i].y - down1][second_round[i].x - left].occupied == 0) && ((second_round[i].y - down1 != m.from.y) && (second_round[i].x - left != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down1 + 1][second_round[i].x - left].fishes != 0) && (second_round[i].y - down1 + 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1 - 1][second_round[i].x - left].fishes != 0) && (second_round[i].y - down1 - 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x - left + 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x - left + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x - left - 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x - left - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y][second_round[i].x - left + right1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left + right1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x - left + right1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x - left + right1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left + right1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left + right1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y][second_round[i].x - left - left1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x - left - left1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x - left - left1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left - left1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left - left1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            left++;
        }
        second_round[i].direct = dir_temp;
        dir_temp = -1;
    }
    int *first_prior_ar = calloc(second_round_counter, sizeof(int)); // free
    int first_prior_counter = 0;
    temp = -1;
    for (int i = 0; i < second_round_counter; i++)
    {
        if (second_round[i].prof > temp)
            temp = second_round[i].prof;
    }
    for (int i = 0; i < second_round_counter; i++)
    {
        if (second_round[i].prof == temp)
        {
            first_prior_ar[first_prior_counter] = second_round[i].id;
            first_prior_counter++;
        }
    }
    if (first_prior_counter == 1)
    {
        temp = first_prior_ar[0];
        free(fish_possible);
        free(first_prior_ar);
        return temp;
    }
    temp = -1;
    int *second_prior_ar = calloc(second_round_counter, sizeof(int)); // free
    int second_prior_counter = 0;
    for (int i = 0; i < first_prior_counter; i++)
    {
        if (second_round[first_prior_ar[i]].direct > temp)
            temp = second_round[first_prior_ar[i]].direct;
    }
    for (int i = 0; i < first_prior_counter; i++)
    {
        if (second_round[first_prior_ar[i]].direct == temp)
        {
            second_prior_ar[second_prior_counter] = first_prior_ar[i];
            second_prior_counter++;
        }
    }
    if (second_prior_counter == 1)
    {
        temp = second_prior_ar[0];
        free(amount_of_moves);
        free(block_potention);
        free(same_potention);
        free(fish_possible);
        free(first_prior_ar);
        free(second_prior_ar);
        return temp;
    }
    int *third_prior_ar = calloc(second_prior_counter, sizeof(int)); // free
    int third_prior_counter = 0;
    temp = -1;
    for (int i = 0; i < second_prior_counter; i++)
    {
        if (fish_possible[second_prior_ar[i]] > temp)
            temp = fish_possible[second_prior_ar[i]];
    }
    for (int i = 0; i < second_prior_counter; i++)
    {
        if (second_round[second_prior_ar[i]].direct == temp)
        {
            third_prior_ar[third_prior_counter] = second_prior_ar[i];
            second_prior_counter++;
        }
    }
    temp = third_prior_ar[0];
    free(fish_possible);
    free(amount_of_moves);
    free(block_potention);
    free(same_potention);
    free(first_prior_ar);
    free(second_prior_ar);
    free(third_prior_ar);
    return temp;
}
int bot5_2_choosing_movement(struct board_tile **board, struct player *players, struct movement m, struct bot_movement *mov_choice, int x_size, int y_size, int curr_player)
{
    int movement_counter = 0;
    int up = 1;
    int down = 1;
    int right = 1;
    int left = 1;

    while ((board[m.from.y + up][m.from.x].fishes != 0) && (board[m.from.y + up][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y + up);
        up++;
        movement_counter++;
    }
    while ((board[m.from.y - down][m.from.x].fishes != 0) && (board[m.from.y - down][m.from.x].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x);
        mov_choice[movement_counter].y = (m.from.y - down);
        down++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x + right].fishes != 0) && (board[m.from.y][m.from.x + right].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x + right);
        mov_choice[movement_counter].y = (m.from.y);
        right++;
        movement_counter++;
    }
    while ((board[m.from.y][m.from.x - left].fishes != 0) && (board[m.from.y][m.from.x - left].occupied == 0))
    {
        mov_choice[movement_counter].x = (m.from.x - left);
        mov_choice[movement_counter].y = (m.from.y);
        left++;
        movement_counter++;
    }
    int *fish_possible = calloc(movement_counter, sizeof(int)); // free
    struct bot_second_round *second_round = calloc(movement_counter * x_size * y_size, sizeof(struct bot_second_round));
    int second_round_counter = 0;
    for (int i = 0; i < movement_counter; i++)
    {
        up = 1;
        while ((board[mov_choice[i].y + up][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y + up][mov_choice[i].x].occupied == 0) && (mov_choice[i].y + up != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y + up][mov_choice[i].x].fishes;
            second_round[second_round_counter].x = mov_choice[i].x;
            second_round[second_round_counter].y = mov_choice[i].y + up;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            up++;
        }
        down = 1;
        while ((board[mov_choice[i].y - down][mov_choice[i].x].fishes != 0) && (board[mov_choice[i].y - down][mov_choice[i].x].occupied == 0) && (mov_choice[i].y - down != m.from.y) && (mov_choice[i].x != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y - down][mov_choice[i].x].fishes;
            second_round[second_round_counter].x = mov_choice[i].x;
            second_round[second_round_counter].y = mov_choice[i].y - down;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            down++;
        }
        right = 1;
        while ((board[mov_choice[i].y][mov_choice[i].x + right].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x + right].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x + right != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y][mov_choice[i].x + right].fishes;
            second_round[second_round_counter].x = mov_choice[i].x + right;
            second_round[second_round_counter].y = mov_choice[i].y;
            second_round_counter++;
            right++;
        }
        left = 1;
        while ((board[mov_choice[i].y][mov_choice[i].x - left].fishes != 0) && (board[mov_choice[i].y][mov_choice[i].x - left].occupied == 0) && (mov_choice[i].y != m.from.y) && (mov_choice[i].x - left != m.from.x))
        {
            fish_possible[i] += board[mov_choice[i].y][mov_choice[i].x - left].fishes;
            second_round[second_round_counter].x = mov_choice[i].x - left;
            second_round[second_round_counter].y = mov_choice[i].y;
            second_round[second_round_counter].id = i;
            second_round_counter++;
            left++;
        }
    }
    for (int i = 0; i < second_round_counter; i++)
    {
        int dir_temp = -1;
        int dir_tile = 0;
        up = 1;
        down = 1;
        right = 1;
        left = 1;

        while ((board[second_round[i].y + up][second_round[i].x].fishes != 0) && (board[second_round[i].y + up][second_round[i].x].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up + up1][second_round[i].x].fishes != 0) && (board[second_round[i].y + up + up1][second_round[i].x].occupied == 0) && ((second_round[i].y + up + up1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + up1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y + up + up1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y + up + up1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1][second_round[i].x + 1].fishes != 0) && (second_round[i].y + up + up1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up + up1][second_round[i].x - 1].fishes != 0) && (second_round[i].y + up + up1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y + up - down1][second_round[i].x].fishes != 0) && (board[second_round[i].y + up - down1][second_round[i].x].occupied == 0) && ((second_round[i].y + up - down1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up - down1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y + up - down1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y + up - down1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1][second_round[i].x + 1].fishes != 0) && (second_round[i].y + up - down1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - down1][second_round[i].x - 1].fishes != 0) && (second_round[i].y + up - down1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y + up][second_round[i].x + right1].fishes != 0) && (board[second_round[i].y + up][second_round[i].x + right1].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y + up + 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y + up - 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x + right1 + 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x + right1 - 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y + up][second_round[i].x - left1].fishes != 0) && (board[second_round[i].y + up][second_round[i].x - left1].occupied == 0) && ((second_round[i].y + up != m.from.y) && (second_round[i].x - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up + 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y + up + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up - 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y + up - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x - left1 + 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up][second_round[i].x - left1 - 1].fishes != 0) && (second_round[i].y + up != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            up++;
        }
        while ((board[second_round[i].y - down][second_round[i].x].fishes != 0) && (board[second_round[i].y - down][second_round[i].x].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y - down + up1][second_round[i].x].fishes != 0) && (board[second_round[i].y - down + up1][second_round[i].x].occupied == 0) && ((second_round[i].y - down + up1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + up1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y - down + up1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y - down + up1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1][second_round[i].x + 1].fishes != 0) && (second_round[i].y - down + up1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down + up1][second_round[i].x - 1].fishes != 0) && (second_round[i].y - down + up1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down - down1][second_round[i].x].fishes != 0) && (board[second_round[i].y - down - down1][second_round[i].x].occupied == 0) && ((second_round[i].y - down - down1 != m.from.y) && (second_round[i].x != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down - down1 + 1][second_round[i].x].fishes != 0) && (second_round[i].y - down - down1 + 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1 - 1][second_round[i].x].fishes != 0) && (second_round[i].y - down - down1 - 1 != m.from.y) && (second_round[i].x != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1][second_round[i].x + 1].fishes != 0) && (second_round[i].y - down - down1 != m.from.y) && (second_round[i].x + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - down1][second_round[i].x - 1].fishes != 0) && (second_round[i].y - down - down1 != m.from.y) && (second_round[i].x - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y - down][second_round[i].x + right1].fishes != 0) && (board[second_round[i].y - down][second_round[i].x + right1].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y - down + 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - 1][second_round[i].x + right1].fishes != 0) && (second_round[i].y - down - 1 != m.from.y) && (second_round[i].x + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x + right1 + 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x + right1 - 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y - down][second_round[i].x - left1].fishes != 0) && (board[second_round[i].y - down][second_round[i].x - left1].occupied == 0) && ((second_round[i].y - down != m.from.y) && (second_round[i].x - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down + 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y - down + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down - 1][second_round[i].x - left1].fishes != 0) && (second_round[i].y - down - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x - left1 + 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down][second_round[i].x - left1 - 1].fishes != 0) && (second_round[i].y - down != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            down++;
        }
        while ((board[second_round[i].y][second_round[i].x + right].fishes != 0) && (board[second_round[i].y][second_round[i].x + right].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right != m.from.x)))
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up1][second_round[i].x + right].fishes != 0) && (board[second_round[i].y + up1][second_round[i].x + right].occupied == 0) && ((second_round[i].y + up1 != m.from.y) && (second_round[i].x + right != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up1 + 1][second_round[i].x + right].fishes != 0) && (second_round[i].y + up1 + 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1 - 1][second_round[i].x + right].fishes != 0) && (second_round[i].y + up1 - 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x + right + 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x + right + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x + right - 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x + right - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down1][second_round[i].x + right].fishes != 0) && (board[second_round[i].y - down1][second_round[i].x + right].occupied == 0) && ((second_round[i].y - down1 != m.from.y) && (second_round[i].x + right != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down1 + 1][second_round[i].x + right].fishes != 0) && (second_round[i].y - down1 + 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1 - 1][second_round[i].x + right].fishes != 0) && (second_round[i].y - down1 - 1 != m.from.y) && (second_round[i].x + right != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x + right + 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x + right + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x + right - 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x + right - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y][second_round[i].x + right + right1].fishes != 0) && (board[second_round[i].y][second_round[i].x + right + right1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x + right + right1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x + right + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x + right + right1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x + right + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right + right1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x + right + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right + right1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x + right + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y][second_round[i].x + right - left1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x + right - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x + right - left1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x + right - left1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right - left1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x + right - left1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            right++;
        }
        while ((board[second_round[i].y][second_round[i].x - left].fishes != 0) && (board[second_round[i].y][second_round[i].x - left].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left != m.from.x))) // left
        {
            second_round[i].prof += board[second_round[i].y + up][second_round[i].x].fishes;
            int up1 = 1;
            int down1 = 1;
            int right1 = 1;
            int left1 = 1;
            while ((board[second_round[i].y + up1][second_round[i].x - left].fishes != 0) && (board[second_round[i].y + up1][second_round[i].x - left].occupied == 0) && ((second_round[i].y + up1 != m.from.y) && (second_round[i].x - left != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + up1 + 1][second_round[i].x - left].fishes != 0) && (second_round[i].y + up1 + 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1 - 1][second_round[i].x - left].fishes != 0) && (second_round[i].y + up1 - 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x - left + 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x - left + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y + up1][second_round[i].x - left - 1].fishes != 0) && (second_round[i].y + up1 != m.from.y) && (second_round[i].x - left - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                up1++;
            }
            while ((board[second_round[i].y - down1][second_round[i].x - left].fishes != 0) && (board[second_round[i].y - down1][second_round[i].x - left].occupied == 0) && ((second_round[i].y - down1 != m.from.y) && (second_round[i].x - left != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y - down1 + 1][second_round[i].x - left].fishes != 0) && (second_round[i].y - down1 + 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1 - 1][second_round[i].x - left].fishes != 0) && (second_round[i].y - down1 - 1 != m.from.y) && (second_round[i].x - left != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x - left + 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x - left + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - down1][second_round[i].x - left - 1].fishes != 0) && (second_round[i].y - down1 != m.from.y) && (second_round[i].x - left - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                down1++;
            }
            while ((board[second_round[i].y][second_round[i].x - left + right1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left + right1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left + right1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x - left + right1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x - left + right1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left + right1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left + right1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left + right1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left + right1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left + right1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                right1++;
            }
            while ((board[second_round[i].y][second_round[i].x - left - left1].fishes != 0) && (board[second_round[i].y][second_round[i].x - left1].occupied == 0) && ((second_round[i].y != m.from.y) && (second_round[i].x - left - left1 != m.from.x)))
            {
                dir_tile = 0;
                if ((board[second_round[i].y + 1][second_round[i].x - left - left1].fishes != 0) && (second_round[i].y + 1 != m.from.y) && (second_round[i].x - left - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y - 1][second_round[i].x - left - left1].fishes != 0) && (second_round[i].y - 1 != m.from.y) && (second_round[i].x - left1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left - left1 + 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left - left1 + 1 != m.from.x))
                {
                    dir_tile++;
                }
                if ((board[second_round[i].y][second_round[i].x - left - left1 - 1].fishes != 0) && (second_round[i].y != m.from.y) && (second_round[i].x - left - left1 - 1 != m.from.x))
                {
                    dir_tile++;
                }
                if (dir_temp < dir_tile)
                    dir_temp = dir_tile;
                left1++;
            }
            left++;
        }
        second_round[i].direct = dir_temp;
        dir_temp = -1;
    }
    int *first_prior_ar = calloc(second_round_counter, sizeof(int)); // free
    int first_prior_counter = 0;
    int temp = -1;
    for (int i = 0; i < second_round_counter; i++)
    {
        if (second_round[i].prof > temp)
            temp = second_round[i].prof;
    }
    for (int i = 0; i < second_round_counter; i++)
    {
        if (second_round[i].prof == temp)
        {
            first_prior_ar[first_prior_counter]=second_round[i].id;;
            first_prior_counter++;
        }
    }
    if (first_prior_counter == 1)
    {
        temp = first_prior_ar[0];
        free(fish_possible);
        free(first_prior_ar);
        return temp;
    }
    int *second_prior_ar = calloc(second_round_counter, sizeof(int)); // free
    int second_prior_counter = 0;
    for (int i = 0; i < first_prior_counter; i++)
    {
        if (second_round[first_prior_ar[i]].direct > temp)
            temp = second_round[first_prior_ar[i]].direct;
    }
    for (int i = 0; i < first_prior_counter; i++)
    {
        if (second_round[first_prior_ar[i]].direct == temp)
        {
            second_prior_ar[second_prior_counter] = first_prior_ar[i];
            second_prior_counter++;
        }
    }
    if (second_prior_counter == 1)
    {
        temp = second_prior_ar[0];
        free(fish_possible);
        free(first_prior_ar);
        free(second_prior_ar);
        return temp;
    }
    int *third_prior_ar = calloc(second_round_counter, sizeof(int)); // free
    int third_prior_counter = 0;
    temp = -1;
    for (int i = 0; i < second_prior_counter; i++)
    {
        if (fish_possible[second_prior_ar[i]] > temp)
            temp = fish_possible[second_prior_ar[i]];
    }
    for (int i = 0; i < second_prior_counter; i++)
    {
        if (second_round[second_prior_ar[i]].direct == temp)
        {
            third_prior_ar[third_prior_counter] = second_prior_ar[i];
            second_prior_counter++;
        }
    }
    temp = third_prior_ar[0];
    free(fish_possible);
    free(first_prior_ar);
    free(second_prior_ar);
    free(third_prior_ar);
    return temp;
}

/*



 * BOT GENERAL FUNCTIONS



*/
void execute_placement_bot(struct board_tile **board, int x, int y, struct player *players, int n, int curr_player)
{
    struct placement p;
    struct bot_placement *placements = (struct bot_placement *)malloc(x * y * sizeof(struct bot_placement));
    switch (players[curr_player - 1].bot_level)
    {
    case 1:
    {
        int placement_decision = bot12_possible_placement(board, players, placements, x, y);
        bot_placement_execution(board, players, placements, p, curr_player, placement_decision);
        break;
    }
    case 2:
    {
        int placement_decision = bot12_possible_placement(board, players, placements, x, y);
        bot_placement_execution(board, players, placements, p, curr_player, placement_decision);
        break;
    }
    case 3:
    {
        int placement_decision = bot34_possible_placement(board, players, placements, x, y);
        bot_placement_execution(board, players, placements, p, curr_player, placement_decision);
        break;
    }
    case 4:
    {
        int placement_decision = bot34_possible_placement(board, players, placements, x, y);
        bot_placement_execution(board, players, placements, p, curr_player, placement_decision);
        break;
    }
    case 5:
    {
        int placement_decision = bot5_possible_placement(board, players, placements, x, y, curr_player);
        bot_placement_execution(board, players, placements, p, curr_player, placement_decision);
        break;
    }
        // free the memory
        free(placements);
    }
}
struct movement bot_mov_choosing_execution(struct board_tile **board, struct player *players, struct bot_movement *mov_choice, struct movement m, int curr_player, int movement_decision)
{
    m.to.x = mov_choice[movement_decision].x;
    m.to.y = mov_choice[movement_decision].y;
    return m;
}

void execute_movement_bot(struct board_tile **board, int x, int y, struct player *players, int n, int curr_player)
{
    struct movement m;
    struct bot_choosing *choice = (struct bot_choosing *)calloc(x * y, sizeof(struct bot_choosing));
    struct bot_movement *mov_choice = (struct bot_movement *)calloc(x * y, sizeof(struct bot_movement));

    switch (players[curr_player - 1].bot_level)
    {
    case 1:
    {
        int penguin_decision = bot123_choosing_penguin(board, players, choice, x, y, curr_player);
        m = bot_choosing_execution(board, players, choice, m, curr_player, penguin_decision);
        int movement_decision = bot1_choosing_movement(board, players, m, mov_choice, x, y, curr_player);
        m = bot_mov_choosing_execution(board, players, mov_choice, m, curr_player, movement_decision);
        execute_movement(board, players, curr_player, m);
        break;
    }
    case 2:
    {
        int penguin_decision = bot123_choosing_penguin(board, players, choice, x, y, curr_player);
        m = bot_choosing_execution(board, players, choice, m, curr_player, penguin_decision);
        int movement_decision = bot2_choosing_movement(board, players, m, mov_choice, x, y, curr_player);
        m = bot_mov_choosing_execution(board, players, mov_choice, m, curr_player, movement_decision);
        execute_movement(board, players, curr_player, m);
        break;
    }
    case 3:
    {
        int penguin_decision = bot123_choosing_penguin(board, players, choice, x, y, curr_player);
        m = bot_choosing_execution(board, players, choice, m, curr_player, penguin_decision);
        int movement_decision = bot3_choosing_movement(board, players, m, mov_choice, x, y, curr_player);
        m = bot_mov_choosing_execution(board, players, mov_choice, m, curr_player, movement_decision);
        execute_movement(board, players, curr_player, m);
        break;
    }
    case 4:
    {
        int penguin_decision = bot4_choosing_penguin(board, players, choice, x, y, curr_player);
        m = bot_choosing_execution(board, players, choice, m, curr_player, penguin_decision);
        int movement_decision = bot4_choosing_movement(board, players, m, mov_choice, x, y, curr_player);
        m = bot_mov_choosing_execution(board, players, mov_choice, m, curr_player, movement_decision);
        execute_movement(board, players, curr_player, m);
        break;
    }
    case 5:
    {
        int active_player_counter = 0;
        int penguin_decision = -1;
        for (int i = 0; i < n; i++)
        {
            if (players[i].movement_status == 1)
                active_player_counter++;
        }
        if (active_player_counter < 3)
        {
            penguin_decision = bot5_1_choosing_penguin(board, players, choice, x, y, curr_player);
        }
        else
            penguin_decision = bot5_2_choosing_penguin(board, players, choice, x, y, curr_player);
        m = bot_choosing_execution(board, players, choice, m, curr_player, penguin_decision);
        int movement_decision = -1;
        if (active_player_counter < 3)
        {
            movement_decision = bot5_1_choosing_movement(board, players, m, mov_choice, x, y, curr_player); // should be changed to 5_1
        }
        else
        {
            movement_decision = bot5_2_choosing_movement(board, players, m, mov_choice, x, y, curr_player); // should be changed to 5_2
        }
        m = bot_mov_choosing_execution(board, players, mov_choice, m, curr_player, movement_decision);
        execute_movement(board, players, curr_player, m);
        break;
    }
        // free the memory
        free(choice);
        free(mov_choice);
    }
    // for tests 3: || 3 a 1 3 b 1 2 c 1 1 3 15 15 || 3 a 1 3 b 1 2 c 1 1 1 10 10
    // for tests 4: || 4 a 1 4 b 1 3 c 1 2 d 1 1 3 16 16 || 4 a 1 4 b 1 3 c 1 2 d 1 1 1 10 10
}
