#ifndef KMEANS_CSVHANDLER_H
#define KMEANS_CSVHANDLER_H

#endif //KMEANS_CSVHANDLER_H
#include <vector>
#include "Point.h"

using namespace std;

vector<Point> readCsv(int nd);

void writeCsv(vector<Point>* points, vector<Point>* centroids, int iteration, int k);

void writeDurationCsv(int* meanVectorDuration);

void initialize();
