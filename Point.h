#ifndef KMEANS_POINT_H
#define KMEANS_POINT_H


class Point {
public:
    Point(double x, double y, double z);

    double getX() const;

    double getY() const;

    double getZ() const;

    void setX(double xVal);

    void setY(double yVal);

    void setZ(double zVal);

    int getCluster() const;

    void setCluster(int c);

    int getOldCluster() const;

    void setOldCluster(int c);

    double getClusterDistance() const;

    void setClusterDistance(double minDistance);

private:
    double x, y, z;
    int cluster;
    int oldcluster;
    double clusterDistance;
};


#endif //KMEANS_POINT_H
