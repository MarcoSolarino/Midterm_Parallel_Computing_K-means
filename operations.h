#ifndef KMEANS_DISTANCE_H
#define KMEANS_DISTANCE_H

#endif //KMEANS_DISTANCE_H

#include "Point.h"
#include <vector>

double distance3d(double x1, double x2, double x3, double y1, double y2, double y3);

double distance3d(Point p1, Point p2);

double mean(const std::vector<double>& v);