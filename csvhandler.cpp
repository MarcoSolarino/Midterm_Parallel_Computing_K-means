#include "csvhandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


vector<Point> readCsv() {
    vector<Point> points;
    string line;
    ifstream file("../dataset.csv", ifstream::in);

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y, z;
        getline(lineStream, bit, ',');
        x = stod(bit);
        getline(lineStream, bit, ',');
        y = stod(bit);
        getline(lineStream, bit, '\n');
        z = stod(bit);

        Point pt = Point(x, y, z);

        points.push_back(pt);
    }
    file.close();
    return points;
}

void writeCsv(vector<Point>* points, vector<Point>* centroids, int iteration) {
    ofstream fileIterations("iteration" + to_string(iteration) + ".csv", ifstream::out);
    for(auto &point : *points) {
        fileIterations << point.getX() << "," << point.getY() << "," << point.getZ() << "," << point.getCluster() << "\n";
    }
    fileIterations.close();

    ofstream fileCentroids("centroids" + to_string(iteration) + ".csv", ifstream::out);
    for(auto &centroid: *centroids) {
        fileCentroids << centroid.getX() << "," << centroid.getY() << "," << centroid.getZ() << "\n";
    }
}