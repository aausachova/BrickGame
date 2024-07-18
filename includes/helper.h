#ifndef HELPER_H_
#define HELPER_H_

#include <ncurses.h>
#include <stdlib.h>

#include "backend.h"
#include "cli.h"
#include "define.h"

void rotate_matrix(int matrix[][20]);
void centr_rotate(int matrix[][20], int *x, int *y);
void sort(int scores[100]);
void read_file(int *high_score);
void record_file(int high_score);
void StartGame(int input);

#endif  // HELPER_H_