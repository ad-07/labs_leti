# CC = gcc

# SRC = cw.c functions.c sentence_io.c text_io.c
# OBJ = $(SRC:.c=.o)

all: cw.o functions.o sentence_io.o text_io.o
	gcc cw.o functions.o sentence_io.o text_io.o -o cw
	make clean
cw.o: cw.c functions.h sentence_io.h text_io.h
	gcc -c cw.c

functions.o: functions.c functions.h
	gcc -c functions.c

sentence_io.o: sentence_io.c sentence_io.h
	gcc -c sentence_io.c

text_io.o: text_io.c text_io.h
	gcc -c text_io.c

clean:
	rm *.o