#include "fraction.h"
#include "io.h"

#include <stdio.h>

int main(void) {
    Fraction x;
    Fraction y;

    if(scanf("%d %d", &x.p, &x.q) != 2) {
        printf("Fehler, zwei ganze Zahlen erwartet.\n");
        return 1;
    }

    if(scanf("%d %d", &y.p, &y.q) != 2) {
        printf("Fehler, zwei ganze Zahlen erwartet.\n");
        return 1;
    }

    printf("x = "); print_fraction(x); printf("\n");
    printf("y = "); print_fraction(y); printf("\n");


    if(less(x,y)) {
        printf("%d/%d ist kleiner als %d/%d\n", x.p, x.q, y.p, y.q);
    }
    else if(greater(x,y)) {
        printf("%d/%d ist groesser als %d/%d\n", x.p, x.q, y.p, y.q);
    }
    else {
        printf("%d/%d ist gleich %d/%d\n", x.p, x.q, y.p, y.q);
    }

    Fraction s = add(x, y);
    printf("%d/%d + %d/%d = %d/%d\n", x.p, x.q, y.p, y.q, s.p, s.q);

    Fraction m = mult(x, y);
    printf("%d/%d + %d/%d = %d/%d\n", x.p, x.q, y.p, y.q, m.p, m.q);

    return 0;
}
