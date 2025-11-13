CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -O2 -Iinclude
ARFLAGS = rcs

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = test

LIB_NAME = lib/libsimplify.a
OBJS = $(OBJ_DIR)/simplify.o
TEST_BIN = $(TEST_DIR)/run
TEST_OBJ = $(OBJ_DIR)/test.o

.PHONY: all lib test clean

all: lib test

lib: $(LIB_NAME)

$(LIB_NAME): $(OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/simplify.o: $(SRC_DIR)/simplify.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/test.o: $(TEST_DIR)/test.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN)
