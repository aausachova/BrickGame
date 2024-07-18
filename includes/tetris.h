#ifndef TETRIC_H_
#define TETRIC_H_

#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "backend.h"
#include "cli.h"
#include "define.h"
#include "helper.h"
#include "objects.h"

void game_init();
void init_stats(GameInfo_t *stats);
void read_file(int *high_score);
void sort(int scores[100]);
void record_file(int high_score);

#endif  // TETRIC_H_