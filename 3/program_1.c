#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define TEST_ARR_SZ 5
#define TEST_SZ 12

#define ARR_SZ 12
#define SZ 1000

int bin2dec(int *number, unsigned int comp) {
  int result = 0;
  unsigned i;
  for(i = 0; i < ARR_SZ; i++) {
    result = (result << 1) + (comp ? !number[i] : number[i]);
  }
  return result;
}

int main() {
  FILE *f = fopen("input.txt", "r");

  if(f == NULL)
    exit(EXIT_FAILURE);

  ssize_t status;
  char * line = NULL;
  size_t len;

  int cnt[ARR_SZ] = {0};

  while((status = getline(&line, &len, f)) != -1) {
    char str[ARR_SZ];
    if(sscanf(line, "%s\n", str) != 1)
      exit(EXIT_FAILURE);

    unsigned i;
    for(i = 0; i < ARR_SZ; i++) {
      if(str[i] == '1')
        cnt[i] += 1;
      else
        cnt[i] -= 1;
    }
  }

  int number[ARR_SZ] = {0};

  unsigned i;
  for(i = 0; i < ARR_SZ; i++) {
    if(cnt[i] > 0) {
      number[i] = 1;
    } else {
      number[i] = 0;
    }
  }

  printf("Answer: %d\n", bin2dec(number, 0) * bin2dec(number, 1));

  return EXIT_SUCCESS;
}
