CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra
BUILD_PATH = ../build/

# "build" target build executable file of the app graph 
build: all

# "rebuild" target clean and build the app from scratch
rebuild: clean build

# "all" target build executable file of the app graph
all: main.c stack/stack.c parser/parser.c graph/graph.c calculation/calculation.c
	$(CC) $(FLAGS) -o $(BUILD_PATH)graph main.c stack/stack.c parser/parser.c graph/graph.c calculation/calculation.c

# "clean" target delete everything in build directory
clean:
	rm -rf $(BUILD_PATH)*