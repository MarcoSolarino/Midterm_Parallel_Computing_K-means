#include "Point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {
    cluster = -1;
    oldcluster = -1;
    minDistance = __DBL_MAX__;
}

int Point::getCluster() const {
    return cluster;
}

void Point::setCluster(int c) {
    Point::cluster = c;
}

int Point::getOldCluster() const{
    return oldcluster;
}

void Point::setOldCluster(int c) {
    Point::oldcluster = c;
}

double Point::getMinDistance() const {
    return minDistance;
}

void Point::setMinDistance(double maxDistance) {
    Point::minDistance = maxDistance;
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

void Point::setX(double xVal) {
    Point::x = xVal;
}

void Point::setY(double yVal) {
    Point::y = yVal;
}

void Point::setZ(double zVal) {
    Point::z = zVal;
}
