#ifndef KMEANS_CSVHANDLER_H
#define KMEANS_CSVHANDLER_H

#endif //KMEANS_CSVHANDLER_H
#include <vector>
#include "Point.h"

using namespace std;

vector<Point> readCsv();

void writeCsv(vector<Point>* points, int iteration);
