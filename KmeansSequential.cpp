#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include "Point.h"
#include "csvhandler.h"

using namespace std;

double distance3d(double x1, double x2, double x3, double y1, double y2, double y3) {
    // compute euclidean distance
    double distance = sqrt(pow(x1 - y1, 2) + pow(x2 - y2, 2) + pow(x3 - y3, 2));
    return distance;
}

void kMeans(vector<Point>* points, int epochslimit, int k) {
    // Step 1: Chose k random centroids
    vector<Point> centroids;
    random_device rd;
    default_random_engine engine(rd());
    uniform_int_distribution<int> distribution(0, points->size() - 1);
    for(int i=0; i<3; i++) {
        //Point c = points->at(i*111);
        Point c = points->at(distribution(engine));
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
                return;
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

        writeCsv(points, &centroids, ep);
    }

}

int main() {
    vector<Point> data = readCsv(); //FiXME -data[150]: appears during debug before readCsv() is called.
    kMeans(&data, 500, 3);
    cout << "Test" ;
}
