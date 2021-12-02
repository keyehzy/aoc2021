CFLAGS = -W -Wall -Wextra -O0 -g -ansi
LDLIBS = -lm

program : program.c

run : program
	./$< > output

clean :
	$(RM) program *.o output.*
