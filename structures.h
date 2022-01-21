#ifndef STRUCTS
#define STRUCTS
struct player {
    int id;
    char name;
    char full_name[32]; //to get full_name it has to be checked somehow
    int fish_collected;
    int penguins;       //number of penguins, should not be changed
    int pen_not_placed; //number of penguins which are not placed
    int movement_status; //if the player has a tile to go onto
    int bot; // if a player is bot 1, if human - 0; 
    int bot_level; // difficulty level of the bot, 0 if the player is a human.
};

struct board_tile {
    int occupied;   //id of player which occupies this tile or 0 if it is not occupied
    int fishes;     //if it is equal to 0 then it is an ocean floe, if it is equal to 1 or 2 or 3 then it has this amount of fish on it
};

struct coordinate {
    int x;
    int y;
};

struct placement {
    struct coordinate to;
};

struct movement {
    struct coordinate from;
    struct coordinate to;
};

struct GameState {
    struct board_tile** board;
    struct player* players;
    int board_x, board_y; // board dims
    int n;  // number of players
};
struct bot_placement
    {
        int x; // x coordinate of the tile
        int y; // y coordinate of the tile
    };
        struct bot_choosing
    {
        int x; // x coordinate of the tile
        int y; // y coordinate of the tile
    };
    struct bot_movement
    {
        int x; // x coordinate of the tile
        int y; // y coordinate of the tile
    };
    struct bot_second_round
    {
        int x; // x coordinate of the tile
        int y; // y coordinate of the tile
        int prof; // amount of fish it would be able to collect
        int direct; // max amount of directions
        int id; // id of initial tile
    };


#endif
