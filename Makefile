CC := gcc
CFLAGS := -I includes -std=c11 -Wall -Werror -Wextra -D_POSIX_C_SOURCE=200809L -I/opt/homebrew/include
TETRIS_SRC_DIR := brick_game/tetris
CLI_SRC_DIR := gui/cli
OUT_DIR := src/out
CHECK_LIBS= -lcheck -L/opt/homebrew/lib
SRC_TEST := brick_game/tetris/backend.c test.c gui/cli/cli.c brick_game/tetris/helper.c
LFLAGS_COVERAGE=-lgcov --coverage

TETRIS_SRCS := $(wildcard $(TETRIS_SRC_DIR)/*.c)
CLI_SRCS := $(wildcard $(CLI_SRC_DIR)/*.c)

TETRIS_OBJS := $(patsubst %.c, %.o, $(TETRIS_SRCS))
CLI_OBJS := $(patsubst %.c, %.o, $(CLI_SRCS))

OS := $(shell uname -s)

ifeq ($(OS), Linux)
    CHECK_LIBS += -lsubunit -lrt -lpthread -lm -lncurses
endif

ifeq ($(OS), Darwin)
    CHECK_LIBS += -lncurses
endif

all: clean install
	./tetris

tetris: $(TETRIS_OBJS) $(CLI_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

test:
	$(CC) $(CFLAGS) $(SRC_TEST) -o test $(CHECK_LIBS) -lncurses
	./test

install: clean tetris

uninstall:
	rm -rf tetris

dvi:
	open read_me.md

gcov_report:
	$(CC) $(CFLAGS) $(SRC_TEST) -o test $(CHECK_LIBS) -lncurses --coverage
	./test 
	lcov -t "gcov" -o gcov.info -c -d . 
	lcov -r gcov.info '/usr/include/*' -o gcov_filtered.info
	genhtml -o report gcov_filtered.info
	open report/index.html

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

dist: clean
	mkdir -p ./bin
	tar -cvzf ./brick_game_v1.tgz makefile  ./brick_game/tetris/* ./gui/cli/*  read_me.md tests/test.c high_score.txt
	mv brick_game_v1.tgz ./bin/

clang:
	clang-format -i -style=Google $(TETRIS_SRC_DIR)/*.c $(CLI_SRC_DIR)/*.c

clang-check:
	clang-format -n -style=Google $(TETRIS_SRC_DIR)/*.c $(CLI_SRC_DIR)/*.c

clean:
	$(RM) $(CLI_SRC_DIR)/*.o $(TETRIS_SRC_DIR)/*.o tetris
	rm -rf gcov.info
	rm -rf report
	rm -rf test
	rm -rf ./bin
	rm -rf tetris
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

.PHONY: all dvi gcov_report test clean install uninstall dist