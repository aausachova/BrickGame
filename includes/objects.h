#ifndef OBJECTS_H_
#define OBJECTS_H_

#include <stdbool.h>

typedef struct {
  int field[10][20];
  int next[10][20];
  int figure_m[10][20];
  bool new_figure_spawned;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Rotate
} UserAction_t;

typedef enum {
  START_STATE,
  SPAWN_STATE,
  MOVING_STATE,     // нажатие кнопок
  SHIFTING_STATE,   // перемещение фигуры
  ATTACHING_STATE,  // присоеднение фигуры
  PAUSE_STATE,
  GAMEOVER_STATE
} GameState_t;

#endif  // OBJECTS_H_