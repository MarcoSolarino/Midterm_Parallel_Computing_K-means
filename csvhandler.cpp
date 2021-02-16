#include "csvhandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Point.h"

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

void writeCsv(vector<Point>* points, int iteration) {
    ofstream file("iteration" + to_string(iteration) + ".csv", ifstream::out);
    for(auto &point : *points) {
        file << point.getX() << "," << point.getY() << "," << point.getZ() << "," << point.getCluster() << "\n";
    }
    file.close();
}