#include "backend.h"

void clear_game_field(int field[10][20]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      field[i][j] = 0;
    }
  }
}

void spawn_new_figure(int matrix[][20]) {
  int value = rand() % 7 + 1;
  int figures[7][4] = {{1, 3, 5, 7}, {2, 4, 5, 7}, {3, 4, 5, 6}, {3, 4, 5, 7},
                       {2, 3, 5, 7}, {3, 5, 6, 7}, {2, 3, 4, 5}};
  for (int c = 0; c < 4; c++) {
    int x = figures[value - 1][c] % 2 + 4;
    int y = figures[value - 1][c] / 2;
    matrix[x][y] = 1;
  }

  if (value != 1) move_up_matrix(matrix);
}

UserAction_t userInput(int action) {
  UserAction_t rc = -1;
  if (action == KEY_UP)
    rc = Up;
  else if (action == KEY_DOWN)
    rc = Down;
  else if (action == KEY_LEFT)
    rc = Left;
  else if (action == KEY_RIGHT)
    rc = Right;
  else if (action == ' ')
    rc = Rotate;
  else if (action == ENTER_KEY)
    rc = Start;
  else if (action == ESCAPE)
    rc = Terminate;
  else if (action == 'p' || action == 'P')
    rc = Pause;

  return rc;
}

void game_controller(GameInfo_t *info, GameState_t *state, int input) {
  switch (userInput(input)) {
    case Terminate:
      *state = GAMEOVER_STATE;
      break;
    case Left:
      move_left_matrix(info->figure_m);
      if (check_matrix(info) == 0) move_right_matrix(info->figure_m);
      *state = MOVING_STATE;
      break;
    case Right:
      move_right_matrix(info->figure_m);
      if (check_matrix(info) == 0) move_left_matrix(info->figure_m);
      *state = MOVING_STATE;
      break;
    case Down:
      if (check_matrix(info) == 1) {
        move_down_matrix(info->figure_m);
        *state = MOVING_STATE;
      } else {
        move_up_matrix(info->figure_m);
        *state = ATTACHING_STATE;
      }
      break;
    case Rotate:
      rotate_matrix(info->figure_m);
      break;
    case Pause:
      *state = PAUSE_STATE;
      break;
    default:
      break;
  }
}

void updateCurrentState(GameInfo_t *data, GameState_t *state, int input) {
  struct timespec ts = {.tv_sec = 0, .tv_nsec = 0.001 * 1000000000L};
  switch (*state) {
    case START_STATE:
      *state = MOVING_STATE;
      clear_game_field(data->field);
      clear_game_field(data->figure_m);
      clear_game_field(data->next);
      spawn_new_figure(data->figure_m);
      spawn_new_figure(data->next);
      break;
    case SPAWN_STATE:
      *state = MOVING_STATE;
      clear_game_field(data->figure_m);
      copy_matrix(data->figure_m, data->next);
      clear_game_field(data->next);
      spawn_new_figure(data->next);
      break;
    case MOVING_STATE:
      *state = SHIFTING_STATE;
      game_controller(data, state, input);
      break;
    case SHIFTING_STATE:
      if (check_matrix(data) == 1) {
        *state = MOVING_STATE;
        move_down_matrix(data->figure_m);

        ts.tv_nsec = 0.01 * data->speed * 1000000000L;
        nanosleep(&ts, NULL);

        if (data->high_score < data->score) {
          data->high_score = data->score;
        }
      } else {
        move_up_matrix(data->figure_m);
        *state = ATTACHING_STATE;
      }
      break;
    case ATTACHING_STATE:
      *state = SPAWN_STATE;
      add_matrix(data->field, data->field, data->figure_m);
      data->score += 4;
      if (data->score > data->high_score) data->high_score = data->score;
      int rows_ = shift_rows(data->field);
      add_points(data, rows_);
      if (data->score > 600 * (data->level + 1) && data->level < 10) {
        data->level++;
        data->speed -= 5;
      }
      if (check_game_over(data->field) == 0) *state = GAMEOVER_STATE;
      break;
    case PAUSE_STATE:
      *state = PAUSE_STATE;
      if (userInput(input) == Pause) *state = MOVING_STATE;
      break;
    default:
      break;
  }
}

void shift_matrix_down(int matrix[][20], int start_row) {
  for (int i = 0; i < 10; ++i) {
    for (int k = start_row; k >= 0; --k) {
      if (matrix[i][k] == 1) {
        matrix[i][k] = 0;
        matrix[i][k + 1] = 1;
      }
    }
  }
}

void move_down_matrix(int matrix[][20]) { shift_matrix_down(matrix, 19); }

int check_matrix(const GameInfo_t *data) {
  int matrix[10][20] = {0};
  clear_game_field(matrix);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 20; ++j) {
      matrix[i][j] = data->field[i][j] * data->figure_m[i][j];
      if (matrix[i][j] == 1) return 0;
    }
  }
  for (int i = 0; i < 10; i++)
    if (data->figure_m[i][19] == 1) return 0;
  return 1;
}

void move_up_matrix(int matrix[][20]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      if (matrix[i][j] == 1) {
        matrix[i][j] = 0;
        matrix[i][j - 1] = 1;
      }
    }
  }
}

void copy_matrix(int res[][20], int dest[][20]) {
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 20; j++) res[i][j] = dest[i][j];
}

void move_left_matrix(int matrix[][20]) {
  int check_left = 1;
  for (int j = 0; j < 20; ++j)
    if (matrix[0][j] == 1) check_left = 0;

  if (check_left == 1) {
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 20; ++j) {
        if (matrix[i][j] == 1) {
          matrix[i][j] = 0;
          matrix[i - 1][j] = 1;
        }
      }
    }
  }
}

void move_right_matrix(int matrix[][20]) {
  int check_left = 1;
  for (int j = 0; j < 20; ++j)
    if (matrix[9][j] == 1) check_left = 0;

  if (check_left == 1) {
    for (int i = 9; i >= 0; --i) {
      for (int j = 0; j < 20; ++j) {
        if (matrix[i][j] == 1) {
          matrix[i][j] = 0;
          matrix[i + 1][j] = 1;
        }
      }
    }
  }
}

void add_matrix(int matrix_res[][20], const int matrix_1[][20],
                const int matrix_2[][20]) {
  for (int i = 0; i < 10; ++i)
    for (int j = 0; j < 20; ++j)
      matrix_res[i][j] = matrix_1[i][j] + matrix_2[i][j];
}

int shift_rows(int matrix[][20]) {
  int row_count = 0;
  for (int j = 19; j >= 0; --j) {
    if (is_full_row(matrix, j) == TRUE) {
      for (int i = 0; i < 10; i++) matrix[i][j] = 0;
      shift_matrix_down(matrix, j);
      j++;
      row_count++;
    }
  }
  return row_count;
}

void add_points(GameInfo_t *data, int rows_count) {
  if (rows_count == 1)
    data->score += 100;
  else if (rows_count == 2)
    data->score += 300;
  else if (rows_count == 3)
    data->score += 700;
  else if (rows_count == 4)
    data->score += 1500;
}

int check_game_over(int matrix[][20]) {
  int flag = TRUE;
  for (int i = 0; i < 10; ++i)
    if (matrix[i][0] == 1) flag = 0;

  return flag;
}

int is_full_row(int matrix[][20], int row) {
  int sum = 0;
  int flag = FALSE;
  for (int i = 0; i < 10; ++i) sum += matrix[i][row];

  if (sum == 10) flag = TRUE;

  return flag;
}