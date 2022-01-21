#include "../defines.h"
#include "../structures.h"
#include "../map.h"
#include "../miscellaneous.h"
#include "../movement.h"
#include "../placement.h"
#include "../evaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>             
#include <assert.h>
#include <queue.h>
#include <vector.h>
#include "raylib.h"
#include "raygui.h"
#include "gui.h"


static Color colorId[9] = {RED, BLUE, GREEN,
                    PURPLE, BEIGE, PINK,
                    ORANGE, BROWN, YELLOW};

// parameters for GUI elements

// spinner with number of players
static bool spinner1EditMode = 0;  
static int spinner1Value = 1;      

// spinner with number of penguins
static bool spinner2EditMode = 0; 
static int spinner2Value = 1;

// spinner with size of board's x dim
static bool spinner3EditMode = 0; 
static int spinner3Value = 5;

// spinner with size of board's y dim
static bool spinner4EditMode = 0; 
static int spinner4Value = 5;

// input fields
typedef struct {
    char text[16];
    char *placeHolder;
    bool editMode;
} FieldValue; 
FieldValue inputFields[9];

void simple_board(struct board_tile **board, int x, int y) {
    for (int i=0; i<y; ++i) {
        for (int j=0; j<x; ++j)
            printf("%d ",board[i][j].fishes);
        printf("\n");
    }
}

void draw_tiles(struct board_tile **board, int x, int y) {
    int tx = (int)(800.0 / (float)(x));
    int ty = (int)(800.0 / (float)(y));
    tx = (tx < ty) ? tx : ty;
    ty = tx;
    int padding = ty / 8.0;
    int tw = tx - padding;
    int th = ty - padding;
    for (int i=0; i<y; ++i) {
        for (int j=0; j<x; ++j) { 
            //printf("%d ",board[i][j].fishes);
            DrawRectangle(j * tx + padding, i * ty + padding, tw, th, (board[i][j].fishes>0)? WHITE : SKYBLUE);
            char tile_val[2];
            tile_val[0] = '0' + board[i][j].fishes;
            tile_val[1] = '\0';
            if (board[i][j].fishes)
                DrawText(tile_val, j*tx + padding + tw/4.0, i*ty + padding + th/4.0, tw/1.5, BLACK);
        }
        //printf("\n");
    }
}
void init_gui(const int screenWidth, const int screenHeight, char *windowName, int frameRate) {
    InitWindow(screenWidth, screenHeight, windowName);
    SetExitKey(0);
    SetTargetFPS(frameRate);

    // set initial values for GUI elements
    for (int i=0; i<9; ++i) {
        //inputFields[i].text = "";
        inputFields[i].placeHolder = "Type name";
        inputFields[i].editMode = 0;
    }
}

