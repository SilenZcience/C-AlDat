
#include <stdio.h>

int main(void) {
    // print table headers
    printf("Zahl Quadrat Kehrwert\n");

    for (int i = 1; i <= 12; i++)
    {
        /*
        %4d -> decimal right aligned to 4 chars
        %7d -> decimal right aligned to 7 chars
        %8.6f -> float right aligned to 8 chars, with 6 chars after decimal point.
        (decimal point counts as 1 char itself)
        we need to cast 1/i to double (or float), otherwise the result will always be zero.
        */
        printf("%4d %7d %8.6f\n", i, i*i, (double) 1/i);
    }
    
    return 0;
}