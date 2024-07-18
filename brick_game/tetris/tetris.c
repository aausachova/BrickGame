#include "tetris.h"

#include "backend.h"

int main() {
  WIN_INIT(50);
  setlocale(LC_ALL, "");

  game_init();

  endwin();

  return 0;
}

void game_init() {
  GameInfo_t data;
  GameState_t state = START_STATE;
  bool break_flag = TRUE;
  int high = 0;

  init_stats(&data);
  read_file(&high);

  data.high_score = high;
  data.speed = 50;

  while (break_flag) {
    int input = getch();
    if (state == START_STATE) {
      StartGame(input);
    }
    updateCurrentState(&data, &state, input);
    if (state == GAMEOVER_STATE) {
      break_flag = false;
      record_file(data.score);
      clear();
      print_game_over();
      getch();
      sleep(3);
    } else if (state == PAUSE_STATE) {
      print_pause_message();
    } else {
      print_overlay();
      if (state == START_STATE || state == SPAWN_STATE || state == MOVING_STATE)
        draw_next_info(&data);
      draw_field(&data);
    }
  }
}

void init_stats(GameInfo_t *stats) {
  stats->level = 1;
  stats->score = 0;
  stats->speed = 1;
  stats->high_score = 0;
  stats->pause = 0;
  clear_game_field(stats->field);
  clear_game_field(stats->next);
  clear_game_field(stats->figure_m);
}