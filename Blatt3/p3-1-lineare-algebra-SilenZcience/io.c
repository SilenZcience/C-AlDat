#include "debug.h"
#include "io.h"
#include <stdio.h>

bool _read_error = false;

Point3d read_point() {
    Point3d p = {0.0, 0.0, 0.0};
    _read_error = false;

    if(scanf("%lf", &p.x) != 1){
        _read_error = true;
        ca_dbg(printf("[Debug] Fehler beim Lesen von x-Koordinate\n"));
        return p;
    }

    if(scanf("%lf", &p.y) != 1){
        _read_error = true;
        ca_dbg(printf("[Debug] Fehler beim Lesen von y-Koordinate\n"));
        return p;
    }

    if(scanf("%lf", &p.z) != 1){
        _read_error = true;
        ca_dbg(printf("[Debug] Fehler beim Lesen von z-Koordinate\n"));
        return p;
    }

    ca_dbg(printf("[Debug] Punkt [%.3lf, %.3lf, %.3lf] gelesen.\n", p.x, p.y, p.z));

    return p;
}

void print_point(Point3d p) {
    printf("[%.3lf, %.3lf, %.3lf]", p.x, p.y, p.z);
}

bool point_read_error() {
    return _read_error;
}