void draw_input_phase(struct board_tile ***board, int *x, int *y, struct player **players, int *n, int *curr_player, Phase *phase) {
    // draw the ocean
    DrawRectangle(0, 0, 800, 800, SKYBLUE);
    // draw the console - the area with inputs 
    DrawRectangle(800, 0, 400, 800, WHITE);
    // draw the title 
    DrawText("Game setup", 820, 20, 30, DARKPURPLE);
    // draw comment and sliders for the number of players 
    DrawText("Number of players", 820, 60, 15, DARKPURPLE);
    // set style for the spinner 
    GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);     
    // draw the spinner and if it is clicked on enter if statemetment
    if (GuiSpinner((Rectangle){ 820, 80, 170, 30 }, NULL, &spinner1Value, 1, 9, spinner1EditMode)) {
        spinner1EditMode ^= 1;
    }
    int new_n = spinner1Value;
    if (*n != new_n) {
        *n = new_n;
        *players = new_players(*players, *n);
    }
    // draw comment and sliders for the number of penguins 
    DrawText("Number of penguins", 1010, 60, 15, DARKPURPLE);
    // set style for the spinner 
    GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);     
    // draw the spinner and if it is clicked on enter if statemetment
    if (GuiSpinner((Rectangle){ 1010, 80, 170, 30 }, NULL, &spinner2Value, 1, 9, spinner2EditMode)) {
        spinner2EditMode ^= 1;
    }
    // the list of players - a list of input fields
    DrawText("List of players", 820, 150, 20, DARKPURPLE);
    // set style for input fields 
    GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_LEFT);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);    
    // draw the input fields
    int x_0 = 820, y_0 = 175, fieldWidth = 125, fieldHeight = 40, dy = 50;
    // first column
    for (int i=0; i<9; i+=2) {
        if (i+1 > *n) break;
        if (GuiTextBox((Rectangle){ x_0, y_0 + i/2*dy, fieldWidth, fieldHeight}, 
                                    (inputFields[i].editMode || strlen(inputFields[i].text) > 0) ? 
                                    inputFields[i].text : inputFields[i].placeHolder, 16,
                                    inputFields[i].editMode)) {
            inputFields[i].editMode ^= 1;
        }
    }
    // second column
    x_0 = 1010;
    // second column
    for (int i=1; i<9; i+=2) {
        if (i+1 > *n) break;
        if (GuiTextBox((Rectangle){ x_0, y_0 + i/2*dy, fieldWidth, fieldHeight}, 
                                    (inputFields[i].editMode || strlen(inputFields[i].text) > 0) ? 
                                    inputFields[i].text : inputFields[i].placeHolder, 16,
                                    inputFields[i].editMode)) {
            inputFields[i].editMode ^= 1;
        }
    }
    // draw comment for spinner for x board dimenstion
    DrawText("Board x-dim", 820, 450, 15, DARKPURPLE); 
    // draw the spinner and if it is clicked on enter if statemetment
    if (GuiSpinner((Rectangle){ 820, 470, 170, 30 }, NULL, &spinner3Value, 5, 16, spinner3EditMode)) {
        spinner3EditMode ^= 1;
    }
    int new_x = spinner3Value;
    if (*x != new_x) {
        free_board(*board, *x, *y);
        *x = new_x;
        *board = new_board(*x, *y);
        generate_board(*board, *x, *y, *n);
    }
    // draw comment for spinner for y board dimenstion
    DrawText("Board y-dim", 1010, 450, 15, DARKPURPLE); 
    // draw the spinner and if it is clicked on enter if statemetment
    if (GuiSpinner((Rectangle){ 1010, 470, 170, 30 }, NULL, &spinner4Value, 5, 16, spinner4EditMode)) {
        spinner4EditMode ^= 1;
    }
    int new_y = spinner4Value;
    if (*y != new_y) {
        free_board(*board, *x, *y);
        *y = new_y;
        *board = new_board(*x, *y);
        generate_board(*board, *x, *y, *n);
    }
    // draw a grid of tiles 
    int tx = (int)(800.0 / (float)(*x));
    int ty = (int)(800.0 / (float)(*y));
    tx = (tx < ty) ? tx : ty;
    ty = tx;
    int padding = ty / 8.0;
    int tw = tx - padding;
    int th = ty - padding;
    for (int i=0; i<*y; ++i) {
        for (int j=0; j<*x; ++j) { 
            DrawRectangle(j * tx + padding, i * ty + padding, tw, th, ((*board)[i][j].fishes>0)? WHITE : SKYBLUE);
            char tile_val[2];
            tile_val[0] = '0' + (*board)[i][j].fishes;
            tile_val[1] = '\0';
            if ((*board)[i][j].fishes)
                DrawText(tile_val, j*tx + padding + tw/4.0, i*ty + padding + th/4.0, tw/1.5, BLACK);
        }
    }
    /* PLAY BUTTON */
    
    // set the style 
    GuiSetState(GUI_STATE_NORMAL);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);     
    if (GuiButton((Rectangle){ 820, 680, 360, 100}, "PLAY")) {
        *phase = PLACEMENT_PHASE;
        // copy all inputed values
        for (int i=0; i<9; ++i) {
            if (*n < i+1) break;
            (*players)[i].id = i+1;
            (*players)[i].name = inputFields[i].text[0];
            (*players)[i].fish_collected = 0;
            (*players)[i].penguins = spinner2Value;
            (*players)[i].pen_not_placed = spinner2Value;
            (*players)[i].bot = 0;
            (*players)[i].bot_level = 0;
        }       
        *curr_player = choose_first_player(*n); 
    }
}

void draw_console(struct player *players, int n, int curr_player, char *title) {
    
    // draw the ocean
    DrawRectangle(0, 0, 800, 800, SKYBLUE);
    // draw the console - the area with inputs 
    DrawRectangle(800, 0, 400, 800, WHITE);
    // draw the title 
    DrawText(title, 820, 20, 35, DARKPURPLE);
    // draw comment and sliders for the number of players
    char buf[12];
    snprintf(buf, 12, "%s%c", "TURN: ", players[curr_player-1].name); 
    DrawText(buf, 820, 70, 30, DARKPURPLE);
    DrawText("Ranking", 820, 120, 30, DARKPURPLE);

    int y_0 =  155, dy = 40;
    // draw ranking
    for (int i=0; i<n; ++i) {
        char position[12];
        snprintf(position, 12, "%c%s%d", players[i].name, "\t", players[i].fish_collected); 
        DrawText(position, 820, y_0 + i*dy, 30, colorId[i]); 
    }
}

struct placement get_placement(struct board_tile **board, int x, int y, int curr_player) {
    struct placement p;
    p.to.x = -1;
    p.to.y = -1;
    // draw a grid of tiles 
    int tx = (int)(800.0 / (float)(x));
    int ty = (int)(800.0 / (float)(y));
    tx = (tx < ty) ? tx : ty;
    ty = tx;
    int padding = ty / 8.0;
    int tw = tx - padding;
    int th = ty - padding;
    
