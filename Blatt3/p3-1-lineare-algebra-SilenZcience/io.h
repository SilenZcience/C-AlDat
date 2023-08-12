#ifndef CALDAT_IO_H_
#define CALDAT_IO_H_

#include "point.h"
#include <stdbool.h>

Point3d read_point();
void print_point(Point3d p);
bool point_read_error();


#endif
