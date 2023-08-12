/* Einfache Implementierung von Bruechen. Limitierung: Achtet bei keiner
 * Operation darauf, ob der darstellbare Zahlenbereich (insgesamt und in den
 * Zwischenschritten) eingehalten wird. */
#include "fraction.h"

// typedef struct Fraction {
//     int p;
//     int q;
// } Fraction;

Fraction make_fraction(int p, int q) {
    assert(q >= 0);
    return (Fraction){p, q};
}

Fraction scalar_mult(int factor, Fraction x) {
    if(factor == 0) {
        Fraction r = {0, x.q};
        return r;
    }

    int sign = (factor > 0 ? 1 : -1);
    factor = iabs(factor);

    return make_fraction(sign*factor*x.p, factor*x.q);
}

Fraction simplify(Fraction x) {
    int g = gcd(iabs(x.p), iabs(x.q));
    return make_fraction(x.p / g, x.q / g);
}

Fraction mult(Fraction x, Fraction y) {
    return simplify(make_fraction(x.p * y.p, x.q * y.q));
}

Fraction add(Fraction x, Fraction y) {
    return simplify(make_fraction(x.p*y.q + y.p*x.q, x.q*y.q));
}

bool equal(Fraction x, Fraction y) {
    return (x.p*y.q == y.p*x.q);
}

bool greater_equal(Fraction x, Fraction y) {
    return !less(x, y);
}

bool less_equal(Fraction x, Fraction y) {
    return !greater(x, y);
}

bool less(Fraction x, Fraction y) {
    return (x.p*y.q < y.p*x.q);
}

bool greater(Fraction x, Fraction y) {
    return (x.p*y.q > y.p*x.q);
}


