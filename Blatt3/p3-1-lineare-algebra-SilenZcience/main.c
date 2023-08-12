#include "point.h"
#include "io.h"
#include "pointmath.h"

#include <stdio.h>

int main(void) {
    Point3d p = read_point();
    if(point_read_error()){
        printf("Fehler: Konnte Punkt 1 nicht lesen.\n");
        return 1;
    }

    Point3d q = read_point();
    if(point_read_error()){
        printf("Fehler: Konnte Punkt 2 nicht lesen.\n");
        return 1;
    }

    printf("Quadrierte Länge von p: %.3f\n", sq_length(p));
    printf("Quadrierte Länge von q: %.3f\n", sq_length(q));
    printf("Quadrierter abstand von p und q: %.3f\n", sq_dist(p, q));
    printf("Summe von p und q: ");
    print_point(add(p,q));
    printf("\n");

    return 0;
}
