#include "csvhandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>


vector<Point> readCsv(int nd) {
    vector<Point> points;
    string line;
    ifstream file("../input/dataset" + to_string(nd) + ".csv", ifstream::in);

    while (getline(file, line)) {
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
    }
    file.close();

    return points;
}

void writeCsv(vector<Point>* points, vector<Point>* centroids, int iteration, int k) {
    ofstream fileIterations("../output/k" + to_string(k) + "iteration" + to_string(iteration) + ".csv", ifstream::out);
    for(auto &point : *points) {
        fileIterations << point.getX() << "," << point.getY() << "," << point.getZ() << "," << point.getCluster() << "\n";
    }
    fileIterations.close();

    ofstream fileCentroids("../output/k" + to_string(k) + "centroids" + to_string(iteration) + ".csv", ifstream::out);
    for(auto &centroid: *centroids) {
        fileCentroids << centroid.getX() << "," << centroid.getY() << "," << centroid.getZ() << "\n";
    }
    fileIterations.close();

}

void writeDurationCsv(int* meanVectorDuration) {
    ofstream fileDuration("durationSeq.csv", ifstream::out);
    for (int i=0; i<10; i++) { //TODO change 10
        fileDuration << meanVectorDuration[i] << "\n";
    }
    fileDuration.close();
}

void initialize(){
    std::filesystem::remove_all("../output/");
    std::filesystem::create_directory("../output/");
}
