#ifndef BACKEND_H_
#define BACKEND_H_

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "cli.h"
#include "define.h"
#include "helper.h"
#include "objects.h"
#include "tetris.h"

UserAction_t userInput(int action);

int check_matrix(const GameInfo_t *data);
int shift_rows(int matrix[][20]);
int check_game_over(int matrix[][20]);
int is_full_row(int matrix[][20], int row);

void updateCurrentState(GameInfo_t *data, GameState_t *state, int input);
void clear_game_field(int field[10][20]);
void game_controller(GameInfo_t *game_info, GameState_t *state, int input);
void spawn_new_figure(int matrix[][20]);
void shift_matrix_down(int matrix[][20], int start_row);
void move_down_matrix(int matrix[][20]);
void move_up_matrix(int matrix[][20]);
void copy_matrix(int res[][20], int dest[][20]);
void move_left_matrix(int matrix[][20]);
void move_right_matrix(int matrix[][20]);
void add_matrix(int matrix_res[][20], const int matrix_1[][20],
                const int matrix_2[][20]);
void add_points(GameInfo_t *data, int rows_count);

#endif  // BACKEND_H_