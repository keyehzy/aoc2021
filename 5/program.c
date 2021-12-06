#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_SZ 10
#define SZ 1000

int board[SZ][SZ];

void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  memset(board, 0, sizeof(int) * SZ * SZ);

  while((status = getline(&line, &len, f)) != -1) {
    int x1, y1, x2, y2;
    if(sscanf(line, "%d,%d -> %d,%d\n", &x1, &y1, &x2, &y2) != 4)
      exit(EXIT_FAILURE);

    if(x1 == x2) {
      if(y1 > y2) swap(&y2, &y1);

      int i;
      for(i = y1; i <= y2; i++)
        board[x1][i] += 1;

    } else if(y1 == y2) {
      if(x1 > x2) swap(&x2, &x1);

      int i;
      for(i = x1; i <= x2; i++)
        board[i][y1] += 1;

    } else {

      if(x1 > x2) {
        swap(&x2, &x1);
        swap(&y2, &y1);
      }

      int sign_y = (y2-y1>0) - (y2-y1<0);

      int i;
      for(i = 0; i <= x2-x1; i++) {
          board[x1 + i][y1 + sign_y * i] += 1;
      }
    }
  }

  int sum = 0;
  int i, j;
  for(i = 0; i < SZ; i++) {
    for(j = 0; j < SZ; j++) {
      printf("%d ", board[j][i]);
      sum += (board[i][j] > 1);
    }
    printf("\n");
  }

  printf("Answer: %d\n", sum);

  return EXIT_SUCCESS;
}
