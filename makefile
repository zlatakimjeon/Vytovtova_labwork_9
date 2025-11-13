CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = test

LIB = $(LIB_DIR)/libsimplify.a
LIB_OBJS = $(OBJ_DIR)/simplify.o

TEST_SRC = $(TEST_DIR)/test.c
TEST_OBJ = $(OBJ_DIR)/test.o
TEST_BIN = $(TEST_DIR)/run

all: lib test

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(OBJ_DIR)/simplify.o: $(SRC_DIR)/simplify.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

lib: $(LIB_DIR) $(LIB_OBJS)
	ar rcs $(LIB) $(LIB_OBJS)

$(OBJ_DIR)/test.o: $(TEST_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ) $(LIB)
	$(CC) $^ -L$(LIB_DIR) -lsimplify -o $(TEST_BIN)

# Очистка
clean:
	if exist $(OBJ_DIR)\*.o del /Q $(OBJ_DIR)\*.o
	if exist $(LIB_DIR)\libsimplify.a del /Q $(LIB_DIR)\libsimplify.a
	if exist $(TEST_DIR)\run del /Q $(TEST_DIR)\run
