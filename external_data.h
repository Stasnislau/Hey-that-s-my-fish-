#ifndef EXTFILES
#define EXTFILES
// reads content of the file given in name, fills game state with date from a text file which path is specified in name
// arguments: game state, name of the file
// return: no value 
void read_board(struct GameState *state, char* name);
// writes a new file to location specified in name
// arguments: current game state, name of the file to write this state
// returns: no value
void write_board(struct GameState* state, char* name);
#endif
