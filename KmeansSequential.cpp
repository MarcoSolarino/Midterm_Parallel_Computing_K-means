#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>

#include "Point.h"
#include "csvhandler.h"
#include "operations.h"


using namespace std::chrono;
using namespace std;

void updateCentroids(vector<Point> *points, vector<Point> *centroids, int k){
    vector<int> numPoints(k, 0); // keep trace of the number of points in each cluster
    vector<float> sumX(k, 0.0);
    vector<float> sumY(k, 0.0);
    vector<float> sumZ(k, 0.0);

    for (auto &point : *points) {
        int pointCluster = point.getCluster();
        sumX.at(pointCluster) += point.getX();
        sumY.at(pointCluster) += point.getY();
        sumZ.at(pointCluster) += point.getZ();
        numPoints.at(pointCluster)++;
    }

    for (int i = 0; i < k; i++){
        float newX = sumX.at(i) / numPoints.at(i);
        float newY = sumY.at(i) / numPoints.at(i);
        float newZ = sumZ.at(i) / numPoints.at(i);

        centroids->at(i).setX(newX);
        centroids->at(i).setY(newY);
        centroids->at(i).setZ(newZ);
    }

}

void assignClusters(vector<Point> *points, vector<Point> *centroids, int k){
    for (auto &point : *points) {
        point.setClusterDistance(__DBL_MAX__);
        point.setOldCluster(point.getCluster());

        float clusterDistance = point.getClusterDistance();  // the calculateDistance between its actual cluster' centroid

        for (int j = 0; j < k; j++) {
            float distance = calculateDistance(centroids->at(j), point);
            if (distance < clusterDistance) {
                point.setClusterDistance(distance);
                clusterDistance = distance;
                point.setCluster(j);
            }
        }
    }

}

vector<Point> selectRandom(vector<Point> *points, int n, int k){
    vector<Point> centroids;

    srand (time(NULL));
    int randIdx = rand() % n;
    for(int i = 0; i < k; i ++ ){
        int offset = i * (n / k);
        Point c = points->at((randIdx + offset) % n);
        centroids.push_back(c);
    }
    return centroids;
}

void kMeans(vector<Point> *points, int iterations, int n, int k) {

    vector<Point> centroids = selectRandom(points, n, k);

    for(int i = 0 ; i < iterations; i++) {
        assignClusters(points, &centroids, k);
        updateCentroids(points, &centroids, k);
    }

    writeCsv(points, &centroids);
}

int main(int argc, char** argv) {
    initialize();
    int clusters = stoi(argv[1]);
    int iterations = stoi(argv[2]);
    int n = 1000;
    vector<Point> points = readCsv(n);

    auto start = high_resolution_clock::now();
    kMeans(&points, iterations, n, clusters);
    auto end = high_resolution_clock::now();

    auto ms_int = duration_cast<milliseconds>(end - start);
    return ms_int.count();
}
