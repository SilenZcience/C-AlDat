#include <stdio.h>
#include "primes.h"

int main(void) {
    unsigned int n = 0;
    if(scanf("%u", &n) != 1) {
        printf("Fehler, ganze Zahl erwartet\n");
        return 1;
    }

    print_primes(n);

    return 0;
}
