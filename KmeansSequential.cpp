#include <vector>
#include <random>
#include <algorithm>
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

void kMeans(vector<Point> *points, int iterations, int k) {
    //Create k random centroids
    vector<Point> centroids;
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distribution(0, points->size() - 1);
    for(int i=0; i<k; i++) {
        int randomLocation = distribution(engine);
        Point c = points->at(randomLocation);
        centroids.push_back(c);
    }


    for(int i = 0 ; i < iterations; i++) {
        // if (i != 0) writeCsv(points, &centroids, i, k);

        assignClusters(points, &centroids, k);
        updateCentroids(points, &centroids, k);

    }

    writeCsv(points, &centroids);
}


int main() {
    initialize();
    int iterations = 50; //TODO pass by argument
    int clusters = 5; // TODO pass by argument

    vector<Point> points = readCsv();

    auto start = high_resolution_clock::now();
    kMeans(&points, iterations, clusters);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start);
    return 0;

}
