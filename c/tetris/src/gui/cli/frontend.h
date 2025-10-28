#ifndef FRONTEND_H
#define FRONTEND_H

// #include <limits.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20
#define BORDER_OFFSET 2
#define PAUSE_START 1
#define PAUSE_PAUSE 2
#define NEXT_FIG_POS_X 10
#define NEXT_FIG_POS_Y 27
#define FIELD_TOP 0
#define FIELD_BOTTOM 21
#define FIELD_LEFT 0
#define FIELD_RIGHT 11
#define INFO_PANEL_RIGHT 19

#define SCORE_X 2
#define SCORE_Y 32
#define SCORE_NUM_X 3
#define SCORE_NUM_Y 32

#define HI_SCORE_X 5
#define HI_SCORE_Y 29
#define HI_SCORE_NUM_X 6
#define HI_SCORE_NUM_Y 32

#define NEXT_X 8
#define NEXT_Y 33

#define LEVEL_X 15
#define LEVEL_Y 32
#define LEVEL_NUM_X 16
#define LEVEL_NUM_Y 35

#define SPEED_X 18
#define SPEED_Y 31
#define SPEED_NUM_X 19
#define SPEED_NUM_Y 35

#include "../../struct.h"

void initNcurses();
void inputProcessing(int ch, UserAction_t *current_action);
void printGameInfo(GameInfo_t backend);
void printFigure(GameInfo_t CurrentState);
void printField(GameInfo_t CurrentState);
void printStart();
void printPause();
void printBorder();
void printStat(GameInfo_t CurrentState);

#endif
