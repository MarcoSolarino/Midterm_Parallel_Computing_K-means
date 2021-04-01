#include "operations.h"
#include <cmath>
#include <vector>

using namespace std;

float calculateDistance(Point p1, Point p2){
    float x1 = p1.getX();
    float x2 = p1.getY();
    float x3 = p1.getZ();
    float y1 = p2.getX();
    float y2 = p2.getY();
    float y3 = p2.getZ();
    float distance = sqrt(pow(x1 - y1, 2) + pow(x2 - y2, 2) + pow(x3 - y3, 2));
    return distance;
}
