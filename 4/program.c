#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_SZ 3
#define TEST_NUMS 27

#define SZ 100
#define NUMS 100

#define ROW 5
#define COL 5

int draws[NUMS];
int boards[SZ][ROW][COL];
int marked[SZ][ROW][COL];
int already_won[SZ];

void mark_board(int k, int n) {
  unsigned i, j;
  for(i = 0; i < ROW; i++) {
    for(j = 0; j < COL; j++) {
      if(boards[k][i][j] == n)
        marked[k][i][j] = 1;
    }
  }
}

void mark_all_boards(int n) {
  unsigned k;
  for(k = 0; k < SZ; k++)
    mark_board(k, n);
}

int check_rows(int k) {
  unsigned i, j;
  for(i = 0; i < ROW; i++) {
    int good = 1;
    for(j = 0; j < COL; j++) {
      if(marked[k][i][j] == 0) {
        good = 0;
        break;
      }
    }
    if(good) return 1;
  }
  return 0;
}

int check_cols(int k) {
  unsigned i, j;
  for(i = 0; i < ROW; i++) {
    int good = 1;
    for(j = 0; j < COL; j++) {
      if(marked[k][j][i] == 0) {
        good = 0;
        break;
      }
    }
    if(good) return 1;
  }
  return 0;
}

int check_board(int k) {
  return check_rows(k) || check_cols(k);
}

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = malloc(1024);
  size_t len;

  unsigned i, j, k;

  if(getline(&line, &len, f) == -1)
    exit(EXIT_FAILURE);

  for(i = 0; i < NUMS; i++) {
    char *beg = line;
    char *end = NULL;
    draws[i] = strtol(line, &end, 10);
    line += end - beg + 1;
  }

  for(i = 0; i < SZ; i++) {

    for(j = 0; j < ROW; j++) {
      if(getline(&line, &len, f) == -1)
        exit(EXIT_FAILURE);

      if(strcmp(line, "\n") == 0)
        if(getline(&line, &len, f) == -1)
          exit(EXIT_FAILURE);

      if(sscanf(line, "%d %d %d %d %d\n", &boards[i][j][0], &boards[i][j][1],
                &boards[i][j][2], &boards[i][j][3], &boards[i][j][4]) != COL)
        exit(EXIT_FAILURE);
    }
  }

  memset(marked, 0, sizeof(int) * SZ * ROW * COL);
  memset(already_won, 0, sizeof(int) * SZ);

  unsigned l;
  for(l = 0; l < NUMS; l++) {
    int draw = draws[l];
    mark_all_boards(draw);

    for(k = 0; k < SZ; k++) {
      if(already_won[k]) continue;

      int good = check_board(k);
      int unmarked = 0;

      if(good) {
        for(i = 0; i < ROW; i++) {
          for(j = 0; j < COL; j++) {
            if(marked[k][i][j] == 0)
              unmarked += boards[k][i][j];
          }
        }
        printf("Answer: %d\n", draw * unmarked);
        already_won[k] = 1;
      }
    }
  }
  return EXIT_SUCCESS;
}
