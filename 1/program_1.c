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

  int ans = 0;
  int prev = -1;
  while((status = getline(&line, &len, f)) != -1) {
    int current;
    if(sscanf(line, "%d\n", &current) != 1)
      exit(EXIT_FAILURE);
    if(prev > 0 && current > prev) ans++;
    prev = current;
  }
  printf("%d\n", ans);
  return EXIT_SUCCESS;
}
