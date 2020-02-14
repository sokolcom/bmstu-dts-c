
CC = gcc
CFLAGS = -std=c99 -Wall -Werror

MAIN = main
FUNC_C = $(wildcard src/*.c)

OBJ_MAIN = $(patsubst %.c, %.o, $(MAIN).c)
OBJ_SRC = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))



DATA = data.gv
RESULT = result.gv
PNG = graph.png
PNG_RESULT = result.png
# PATH = /C/"Program Files (x86)"/Graphviz2.38/bin/

run: app.exe draw

app.exe: $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) -o $@ $^

draw:
	/C/"Program Files (x86)"/Graphviz2.38/bin/dot.exe -Tpng $(DATA) -o $(PNG)
	/C/"Program Files (x86)"/Graphviz2.38/bin/dot.exe -Tpng $(RESULT) -o $(PNG_RESULT)



clean:
	rm *.o *.exe ./src/*.o *.png
