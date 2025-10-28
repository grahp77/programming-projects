#ifndef BACKEND_H
#define BACKEND_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define WIDTH 10
#define HEIGHT 20
#define MIN 1
#define MAX 7
#define FIGURE_START_X -4
#define FIGURE_START_Y 4
#define HIGHSCORE_FILE "highscore.txt"

#include "../../struct.h"

typedef enum {
  Start_game,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  Pause_game,
  Game_over
} State_t;

typedef struct {
  GameInfo_t CurrentState;
  UserAction_t current_action;
  State_t State;
  int start;
  int number_random_figure;
  int number_cur_figure;
  int **current_figure;
  int **temp_figure;
  int move;
  int prev_move;
  int left_right;
  int previous_left_right;
  long long interval;
  long long last_time;
} All_t;

typedef void (*action)(All_t *info);

GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);

All_t *movementFigure();
void memoryAllcationAll(All_t *info);
int memoryAllocation(int ***matrix, int rows, int cols);

action fsm_state(int State, int current_action);
void startGame(All_t *info);
int load_highscore();

void spawn(All_t *info);
void copyMatrix(int **result, int **matrix);
void matrixNull(int **matrix);
void figure(GameInfo_t *CurrentState, int number_random_figure);

void shifting(All_t *info);
long long get_milliseconds();
void figureMooveNull(All_t *info);
int collisionCheck(All_t *info);
void figureMoove(All_t *info);

void moving(All_t *info);
void moveleft(All_t *info);
void moveright(All_t *info);
void movedown(All_t *info);
void moveup(All_t *info);
void turn(All_t *info);

void checkAttaching(All_t *info);
void clearLineAndScore(All_t *info);
void shiftingDownwards(All_t *info, int line);
void save_highscore(int highscore);

void gameOver(All_t *info);
void grafic(All_t *info, bool x);

void exitGame(All_t *info);
void removeAllocation(int ***matrix, int rows);

// void input_processing(int ch, UserAction_t *current_action);

#endif
