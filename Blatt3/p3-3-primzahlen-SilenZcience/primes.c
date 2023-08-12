#include "primes.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

void print_primes(int n) {
    
    /* declare an array primes of type bool of length n+1
    index i identifies the number i as a prime.
    by default we instantiate all values as true/prime */
    bool primes[n + 1];
    for (int i = 0; i <= n; i++) {
        primes[i] = true;
    }
    
    /* index 1 should be false, since 1 is not a prime
    but we will start the for-loops with 2 anyways.
    same counts for index 0... */

    /* we can stop the for-loop when prime <= sqrt(n)
    or equivalent to it prime*prime <= n ...
    this algorithm is rather well known ... */
    for (int prime = 2; prime * prime <= n; prime++) {
        // if it is not a prime we do not set the multiples
        // to not-a-prime.
        if (!primes[prime])
            continue;
        
        // otherwise, if it is a prime...
        // we update all multiples to be not-a-prime.
        for (int p = prime * prime; p <= n; p += prime) {
            primes[p] = false;
        }
    }

    // simply print out every prime (prime[i] == true)
    for (int prime = 2; prime <= n; prime++) {
        if (primes[prime]) {
            printf("%d\n", prime);
        }
    }
}
