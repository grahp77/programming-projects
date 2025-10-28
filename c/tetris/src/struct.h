#ifndef STRUCT_H
#define STRUCT_H

typedef enum {
  Terminate,
  Start,
  Pause,
  Left,
  Right,
  Up,
  Down,
  Action,
  Exit
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#endif