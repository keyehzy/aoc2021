#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  while((status = getline(&line, &len, f)) != -1) {
    int number;
    if(sscanf(line, "%d\n", &number) != 1)
      exit(EXIT_FAILURE);
  }
  
  return EXIT_SUCCESS;
}
