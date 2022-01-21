#ifndef AUTOFUN
#define AUTOFUN
// function is run by main if game is played in autonomous mode, executes command given in command line arguments
// arguments: game state, number of command line arguments, command line arguments
// returns: no value
void execute_autonomous_command(struct GameState* state, int argc, char **argv);
// these functions only run in autonomous mode, check if command line arguments are valid - according to documentation
// arguments: number of command line arguments, command line arguments
// returns: no value 
void invalid_cla_check(int argc, char **argv);
// checkes if the there extists a players with a full name / nick
int find_id_by_name(struct player *players, int n, char *nick);
// adds a new players to an array, it might change the address of the array as it might no longer fit in the previously assigned block of memory
void add_new_player(struct player **players, int *n, int id, char name, char *full_name, int fish_collected, int penguins, int pen_not_placed, int movement_status, int bot, int bot_level);
// returns next id which is not used by another player
int next_free_id(struct player* players, int n); 
#endif
