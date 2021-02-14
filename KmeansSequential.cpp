#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <random>
#include "Point.h"

using namespace std;

vector<Point> readCsv() {
    vector<Point> points;
    string line;
    ifstream file("D:/JetBrains/Projects/Clion/Kmeans/dataset.csv", ifstream::in);

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y, z;
        getline(lineStream, bit, ',');
        x = stod(bit);
        getline(lineStream, bit, ',');
        y = stod(bit);
        getline(lineStream, bit, '\n');
        z = stod(bit);

        Point pt = Point(x, y, z);

        points.push_back(pt);

    }

    return points;
}

double randDouble(double inf, double max) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 mt(seed);
    uniform_real_distribution<double> distribution(inf, max);

    double result = distribution(mt);
    return result;
}

void kMeans(vector<Point>* points, int epochs, int k) {

}

int main() {
    vector<Point> data = readCsv();
    kMeans(&data, 5, 3);
    cout << "Test" ;
}
