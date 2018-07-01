
CFLG=-O3 -Wall
LIBS=-lglut -lGLU -lGL -lm
CLEAN=rm -f final *.o *.a

#  Generic compile and link
final:final.c display.o keys.o cube.o cylinder.o sphere.o cone.o objects.o loadtexbmp.o fatal.o errcheck.o
	gcc $(CFLG) -o $@ $^ $(LIBS)

%.o:%.c %.h common.h
	gcc $(CFLG) -c -o $@ $< $(LIBS)

#  Clean
clean:
	$(CLEAN)
