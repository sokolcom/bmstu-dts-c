CC = gcc
CFLAGS = -std=c99 -Wall -Werror

DEFINES = struct.h define.h

LIST_H = stack_list.h
ARRAY_H = stack_array.h


app.exe: main.o stack_list.o stack_array.o menu.o stats.o
	$(CC) -o $@ $^

main.o: main.c $(DEFINES) $(LIST_H) $(ARRAY_H) menu.h stats.h 
	$(CC) $(CFLAGS) -c $<

stack_list.o: stack_list.c $(DEFINES) $(LIST_H)
	$(CC) $(CFLAGS) -c $<

stack_array.o: stack_array.c $(DEFINES) $(ARRAY_H)
	$(CC) $(CFLAGS) -c $<

stats.o: stats.c stats.h $(DEFINES) $(LIST_H) $(ARRAY_H)
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c menu.h define.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe