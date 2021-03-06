#include "csvhandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>


vector<Point> readCsv(int n) {
    vector<Point> points;
    string line;
    ifstream file("../input/dataset.csv", ifstream::in);

    int i = 0;
    while (getline(file, line) && i < n) {
        stringstream lineStream(line);
        string bit;
        float x, y, z;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, ',');
        y = stof(bit);
        getline(lineStream, bit, '\n');
        z = stof(bit);

        Point pt = Point(x, y, z);
        points.push_back(pt);

        i ++;
    }
    file.close();

    return points;
}

void writeCsv(vector<Point>* points, vector<Point>* centroids) {
    ofstream filePoints("../output/points.csv", ifstream::out);
    for(auto &point : *points) {
        filePoints << point.getX() << "," << point.getY() << "," << point.getZ() << "," << point.getCluster() << "\n";
    }
    filePoints.close();

    ofstream fileCentroids("../output/centroids.csv", ifstream::out);
    for(auto &centroid: *centroids) {
        fileCentroids << centroid.getX() << "," << centroid.getY() << "," << centroid.getZ() << "\n";
    }
    filePoints.close();
}

void initialize(){
    std::filesystem::remove_all("../output/");
    std::filesystem::create_directory("../output/");
}
