CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app.exe: main.o matrix_io.o algebra.o menu.o
	$(CC) -o $@ $^

main.o: main.c matrix_io.h algebra.h menu.h struct.h defines.h
	$(CC) $(CFLAGS) -c $<

matrix_io.o: matrix_io.c matrix_io.h menu.h struct.h defines.h
	$(CC) $(CFLAGS) -c $<

algebra.o: algebra.c algebra.h struct.h defines.h
	$(CC) $(CFLAGS) -c $<

menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe