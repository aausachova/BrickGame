#include <check.h>
#include <time.h>

#include "../includes/backend.h"
#include "../includes/cli.h"
#include "../includes/define.h"
#include "../includes/objects.h"
#include "../includes/tetris.h"

START_TEST(matr_copy) {
  int matr_1[10][20];
  int matr_2[10][20];
  clear_game_field(matr_1);
  clear_game_field(matr_2);
  matr_1[3][10] = 1;
  copy_matrix(matr_2, matr_1);

  ck_assert_int_eq(matr_1[3][10], matr_2[3][10]);
}
END_TEST

START_TEST(game_over) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 0;

  while (state != GAMEOVER_STATE) {
    updateCurrentState(&data, &state, 0);
  }

  ck_assert_int_eq(state, GAMEOVER_STATE);
}
END_TEST

START_TEST(terminate) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 0;
  int input = 0550;
  updateCurrentState(&data, &state, input);

  ck_assert_int_ne(state, GAMEOVER_STATE);
}
END_TEST

START_TEST(move_down) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 0;
  int input = KEY_DOWN;
  updateCurrentState(&data, &state, input);
  input = KEY_DOWN;
  updateCurrentState(&data, &state, input);

  ck_assert_int_eq(state, MOVING_STATE);
}
END_TEST

START_TEST(move_left) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 0;
  int input = KEY_LEFT;
  updateCurrentState(&data, &state, input);
  updateCurrentState(&data, &state, input);

  ck_assert_int_eq(state, MOVING_STATE);
}
END_TEST

START_TEST(move_right) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 1;
  int input = KEY_RIGHT;
  updateCurrentState(&data, &state, input);
  updateCurrentState(&data, &state, input);

  ck_assert_int_eq(state, MOVING_STATE);
}
END_TEST

START_TEST(PAUSE) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 1;
  int input = 'p';
  updateCurrentState(&data, &state, input);

  ck_assert_int_ne(state, PAUSE_STATE);
}
END_TEST

START_TEST(move_rotate) {
  srand(time(NULL));
  GameInfo_t data;
  GameState_t state = START_STATE;
  data.speed = 1;
  int input = ' ';
  updateCurrentState(&data, &state, input);

  ck_assert_int_eq(state, MOVING_STATE);
}
END_TEST

Suite *tetris_suite(void) {
  Suite *suite;
  suite = suite_create("Tetris");

  TCase *tcase_core = tcase_create("Core");
  tcase_add_test(tcase_core, matr_copy);
  tcase_add_test(tcase_core, game_over);
  tcase_add_test(tcase_core, terminate);
  tcase_add_test(tcase_core, move_down);
  tcase_add_test(tcase_core, move_left);
  tcase_add_test(tcase_core, move_right);
  tcase_add_test(tcase_core, PAUSE);
  tcase_add_test(tcase_core, move_rotate);
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main(void) {
  Suite *suite = tetris_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_VERBOSE);
  int failed_count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}