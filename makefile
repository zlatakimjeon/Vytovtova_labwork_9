CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -O2 -Iinclude
ARFLAGS = rcs

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
TEST_DIR = test

LIB_NAME = $(LIB_DIR)/libsimplify.a
OBJS = $(OBJ_DIR)/simplify.o
TEST_OBJ = $(OBJ_DIR)/test.o
TEST_BIN = $(TEST_DIR)/run

.PHONY: all clean rebuild test

all: $(TEST_BIN)

$(TEST_BIN): $(TEST_OBJ) $(LIB_NAME)
	@echo "Linking $@..."
	$(CC) $(CFLAGS) $^ -o $@

$(LIB_NAME): $(OBJS) | $(LIB_DIR)
	@echo "Creating static library $@..."
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/simplify.o: $(SRC_DIR)/simplify.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test.o: $(TEST_DIR)/test.c | $(OBJ_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

clean:
	@echo "Cleaning..."
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN)

rebuild: clean all

test: all
	@echo "Running tests..."
	./$(TEST_BIN)
