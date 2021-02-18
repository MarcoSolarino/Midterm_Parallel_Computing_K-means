#include "Point.h"

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {
    cluster = -1;
    oldcluster = -1;
    clusterDistance = __DBL_MAX__;
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

double Point::getClusterDistance() const {
    return clusterDistance;
}

void Point::setClusterDistance(double distance) {
    Point::clusterDistance = distance;
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
