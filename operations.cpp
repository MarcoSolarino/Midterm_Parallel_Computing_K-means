#include "operations.h"
#include <cmath>
#include <vector>

using namespace std;

double distance3d(double x1, double x2, double x3, double y1, double y2, double y3) {
    // compute euclidean distance
    double distance = sqrt(pow(x1 - y1, 2) + pow(x2 - y2, 2) + pow(x3 - y3, 2));
    return distance;
}

double distance3d(Point p1, Point p2){
    double x1 = p1.getX();
    double x2 = p1.getY();
    double x3 = p1.getZ();
    double y1 = p2.getX();
    double y2 = p2.getY();
    double y3 = p2.getZ();
    return distance3d(x1, x2, x3, y1, y2, y3);
}

double mean(vector<double> *v){
    double mean = 0;
    for (auto &value : *v){
        mean += value;
    }
    mean = mean/v->size();
    return mean;
}
