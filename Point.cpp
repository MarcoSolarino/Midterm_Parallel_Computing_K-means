//
// Created by Marco on 13/02/2021.
//

#include "Point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {
    cluster = -1;
    maxDistance = __DBL_MAX__;
}

int Point::getCluster() const {
    return cluster;
}

void Point::setCluster(int cluster) {
    Point::cluster = cluster;
}

double Point::getMaxDistance() const {
    return maxDistance;
}

void Point::setMaxDistance(double maxDistance) {
    Point::maxDistance = maxDistance;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

double Point::getZ() const {
    return z;
}

void Point::setX(double x) {
    Point::x = x;
}

void Point::setY(double y) {
    Point::y = y;
}

void Point::setZ(double z) {
    Point::z = z;
}
