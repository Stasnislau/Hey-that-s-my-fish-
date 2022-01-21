//
// Created by timur on 12/5/21.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "command_line_ui.h"

/*
input parameters: none
return: integer
this function asks a user for an input and returns an integer for number of players.
*/
int get_nbr_of_players() {
    int number_of_players;
    printf("Enter the number of players(from 1 to 9):");
    scanf("%i", &number_of_players);
    while (number_of_players < 1 || number_of_players >= 9) {
        printf("Wrong number of players. Please try again:");
        scanf("%i", &number_of_players);
    }
    return number_of_players;

}

/*
input parameters: none
return: integer
this function asks a user for an input and returns an integer for number of penguins.
*/
int get_nbr_of_penguins() {
    int number_of_penguins;
    printf("Enter the number of penguins(from 1 to 5):");
    scanf("%i", &number_of_penguins);
    while (number_of_penguins < 1 || number_of_penguins >= 5) {
        printf("Wrong number of penguins. Please try again:");
        scanf("%i", &number_of_penguins);
    }
    return number_of_penguins;
}

/*
input parameters: struct player* players, int number_of_players
return: none
this function gets an array and number of players as an input and asks each player for name, simultaneously assigning names to array.
*/
void init_players(struct player* players, int number_of_players) {
    int i,bot,bot_dif;
    for (i = 0; i < number_of_players; i++) {
        char ch;
        printf("Enter the name of the %ist player(only one character):", i + 1);
        scanf(" %c", &ch);
        while ((ch < 'A' || ch > 'z') || (check_if_exists(players,ch,i) == 0)) {
            printf("Invalid name, try again:");
            scanf("%c", &ch);
        }
        
        bot = check_if_ai();
        if(bot != 0)
        {
            bot_dif = get_difficulty_level();
        }
        else
        {
            bot_dif = 0;
        }
        // assigning initial values
        players[i].id = i+1;
        players[i].name = ch;
        players[i].fish_collected = 0;
        players[i].movement_status = 0;
        players[i].bot = bot;
        players[i].bot_level = bot_dif;
    }
    int penguins;
    printf("Amount of penguins each players has: ");
    scanf("%d", &penguins);
    for (i = 0; i < number_of_players; i++) {
        players[i].penguins = penguins;
        players[i].pen_not_placed = penguins;
    }
}
//input parameters: pointer to array's first index, name of current player and number of players
//returns: 1 if this name doesn't exist, 0 if it does
//check if the name already exists in array
int check_if_exists(struct player* players,char ch,int number_of_players) {
    for (int i = 0; i < number_of_players; i++) {
        if(players[i].name == ch) {
            return 0;
        }
    }
    return 1;
}

/*
input parameters: none
return: integer
this function asks a user for number of columns of a board.
*/
int get_x_dimension() {
    int x;
    printf("Enter how many columns you want in the board(from 2 to 16):");
    scanf("%i", &x);
    while (x < 2 || x > 16) {
        printf("Wrong number of columns. Please try again:");
        scanf("%i", &x);
    }
    return x;
}

/*
input parameters: none
return: integer
this function asks a user for number of rows of a board.
*/
int get_y_dimension() {
    int y;
    printf("Enter how many rows you want in the board(from 2 to 16):");
    scanf("%i", &y);
    while (y < 2 || y > 16) {
        printf("Wrong number of rows. Please try again:");
        scanf("%i", &y);
    }
    return y;
}

/*
input parameters: int number_of_columns, int number_of_rows
return: movement type
this function asks a user for a movement and returns it.
*/
struct movement get_movement(int number_of_columns, int number_of_rows) {
    int fromX, fromY, toX, toY;
    printf("Enter x-coordinate you want to move your penguin from:");
    scanf("%i",&fromX);
    while (fromX > number_of_columns - 1 || fromX < 0) {
        printf("Wrong coordinates, please try again:");
        printf("Enter x-coordinate you want to move your penguin from:");
        scanf("%i", &fromX);
    }

