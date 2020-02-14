CC = gcc
CFLAGS = -std=c99 -Wall -Werror

MAIN = main
FUNC_C = $(wildcard src/*.c)

OBJ_MAIN = $(patsubst %.c, %.o, $(MAIN).c)
OBJ_SRC = $(patsubst %.c, %.o, $(wildcard $(FUNC_C)))


 

app.exe: $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) -o $@ $^


run: app.exe
	./app


clean:
	rm -f *.o *.exe ./src/*.o
