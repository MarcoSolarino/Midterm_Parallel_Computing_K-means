#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Point.h"
#include "csvhandler.h"
#include "operations.h"


using namespace std;

float silhouetteCoefficient(vector<Point> *points, Point point, vector<Point> *centroids) {
    if (centroids->size() <= 1) {
        return -1;
    }
    vector<float> a;
    vector<float> b;

    // calculate nearest other cluster
    auto minDistance = __DBL_MAX__;
    int nearestCluster;
    for (int i = 0; i < centroids->size(); i++) {
        if (i != point.getCluster()) {
            float d = distance3d(point, centroids->at(i));
            if (d < minDistance) {
                nearestCluster = i;
                minDistance = d;
            }
        }
    }

    for (auto &otherPoint : *points) {
        if (otherPoint.getCluster() == point.getCluster())
            a.push_back(distance3d(otherPoint, point));
        if (otherPoint.getCluster() == nearestCluster)
            b.push_back(distance3d(otherPoint, point));
    }

    float meanA = mean(&a);
    float meanB = mean(&b);

    return (meanB - meanA) / max(meanA , meanB);
}

float kMeans(vector<Point> *points, int epochsLimit, int k) {
    // Step 1: Chose k random centroids
    vector<Point> centroids;
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distribution(0, points->size() - 1);
    int lastEpoch = 0;
    for(int i=0; i<k; i++) {
        int randomLocation = distribution(engine);
        //Point c = points->at(111*i);
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
        writeCsv(points, &centroids, 9001, k); //last iteration is also 9001
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

    //calculate silhouette coefficient
    vector<float> s;
    for (auto &point : *points) {
        s.push_back(silhouetteCoefficient(points, point, &centroids));
    }

    cout << "k = " << k << " -> iterations = " << lastEpoch << "\n";
    float m = mean(&s);
    return m;
}


int main() {
    vector<float> silhouetteScore;
    int maxClusters = 10;
    int minClusters = 2;
    initialize();


    //repeats kMeans for different k and finds best silhouette score

    for (int k = minClusters; k <= maxClusters; k++) {
        vector<Point> data = readCsv();
        silhouetteScore.push_back(kMeans(&data, 500, k));
    }

    //find highest silhouette score
    float bestScore = *max_element(silhouetteScore.begin(), silhouetteScore.end());
    int bestK;
    for (int i = 0; i < silhouetteScore.size(); i++){
        cout << "k = " << i+minClusters << " -> score = " << silhouetteScore.at(i) << "\n";
        if (silhouetteScore.at(i) == bestScore) {
            bestK = i + minClusters;
        }
    }
    cout << "Best k: " << bestK;

}