    printf("Enter y-coordinate you want to move your penguin from:");
    scanf("%i",&fromY);
    while (fromY > number_of_rows - 1 || fromY < 0) {
        printf("Wrong coordinates, please try again:");
        printf("Enter y-coordinate you want to move your penguin from:");
        scanf("%i", &fromY);
    }
    printf("Enter x-coordinate you want to move your penguin on:");
    scanf("%i",&toX);
    while (toX > number_of_columns - 1 || toX < 0) {
        printf("Wrong coordinates, please try again:");
        printf("Enter x-coordinate you want to move your penguin on:");
        scanf("%i", &toX);
    }

    printf("Enter y-coordinate you want to move your penguin on:");
    scanf("%i",&toY);
    while (toY > number_of_rows - 1 || toY < 0) {
        printf("Wrong coordinates, please try again:");
        printf("Enter y-coordinate you want to move your penguin on:");
        scanf("%i", &toY);
    }

    struct movement m;
    m.from.x= fromX;
    m.from.y= fromY;
    m.to.x= toX;
    m.to.y= toY;
    return m;
}

/*
input parameters: int number_of_columns, int number_of_rows
return: placement type
this function asks a user for a placement of a penguin and returns it.
*/
struct placement get_placement(int number_of_columns, int number_of_rows) {
    int x, y;
    printf("Enter x-coordinate you want to place your penguin on:");
    scanf("%i",&x);
    while (x > number_of_columns - 1 || x < 0) {
        printf("Wrong coordinates, please try again:");
        scanf("%i", &x);
    }

    printf("Enter y-coordinate you want to place your penguin on:");
    scanf("%i",&y);
    while (y > number_of_rows - 1|| y < 0) {
        printf("Wrong coordinates, please try again:");
        scanf("%i", &y);
    }

    struct placement p = {x, y};
    return p;
}

/*
input parameters: struct player* players, int curr_player
return: none
this function displays which player's turn is.
*/
void display_curr_player(struct player* players, int curr_player) {
   printf("TURN: %c\n", players[curr_player-1].name); 
}

/*
input parameters: none
return: none
this function is used when the placement is invalid.
*/
void print_invalid_placement() {
    printf("Placement is invalid.\n");
}

/*
input parameters: none
return: none
this function is used when the movement is invalid.
*/
void print_invalid_movement() {
    printf("Movement is invalid.\n");
}

/*
input parameters: struct player* players, int n, int winner
return: none
this function is used to print the winner.
*/
void print_winner(struct player* players, int n, int winner) {
    printf("The winner is %c,Congratulations!\n", players[winner - 1].name);
    printf("The winner's score is %d\n", players[winner - 1].fish_collected);
}

/*
input parameters: struct player* players, int n
return: none
this function is used to show the ranking.
*/
void show_ranking(struct player* players, int n) {
    printf("RANKING\n");
    printf("name | score\n");
    int i;
    for (i=0; i<n; ++i) {
        printf("%c: %d\n", players[i].name, players[i].fish_collected);
    }
}

/*
input parameters: none
return: integer
this function is determine the difficulty level of the bot.
*/
int get_difficulty_level() {
    int level;
    printf("Enter the level of difficulty(from 1(included) to 5(included)): ");
    scanf("%i", &level);

    while (level < 0 || level > 5) {
        printf("Wrong level of difficulty. Please try again");
        scanf("%i", &level);
    }
    return level;
}

/*
input parameters: none
return: integer
this function is check if certain player is a bot.
*/
int check_if_ai() {
    int answer;
    printf("Is the player a bot?(1 for yes and 0 for no): ");
    scanf("%i",&answer);
    while(answer != 0 && answer != 1) {
        printf("Wrong answer. Please try again");
        scanf("%i",&answer);
    }
    return answer;
}
