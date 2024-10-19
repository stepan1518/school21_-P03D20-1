wgcc = gcc -Wall -Werror -Wextra
BUILD_PATH = ../build/graph

all:	graph.o draw.o
	$(wgcc) -o $(BUILD_PATH) $^

graph.o:
	$(wgcc) -c graph.c

draw.o:
	$(wgcc) -c draw.c

clean:
	rm $(BUILD_PATH) *.o
run:
	clear
	$(BUILD_PATH)