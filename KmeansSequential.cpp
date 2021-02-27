#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Point.h"
#include "csvhandler.h"
#include "operations.h"


using namespace std;

void kMeans(vector<Point> *points, int epochsLimit, int k) {
    // Step 1: Chose k random centroids
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

    // repeat step 2 and 3 for a number of times less than epochsLimit or until nothing happens

    for(int ep=0; ep < epochsLimit; ep++) {
        bool clustersChanged = false;

        //Step 2: assign dataPoints to the clusters, based on the distance from its centroids

        vector<int> numPoints(k, 0); // keep trace of the number of points in each cluster
        vector<float> sumX(k, 0.0);
        vector<float> sumY(k, 0.0);
        vector<float> sumZ(k, 0.0);

        // assign points to the clusters
        for (auto &point : *points) {
            point.setClusterDistance(__DBL_MAX__);
            point.setOldCluster(point.getCluster());

            float clusterDistance = point.getClusterDistance();  // the distance between its actual cluster' centroid
            int clusterIndex = point.getCluster(); // keep trace of witch cluster the point is

            for (int j = 0; j < k; j++) {
                float distance = distance3d(centroids.at(j), point);
                if (distance < clusterDistance) {
                    point.setClusterDistance(distance);
                    clusterDistance = distance;
                    point.setCluster(j);
                    clusterIndex = j;
                }
            }

            numPoints.at(clusterIndex) += 1;
            sumX.at(clusterIndex) += point.getX();
            sumY.at(clusterIndex) += point.getY();
            sumZ.at(clusterIndex) += point.getZ();

            if (point.getCluster() != point.getOldCluster()) {
                clustersChanged = true;
            }
        }

        // exit if clusters has not been changed
        if (!clustersChanged) {
            break;
        }

        writeCsv(points, &centroids, ep, k);
        writeCsv(points, &centroids, __INT_MAX__, k); //last iteration is also 9001
        lastEpoch++;

        //Step 3: updates centroids

        for (int i = 0; i < k; i++) {
            float newX = sumX.at(i) / numPoints.at(i);
            float newY = sumY.at(i) / numPoints.at(i);
            float newZ = sumZ.at(i) / numPoints.at(i);
            centroids.at(i).setX(newX);
            centroids.at(i).setY(newY);
            centroids.at(i).setZ(newZ);
        }
    }
    cout << "iterations = " << lastEpoch << "\n";
}


int main() {
    initialize();
    vector<Point> data = readCsv();
    kMeans(&data, 500, 10);

}
