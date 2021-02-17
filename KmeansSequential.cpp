#include <iostream>
#include <vector>
#include <random>
#include "Point.h"
#include "csvhandler.h"
#include "operations.h"

using namespace std;

double silouetteCoefficient(vector<Point>* points, Point point, vector<Point>* centroids) {
    if (centroids->size() <= 1){
        return 1;
    }
    vector<double> a;
    vector<double> b;

    // calculate nearest other cluster
    double minDistance = 9001;
    int nearestCluster;
    for (int i = 0; i < centroids->size(); i++){
        if (i != point.getCluster()){
            double d = distance3d(point, centroids->at(i));
            if (d < minDistance){
                nearestCluster = i;
                minDistance = d;
            }
        }
    }


    for (auto &otherpoint : *points) {
        if (otherpoint.getCluster() == point.getCluster())
            a.push_back(distance3d(otherpoint, point));
        if (otherpoint.getCluster() == nearestCluster)
            b.push_back(distance3d(otherpoint, point));
    }

    double maxA = *max_element(a.begin(), a.end());
    double maxB = *max_element(b.begin(), b.end());

    return (mean(a) + mean(b) ) / max(maxA ,maxB);
}

double kMeans(vector<Point>* points, int epochslimit, int k) {
    // Step 1: Chose k random centroids
    vector<Point> centroids;
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distribution(0, points->size() - 1);
    for(int i=0; i<k; i++) {
        //Point c = points->at(i*111);
        int randomLocation = distribution(engine);
        Point c = points->at(randomLocation);
        centroids.push_back(c);
    }

    // repeat step 2 and 3 for a number of times less than epochslimit or until nothing happens

    for(int ep=0; ep < epochslimit; ep++) {
        bool clusterChanged = false;

        //Step 2: assign datapoints to the clusters, based on the distance from its centroids

        vector<int> numPoints; // keep trace of the number of points in each cluster
        vector<double> sumX;   // will be used to update centroids through the mean point of the clusters
        vector<double> sumY;
        vector<double> sumZ;

        //initialize with zeros
        for (int i=0; i<k; i++) {
            numPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
            sumZ.push_back(0.0);
        }

        for(auto & point : *points){
            double x1 = point.getX();
            double x2 = point.getY();
            double x3 = point.getZ();
            double distMin = point.getMaxDistance();

            int clusterIndex = point.getCluster(); // keep trace of witch cluster the point is
            point.setOldCluster(point.getCluster());

            for(int j=0; j<k; j++){
                double y1 = centroids.at(j).getX();
                double y2 = centroids.at(j).getY();
                double y3 = centroids.at(j).getZ();
                double distance = distance3d(x1, x2, x3, y1, y2, y3);

                if (distance < distMin) {
                    point.setMaxDistance(distance);
                    distMin = distance;
                    point.setCluster(j);
                    clusterIndex = j;
                }
            }

            numPoints.at(clusterIndex) += 1;
            sumX.at(clusterIndex) += point.getX();
            sumY.at(clusterIndex) += point.getY();
            sumZ.at(clusterIndex) += point.getZ();
            if (point.getCluster() != point.getOldCluster()){
                clusterChanged = true;
            }
        }

        // exit if clusters has not been changed
        if (!clusterChanged){
            break;
        }

        //Step 3: updates centroids

        for(int i=0; i<k; i++) {
            double newX = sumX.at(i)/numPoints.at(i);
            double newY = sumY.at(i)/numPoints.at(i);
            double newZ = sumZ.at(i)/numPoints.at(i);
            centroids.at(i).setX(newX);
            centroids.at(i).setY(newY);
            centroids.at(i).setZ(newZ);
        }
        writeCsv(points, &centroids, ep, k);

    }

    //calculate silhouette coefficient
    vector<double> s;
    for(auto & point : *points) {
        s.push_back(silouetteCoefficient(points, point, &centroids));
    }


    return mean(s);

}


int main() {
    initialize();
    vector<int> silouetteScore;
    int maxClusters = 10;
    int minClusters = 2;


    //repeats kmeans for different k and finds best silouette score
    for (int k = minClusters; k <= maxClusters; k++){
        vector<Point> data = readCsv();
        silouetteScore.push_back(kMeans(&data, 500, k));
    }

    //find highest silouette score
    int max = silouetteScore.at(0);
    int bestK = minClusters;
    for (int i = 0; i <= maxClusters - minClusters; i++){
        if (max < silouetteScore.at(i)) {
            max = silouetteScore.at(i);
            bestK = i + minClusters;
        }
    }
    cout << "Best k: " << bestK ;

}
