#include "pointmath.h"

Point3d add(Point3d p, Point3d q) {
    Point3d r = {p.x + q.x, p.y + q.y, p.z + q.z};
    return r;
}

Point3d mult(Point3d p, double factor) {
    Point3d r = {factor*p.x, factor*p.y, factor*p.z };
    return r;
}

double sq_length(Point3d p) {
    return p.x*p.x + p.y*p.y + p.z*p.z;
}

double sq_dist(Point3d p, Point3d q) {
    return sq_length(add(p, mult(q, -1.0)));
}
