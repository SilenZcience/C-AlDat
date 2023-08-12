#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argn, char** argv) {
  if(argn < 2) {
    fprintf(stderr, "Fehler, Parameter <n> (Anzahl Schlüssel) erwartet.\n");
    return 1;
  }

  const unsigned int seed = time(NULL);
  srand(seed);
  char *end = NULL;
  unsigned long n = strtoul(argv[1], &end, 10);
  printf("%lu\n", n);


  for(unsigned long i=0; i < n; ++i) {
      int sign = (rand() % 2 == 0 ? 1 : -1);
      printf("%d\n", sign * (rand() % 1000));
  }

  return 0;
}
