#include "../structures.h"
#include "../evaluation.h"
#include "../map.h"
#include "../miscellaneous.h"
#include "../movement.h"
#include "../placement.h"
#include "../bots.h"
#include "../defines.h"
#include "../external_data.h"
#include "../autonomous.h"
#include <stdlib.h>
#include <stdio.h>
#include <queue.h>
#include <vector.h>
#include "raylib.h"
#include <assert.h>

#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_CUSTOM_ICONS     // It requires providing gui_icons.h in the same directory
//#include "gui_icons.h"          // External icons data provided, it can be generated with rGuiIcons tool
#include "raygui.h"
#include <string.h>             
#include "gui.h"

int main(int agrc, char **argv) {   
#if INTERACTIVE_MODE
    int n = 1;                                          // number of players
    struct player* players;
    players = malloc(sizeof(struct player));    // init the array
    players = new_players(players, n);          // array of players
    int curr_player;
    int x = 5, y = 5;                                   // x and y size of the map          
    struct board_tile** board = new_board(x, y);        // board stores a pointer to a 2D array
    generate_board(board, x, y, n);                        // map is fill with values
    
    // set parameters for the game window 
    const int screenWidth = 1200;
    const int screenHeight = 800;
    int frameRate = 60;
    // initiazlize the window
    init_gui(screenWidth, screenHeight, "Game", frameRate);
     
    bool exitWindow = false;

    Phase phase = INPUT_PHASE;

    // as long as the window should stay open 
    while (!exitWindow) {
        exitWindow = WindowShouldClose();
        BeginDrawing();
            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
            if (phase == INPUT_PHASE) {
                draw_input_phase(&board, &x, &y, &players, &n, &curr_player, &phase);
            }   
            if (phase == PLACEMENT_PHASE && placement_game_status(board, x, y, players, n) == END_PP) {
                phase = MOVEMENT_PHASE;
                movement_init(board, x, y, players, n);
            }
            if (phase == PLACEMENT_PHASE) {
                draw_console(players, n, curr_player, "PLACEMENT PHASE");
                while (placement_game_status(board, x, y, players, n) == END_PP && placement_possible(board, x, y, players, curr_player) == FALSE) {
                    next_player(&curr_player, n);
                    //continue;
                }
                struct placement p = get_placement(board, x, y, curr_player);
                if (valid_placement(board, x, y, p) == TRUE) {
                    execute_placement(board, players, curr_player, p);
                    next_player(&curr_player, n);
                }
            }
            if (phase == MOVEMENT_PHASE && movement_game_status(board, players, n) == END_MP) {
                phase = END_PHASE;
            }
            if (phase == MOVEMENT_PHASE) {
                draw_console(players, n, curr_player, "MOVEMENT PHASE");  
                while (movement_game_status(board, players, n) != END_MP && movement_possible(board, x, y, players, curr_player) == FALSE) {
                    next_player(&curr_player, n);
                    //EndDrawing();
                    //continue;
                }
                struct movement m;
                m = get_movement(board, x, y, players, n, curr_player);
                if (movement_null(m) != 1 && valid_movement(board, players, m, curr_player) == TRUE) {
                    execute_movement(board, players, curr_player, m);
                    next_player(&curr_player, n);
                } 
            }
            if (phase == END_PHASE) {
                // Draw the results
                draw_end(players, n, &phase);
            }
 
        EndDrawing();
    }   
           
    CloseWindow();        // Close window and OpenGL context
     
#endif
   
    return 0;      
}
