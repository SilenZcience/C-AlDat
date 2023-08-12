#include "genmath.h"

// Achtung, iabs(MIN_INT) liefert MIN_INT
int iabs(int a) {
    return (a > 0 ? a : (-1)*a);
}

/* berechnet den groessten gemeinsamen Teiler von a,b >= 0 */
int gcd(int a, int b) {
    // euklidischer Algorithmus
    assert(a >= 0);
    assert(b >= 0);

    if(a == 0) return b;

    while(b > 0) {
        int q = a % b;
        a = b;
        b = q;
    }

    return a;
}
