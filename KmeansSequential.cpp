#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Point.h"
#include "csvhandler.h"
#include "operations.h"


using namespace std;

double silhouetteCoefficient(vector<Point> *points, Point point, vector<Point> *centroids) {
    if (centroids->size() <= 1) {
        return -1;
    }
    vector<double> a;
    vector<double> b;

    // calculate nearest other cluster
    auto minDistance = __DBL_MAX__;
    int nearestCluster;
    for (int i = 0; i < centroids->size(); i++) {
        if (i != point.getCluster()) {
            double d = distance3d(point, centroids->at(i));
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

    double meanA = mean(&a);
    double meanB = mean(&b);

    return (meanB - meanA) / max(meanA , meanB);
}

double kMeans(vector<Point> *points, int epochsLimit, int k) {
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
        bool clusterChanged = false;

        //Step 2: assign dataPoints to the clusters, based on the distance from its centroids

        vector<int> numPoints; // keep trace of the number of points in each cluster
        vector<double> sumX;   // will be used to update centroids through the mean point of the clusters
        vector<double> sumY;
        vector<double> sumZ;

        //initialize with zeros
        for (int i = 0; i < k; i++) {
            numPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
            sumZ.push_back(0.0);
        }

        for (auto &point : *points) {
            double x1 = point.getX();
            double x2 = point.getY();
            double x3 = point.getZ();
            point.setMinDistance(__DBL_MAX__);
            double distMin = point.getMinDistance();  // the distance between its actual cluster' centroid

            int clusterIndex = point.getCluster(); // keep trace of witch cluster the point is
            point.setOldCluster(point.getCluster());

            for (int j = 0; j < k; j++) {
                double y1 = centroids.at(j).getX();
                double y2 = centroids.at(j).getY();
                double y3 = centroids.at(j).getZ();
                double distance = distance3d(x1, x2, x3, y1, y2, y3);

                if (distance < distMin) {
                    point.setMinDistance(distance);
                    distMin = distance;
                    point.setCluster(j);
                    clusterIndex = j;
                }
            }

            numPoints.at(clusterIndex) += 1;
            sumX.at(clusterIndex) += point.getX();
            sumY.at(clusterIndex) += point.getY();
            sumZ.at(clusterIndex) += point.getZ();
            if (point.getCluster() != point.getOldCluster()) {
                clusterChanged = true;
            }
        }

        // exit if clusters has not been changed
        if (!clusterChanged) {
            break;
        }

        writeCsv(points, &centroids, ep, k);
        writeCsv(points, &centroids, 9001, k); //last iteration is also 9001
        lastEpoch++;

        //Step 3: updates centroids

        for (int i = 0; i < k; i++) {
            double newX = sumX.at(i) / numPoints.at(i);
            double newY = sumY.at(i) / numPoints.at(i);
            double newZ = sumZ.at(i) / numPoints.at(i);
            centroids.at(i).setX(newX);
            centroids.at(i).setY(newY);
            centroids.at(i).setZ(newZ);

        }

    }

    //calculate silhouette coefficient
    vector<double> s;
    for (auto &point : *points) {
        s.push_back(silhouetteCoefficient(points, point, &centroids));
    }

    cout << "k = " << k << " -> iterations = " << lastEpoch << "\n";
    double m = mean(&s);
    return m;
}


int main() {
    vector<double> silhouetteScore;
    int maxClusters = 10;
    int minClusters = 2;
    initialize();


    //repeats kMeans for different k and finds best silhouette score

    for (int k = minClusters; k <= maxClusters; k++) {
        vector<Point> data = readCsv();
        silhouetteScore.push_back(kMeans(&data, 500, k));
    }

    //find highest silhouette score
    double bestScore = *max_element(silhouetteScore.begin(), silhouetteScore.end());
    int bestK;
    for (int i = 0; i < silhouetteScore.size(); i++){
        cout << "k = " << i+minClusters << " -> score = " << silhouetteScore.at(i) << "\n";
        if (silhouetteScore.at(i) == bestScore) {
            bestK = i + minClusters;
        }
    }
    cout << "Best k: " << bestK;

}
