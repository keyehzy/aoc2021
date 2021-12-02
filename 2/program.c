#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define SZ 1000
#define TEST_SZ 6

typedef enum {
  forward = 'f',
  up = 'u',
  down = 'd',
} command_name;

typedef struct {
  command_name name;
  unsigned unit;
} command;

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  command data[SZ];
  unsigned index = 0;

  while((status = getline(&line, &len, f)) != -1) {
    char name[128];
    int number;
    if(sscanf(line, "%s %d\n", name, &number) != 2)
      exit(EXIT_FAILURE);
    data[index++] = (command) {.name = (command_name) name[0], .unit = number};
  }

  int position = 0;
  int depth = 0;
  int aim = 0;

  unsigned i;
  for(i = 0; i < SZ; i++) {
    command cmd = data[i];
    switch(cmd.name) {
      case forward:
        position += cmd.unit;
        depth += aim * cmd.unit;
        break;
      case up:
        aim -= cmd.unit;
        break;
      case down:
        aim += cmd.unit;
        break;
    }
  }

  printf("%d\n", position * depth);

  return EXIT_SUCCESS;
}
