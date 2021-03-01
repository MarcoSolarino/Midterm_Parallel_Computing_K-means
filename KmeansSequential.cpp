#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Point.h"
#include "csvhandler.h"
#include "operations.h"


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

//returns true if some point changed cluster
bool assignClusters(vector<Point> *points, vector<Point> *centroids, int k){
    bool clustersChanged = false;
    for (auto &point : *points) {
        point.setClusterDistance(__DBL_MAX__);
        point.setOldCluster(point.getCluster());

        float clusterDistance = point.getClusterDistance();  // the distance between its actual cluster' centroid
        int clusterIndex = point.getCluster(); // keep trace of witch cluster the point is

        for (int j = 0; j < k; j++) {
            float distance = distance3d(centroids->at(j), point);
            if (distance < clusterDistance) {
                point.setClusterDistance(distance);
                clusterDistance = distance;
                point.setCluster(j);
                clusterIndex = j;
            }
        }

        if (point.getCluster() != point.getOldCluster()) {
            clustersChanged = true;
        }
    }

    return clustersChanged;
}

void kMeans(vector<Point> *points, int epochsLimit, int k) {
    // Step 1: Create k random centroids
    vector<Point> centroids;
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distribution(0, points->size() - 1);
    int lastEpoch = 0;
    for(int i=0; i<k; i++) {
        int randomLocation = distribution(engine);
        Point c = points->at(randomLocation);
        centroids.push_back(c);
    }

    for(int ep = 0 ; ep < epochsLimit; ep++) {
        if (ep != 0) {
            writeCsv(points, &centroids, ep, k);
        }

        //Step 2: assign dataPoints to the clusters, based on the distance from its centroids
        bool clustersChanged = assignClusters(points, &centroids, k);
        if (!clustersChanged) {
            break;          // exit if clusters has not been changed
        }

        //Step 3: update centroids
        updateCentroids(points, &centroids, k);

        lastEpoch = ep;
    }


    if (lastEpoch == epochsLimit){
        cout << "Maximum number of iterations reached!";
    }
    cout << "iterations = " << lastEpoch + 1 << "\n";
}


int main() {
    initialize();
    vector<Point> data = readCsv();
    kMeans(&data, 500, 10);

}
