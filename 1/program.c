#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define K 3
#define SZ 2000
#define TEST_SZ 10

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  int data[SZ], index = 0;

  while((status = getline(&line, &len, f)) != -1) {
    int number;
    if(sscanf(line, "%d\n", &number) != 1)
      exit(EXIT_FAILURE);
    data[index++] = number;
  }

  int curr[SZ];
  int ans = 0;

  unsigned i, j;
  for(i = 0; i < SZ - K + 1; i++) {
    curr[i] = 0;

    for(j = 0; j < K; j++) {
      curr[i] += data[i + j];
    }

    if(i > 0 && curr[i] > curr[i-1]) {
      printf("%d\n", curr[i]);
      ans += 1;
    }
  }

  printf("%d\n", ans);

  return EXIT_SUCCESS;
}
