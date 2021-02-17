#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H


class Point {
public:
    Point(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    void setX(double x);

    void setY(double y);

    void setZ(double z);

    int getCluster() const;

    void setCluster(int cluster);

    int getOldCluster() const;

    void setOldCluster(int cluster);

    double getMinDistance() const;

    void setMinDistance(double minDistance);

private:
    double x, y, z;
    int cluster;
    int oldcluster;
    double minDistance;
};


#endif //KMEANS_POINT_H
