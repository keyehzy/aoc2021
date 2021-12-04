CFLAGS = -W -Wall -Wextra -O0 -g -ggdb -ansi
LDLIBS = -lm

program : program.c

run : program
	./$< > output

clean :
	$(RM) program *.o output.*
