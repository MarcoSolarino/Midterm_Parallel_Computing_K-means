This repository contains the midterm project for parallel computing course

## 1 - Generating dataset
first you need to generate dataset
```
python datasetgen.py N K STD
```
where N is the number of points you want to generate, K is the number of clusters and STD is standard deviation of points from clusters, for example:
```
python datasetgen.py 1000 3 0.45
```
## 2 - Run
```
./Kmeans K I
```
Where K is the number of clusters and I the number of iterations.

Example:
```
./Kmeans 5 50
```
Will look for 5 clusters and it will iterate 50 times the algorithm 

## 3 - Plotting
```
python plot.py
```
After running program you can plot result

## Other k-means versions
- [CUDA](https://github.com/daikon899/Midterm_K-means_CUDA)
- [Hadoop](https://github.com/daikon899/Midterm_K-means_hadoop)
