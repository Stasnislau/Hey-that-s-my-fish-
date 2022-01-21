#include "structures.h"
#include "command_line_ui.h"
#include "evaluation.h"
#include "map.h"
#include "miscellaneous.h"
#include "movement.h"
#include "placement.h"
#include "bots.h"
#include "defines.h"
#include "external_data.h"
#include "autonomous.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));   
#if AUTONOMOUS_MODE
    invalid_cla_check(argc, argv);
    
    struct GameState* state = malloc(sizeof(struct GameState));
        
    char *nick = "GROUP-B";
    if (argc == 2) {
        printf("%s",nick);
        return 0;
    }
    char *in = argc == 5 ? argv[3] : argv[2];
    char *out = argc == 5 ? argv[4] : argv[3];
    
    read_board(state, in);

    int id = find_id_by_name(state->players, state->n, nick);
    int bot_level = 1;
    int bot = 1;
    
    if (strcmp(argv[1], "phase=placement")==0) {
        int penguins = atoi(argv[2]+9);
        if (!id) {
            id = next_free_id(state->players, state->n);
            add_new_player(&(state->players), &(state->n), id, 'b', nick, 0, penguins, penguins, 0, bot, bot_level);
        }
        for (int i=0; i<state->players[id-1].penguins; ++i) {
            execute_placement_bot(state->board, state->board_x, state->board_y, state->players, state->n, id);
        }
    }
    else if (strcmp(argv[1], "phase=movement")==0) {
        state->players[id-1].bot = bot;
        state->players[id-1].bot_level = bot_level;
        movement_init(state->board, state->board_x, state->board_y, state->players, state->n);
        execute_movement_bot(state->board, state->board_x, state->board_y, state->players, state->n, id);     
    }
    write_board(state, out);  

    free_game_state(state);
#endif
#if INTERACTIVE_MODE  
    int n = get_nbr_of_players();
    struct player* players = malloc(n * sizeof(struct player));

    init_players(players, n);
    int x = get_x_dimension();
    int y = get_y_dimension();  

    // allocate memory for board and fill with elements using generate_board

    struct board_tile** board = new_board(x, y);
    // board has ocean tiles on all of its borders
    generate_board(board, x, y, n);
    
    // checks if there are enough tiles with 1 fish
    board_gen_check(board,players,x,y,n);
    // in the movement phase we might want to choose ones again the first player to make a move
    int curr_player = choose_first_player(n);
    
    /*
        PLACEMENT PHASE
    */
    placement_init();
    // as long as at least one player can place one of their penguins
    while (placement_game_status(board, x, y, players, n) != END_PP) {
        // check if current player can place a penguin
        if (placement_possible(board, x, y, players, curr_player) == TRUE) {
            display_curr_player(players, curr_player);
            if (players[curr_player-1].bot == FALSE) {
                int valid;
                struct placement p;
                // until chosen placement is invalid ask for a new one
                do {
                    show_ranking(players, n);
                    show_board(board, x, y, players);
                    p = get_placement(x, y);
                    if ( (valid = valid_placement(board, x, y, p)) == FALSE)
                        print_invalid_placement();
                } while (valid == FALSE);
                // execute valid placement
                execute_placement(board, players, curr_player, p);
            }
            else {
                // current player is a bot
                execute_placement_bot(board, x, y, players, n, curr_player);
                show_ranking(players, n);
                show_board(board, x, y, players);
            }
        }
        next_player(&curr_player, n);
    }
   
    /*
        MOVEMENT PHASE
    */
    movement_init(board, x, y, players, n);
    // as long as at least one player can make a move 
    while (movement_game_status(board, players, n) != END_MP) {
        // check if current player can make a move
        if (movement_possible(board, x, y, players, curr_player) == TRUE) {
            // until chosen move is invalid ask for another
            
            struct movement m; 
            display_curr_player(players, curr_player);
            if (players[curr_player-1].bot == FALSE) {
                int valid;
                // until chosen move is invalid ask for another
                do {
                    show_ranking(players, n);    
                    show_board(board, x, y, players);
                    m = get_movement(x, y);
                    if ( (valid = valid_movement(board, players, m, curr_player)) == FALSE)
                        print_invalid_movement();
                } while (valid == FALSE);
                execute_movement(board, players, curr_player, m);
            }
            else {
                // current player is a bot
                show_ranking(players, n);
                show_board(board, x, y, players);
                execute_movement_bot(board, x, y, players, n, curr_player);
            }
        }
        next_player(&curr_player, n);
    }
    
    int winner = determine_winner(players, n);
    show_ranking(players, n);
    print_winner(players, n, winner);
    end_game();

    free_board(board, x, y);
#endif
   
    return 0;      
}
