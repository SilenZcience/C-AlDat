#ifndef P3_2_FRACTION_
#define P3_2_FRACTION_

#include "genmath.h"
#include <stdbool.h>
#include <assert.h>

typedef struct Fraction {
    int p;
    int q;
} Fraction;

Fraction make_fraction(int p, int q);
Fraction scalar_mult(int factor, Fraction x);
Fraction simplify(Fraction x);
Fraction mult(Fraction x, Fraction y);
Fraction add(Fraction x, Fraction y);
bool equal(Fraction x, Fraction y);
bool greater_equal(Fraction x, Fraction y);
bool less_equal(Fraction x, Fraction y);
bool less(Fraction x, Fraction y);
bool greater(Fraction x, Fraction y);

#endif