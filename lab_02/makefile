CC = gcc
CFLAGS = -std=c99 -Wall -Werror

app.exe: main.o input_output.o sorts.o file_parsing.o
	$(CC) -o $@ $^

main.o: main.c input_output.h sorts.h file_parsing.h data_struct.h
	$(CC) $(CFLAGS) -c $<

input_output.o: input_output.c input_output.h
	$(CC) $(CFLAGS) -c $<

sorts.o: sorts.c sorts.h
	$(CC) $(CFLAGS) -c $<

file_parsing.o: file_parsing.c file_parsing.h input_output.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe