#include "helper.h"

void read_file(int *high_score) {
  *high_score = 0;
  int scores[100] = {0};
  FILE *fp;
  if ((fp = fopen("high_score.txt", "r")) == NULL) {
    printw("Cannot open file!\n");
    exit(1);
  }
  char *line = NULL;
  size_t len = 0;
  int i = 0;
  while ((getline(&line, &len, fp) != -1)) {
    if (strlen(line) > 0) {
      scores[i] = atoi(line);
      i++;
    }
  }
  sort(scores);
  *high_score = scores[0];

  free(line);
  fclose(fp);
}

void sort(int scores[100]) {
  int i, j, tmp;
  for (i = 0; i < 100; ++i) {
    for (j = i + 1; j < 100; ++j) {
      if (scores[i] < scores[j]) {
        tmp = scores[i];
        scores[i] = scores[j];
        scores[j] = tmp;
      }
    }
  }
}

void StartGame(int input) {
  (void)input;
  bool flag = true;
  while (flag) {
    print_overlay();
    print_intro_message();
    input = getch();
    if (input == ENTER_KEY || input == ESCAPE) flag = false;
    refresh();
    getch();
  }
}

void record_file(int high_score) {
  FILE *fp;
  if ((fp = fopen("high_score.txt", "a")) == NULL) {
    printw("Cannot open file!\n");
    exit(1);
  }
  fprintf(fp, "%d\n", high_score);

  fclose(fp);
}

void rotate_matrix(int matrix[][20]) {
  int x_c = 0, y_c = 0;
  int matrix_tmp[10][20];
  for (int j = 0; j < 20; ++j) {
    if (matrix[0][j] == 1) {
      move_right_matrix(matrix);
    }
  }
  clear_game_field(matrix_tmp);
  centr_rotate(matrix, &x_c, &y_c);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 20; ++j) {
      if (matrix[i][j] == 1) {
        int i_new = x_c + (-1) * (y_c - j);
        int j_new = y_c + x_c - i;
        if (i_new >= 0 && i_new < 10 && j_new >= 0 && j_new < 20) {
          matrix_tmp[i_new][j_new] = 1;
        }
      }
    }
  }
  clear_game_field(matrix);
  copy_matrix(matrix, matrix_tmp);
}

void centr_rotate(int matrix[][20], int *x, int *y) {
  int x_c = 0, y_c = 0, count = 0;
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 20; ++j) {
      if (matrix[i][j] == 1) {
        x_c += i;
        y_c += j;
        count++;
      }
    }
  }
  if (count == 0) {
    *x = 0;
    *y = 0;
  } else {
    *x = x_c / count;
    *y = y_c / count;
  }
}