    for (int i=0; i<y; ++i) {
        for (int j=0; j<x; ++j) {
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){j * tx + padding, i * ty + padding, tw, th})) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == true &&
                    board[i][j].fishes > 0) {
                    p.to.x = j;
                    p.to.y = i;
                    DrawRectangle(j * tx + 2*padding, i * ty + 2*padding, tx - 3*padding, ty - 3*padding, colorId[curr_player-1]);
                    continue;
                }
                else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == false &&
                         board[i][j].fishes > 0 ) {
                    DrawRectangle(j * tx + padding, i * ty + padding, tw, th, colorId[curr_player-1]);
                    continue;
                } 
            }
            if (board[i][j].occupied != 0)  
                DrawRectangle(j * tx + padding, i * ty + padding, tw, th, colorId[board[i][j].occupied-1]);
            else {
                char tile_val[2];
                tile_val[0] = '0' + board[i][j].fishes;
                tile_val[1] = '\0';
                DrawRectangle(j * tx + padding, i * ty + padding, tw, th, board[i][j].fishes ? WHITE : SKYBLUE);
                if (board[i][j].fishes)
                    DrawText(tile_val, j*tx + padding + tw/4.0, i*ty + padding + th/4.0, tw/1.5, BLACK);
            }
        }
    }
    return p;
}

static struct movement m = (struct movement){{-1, -1}, {-1, -1}};

struct movement get_movement(struct board_tile **board, int x, int y, struct player *players, int n, int curr_player) {
    if (m.from.x != -1 && m.from.y != -1 && m.to.x != -1 && m.to.y != -1)
        m.from.x = m.from.y = m.to.x = m.to.y = -1;
    // draw a grid of tiles 
    int tx = (int)(800.0 / (float)(x));
    int ty = (int)(800.0 / (float)(y));
    tx = (tx < ty) ? tx : ty;
    ty = tx;
    int padding = ty / 8.0;
    int tw = tx - padding;
    int th = ty - padding;
    for (int i=0; i<y; ++i) {
        for (int j=0; j<x; ++j) {
            // if it is the ocean skip this tile
            if (board[i][j].occupied == 0 && board[i][j].fishes == 0)
                continue;
            // if the mouse if over the current tile
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){j * tx + padding, i * ty + padding, tw, th})) {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == true &&
                    board[i][j].occupied == curr_player &&
                    (m.from.x == -1 && m.from.y == -1)) {
                   // we found the movement from 
                    m.from.x = j;
                    m.from.y = i;
                    DrawRectangle(j * tx + 2*padding, i * ty + 2*padding, tx - 3*padding, ty - 3*padding, colorId[curr_player-1]);
                    continue;
                }
                else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == true &&
                         board[i][j].occupied == 0 &&
                         m.from.x != -1 && m.from.y != -1 &&
                         m.to.x == -1 && m.to.y == -1) {
                    // we found the movement to
                    m.to.x = j;
                    m.to.y = i;
                    DrawRectangle(j * tx + 2*padding, i * ty + 2*padding, tx - 3*padding, ty - 3*padding, colorId[curr_player-1]);
                    continue;
                }
                else if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == false &&
                         ((board[i][j].occupied == curr_player) ||
                         (board[i][j].occupied == 0 && board[i][j].fishes))) {
                    // we hover about the tile we can move from/to
                    DrawRectangle(j * tx + padding, i * ty + padding, tw, th, colorId[curr_player-1]);
                    continue;
                }
            }
            if (board[i][j].occupied != 0) {
                if (m.from.x == j && m.from.y == i)  
                    DrawRectangle(j * tx + 2*padding, i * ty + 2*padding, tx - 3*padding, ty - 3*padding, colorId[board[i][j].occupied-1]);
                else 
                    DrawRectangle(j * tx + padding, i * ty + padding, tw, th, colorId[board[i][j].occupied-1]);
            }
            else {
                char tile_val[2];
                tile_val[0] = '0' + board[i][j].fishes;
                tile_val[1] = '\0';
                DrawRectangle(j * tx + padding, i * ty + padding, tw, th, board[i][j].fishes ? WHITE : SKYBLUE);
                if (board[i][j].fishes)
                    DrawText(tile_val, j*tx + padding + tw/4.0, i*ty + padding + th/4.0, tw/1.5, BLACK);
            }
        }
    }
    return m;
}

void draw_end(struct player *players, int n, Phase *phase) {
    // draw the ocean
    DrawRectangle(0, 0, 800, 800, SKYBLUE);
    // draw the console - the area with inputs 
    DrawRectangle(800, 0, 400, 800, WHITE);
    // draw comment and sliders for the number of players
    DrawText("Ranking", 820, 120, 30, DARKPURPLE);

    int y_0 =  155, dy = 40;
    // draw ranking
    for (int i=0; i<n; ++i) {
        char position[12];
        snprintf(position, 12, "%c%s%d", players[i].name, "\t", players[i].fish_collected); 
        DrawText(position, 820, y_0 + i*dy, 30, colorId[i]); 
    }
    GuiSetState(GUI_STATE_NORMAL);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);     
    if (GuiButton((Rectangle){ 300, 350, 200, 100}, "NEW GAME")) {
        *phase = INPUT_PHASE;
    }
}
