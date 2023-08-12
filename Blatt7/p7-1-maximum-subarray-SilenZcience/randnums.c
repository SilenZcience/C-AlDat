#include <stdio.h>
#include <stdlib.h>

int main(int argn, char** argv) {
  if(argn < 3) {
    fprintf(stderr, "Fehler, Parameter <n> <seed> erwartet.\n");
    return 1;
  }

  srand(atoi(argv[2]));
  char *end = NULL;
  unsigned long n = strtoul(argv[1], &end, 10);
  printf("%lu\n", n);


  for(unsigned long i=0; i < n; ++i) {
      int sign = (rand() % 2 == 0 ? 1 : -1);
      printf("%d\n", sign * (rand() % 1000));
  }

  return 0;
}
