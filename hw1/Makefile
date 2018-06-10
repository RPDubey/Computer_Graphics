
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
CLEAN=rm -f hw1 *.o *.a

#  Generic compile and link
hw1:hw1.c display.o keys.o
	gcc $(CFLG) -o $@ $^ $(LIBS)

%.o:%.c %.h
	gcc $(CFLG) -c -o $@ $< $(LIBS)

#  Clean
clean:
	$(CLEAN)
