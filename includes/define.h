#ifndef DEFINE_H_
#define DEFINE_H_

#define WIN_INIT(time)     \
  {                        \
    initscr();             \
    noecho();              \
    cbreak();              \
    nodelay(stdscr, TRUE); \
    curs_set(FALSE);       \
    keypad(stdscr, TRUE);  \
  }

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)
#define CLEAR_BACKPOS(y, x) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), ' ')

#define GET_USER_INPUT getch()

#define INTRO_MESSAGE_T "T"
#define INTRO_MESSAGE_E "E"
#define INTRO_MESSAGE_R "R"
#define INTRO_MESSAGE_I "I"
#define INTRO_MESSAGE_S "S"
#define INTRO_MESSAGE_LEN 6

#define PAUSE_MESSAGE "PAUSE"
#define PAUSE_MESSAGE_LEN 5

#define LEVELNAME_MAX 5

#define ROWS_MAP 20
#define COLS_MAP 10

#define BOARDS_BEGIN 2

#define INITIAL_TIMEOUT 150

#define BOARD_N 19
#define BOARD_M 10
#define HUD_WIDTH 12

#define BEGIN_X 3
#define END_X 13
#define BEGIN_Y 3

#define ESCAPE 27
#define ENTER_KEY 10

#define BEGIN_NEXT_INFO_X 20
#define BEGIN_NEXT_INFO_Y 16

#endif  // DEFINE_H_