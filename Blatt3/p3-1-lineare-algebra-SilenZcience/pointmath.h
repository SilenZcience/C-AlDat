#ifndef CALDAT_POINTMATH_H_
#define CALDAT_POINTMATH_H_

#include "point.h"
#include <math.h>

Point3d add(Point3d p, Point3d q);
Point3d mult(Point3d p, double factor);
double sq_length(Point3d p);
double sq_dist(Point3d p, Point3d q);

#endif
