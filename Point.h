//
// Created by Marco on 13/02/2021.
//

#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H


class Point {
public:
    Point(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    int getCluster() const;

    void setCluster(int cluster);

    double getMaxDistance() const;

    void setMaxDistance(double maxDistance);

private:
    double x, y, z;
    int cluster;
    double maxDistance;
};


#endif //KMEANS_POINT_H
