#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define TEST_ARR_SZ 5
#define TEST_SZ 12

#define ARR_SZ 12
#define SZ 1000

static int all[SZ][ARR_SZ] = {0};

int bin2dec(int *number, unsigned int comp) {
  int result = 0;
  unsigned i;
  for(i = 0; i < ARR_SZ; i++) {
    result = (result << 1) + (comp ? !number[i] : number[i]);
  }
  return result;
}

int find(unsigned int comp) {
  int mark_entries[SZ], good_entries[SZ];
  unsigned i, j, good_left = SZ;
  for(j = 0; j < SZ; j++) {
    mark_entries[j] = 1;
    good_entries[j] = 1;
  }

  unsigned col, row;
  for(col = 0; col < ARR_SZ; col++) {

    if(good_left == 1)
      break;

    int sum = 0;

    for(row = 0; row < SZ; row++) {
      if(!good_entries[row]) continue;
      sum += all[row][col];
    }

    int most_common;
    if(comp) {
      most_common = (sum >= 0) ? 1 : -1;
    } else {
      most_common = (sum < 0) ? 1 : -1;
    }

    for(row = 0; row < SZ; row++) {
      if(!good_entries[row]) continue;
      if(all[row][col] != most_common) {
        mark_entries[row] = 0;
        good_left--;
      }
    }

    for(j = 0; j < SZ; j++) {
      good_entries[j] = mark_entries[j];
    }
  }

  int found[ARR_SZ];
  for(i = 0; i < SZ; i++) {
    if(good_entries[i]) {
      for(j = 0; j < ARR_SZ; j++) {
        found[j] = all[i][j] > 0 ? 1 : 0;
      }
    }
  }
  return bin2dec(found, 0);
}

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  unsigned j = 0;
  while((status = getline(&line, &len, f)) != -1) {
    char str[ARR_SZ];
    if(sscanf(line, "%s\n", str) != 1)
      exit(EXIT_FAILURE);

    unsigned i;
    for(i = 0; i < ARR_SZ; i++) {
      if(str[i] == '1')
        all[j][i] = 1;
      else
        all[j][i] = -1;
    }
    j++;
  }

  printf("Answer: %d\n", find(0) * find(1));

  return EXIT_SUCCESS;
}
