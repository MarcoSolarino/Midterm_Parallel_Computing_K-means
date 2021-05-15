This repository contains the midterm project for parallel computing course.

This implementation of k-means algorithm is intended for execution time comparison wrt [CUDA version](https://github.com/daikon899/Midterm_K-means_CUDA), so you need to specify manually how many iterations you want to execute.

## 1 - Generating dataset
first you need to generate dataset
```
python datasetgen.py N K STD
```
where N is the number of points you want to generate, K is the number of clusters and STD is standard deviation of points from clusters. 
Here is an example:
```
python datasetgen.py 1000 3 0.45
```
this will genearate a dataset of 1000 points inside input folder

## 2 - Run
```
./Kmeans N K I
```
Where N is the number of points to read from dataset, K is the number of clusters and I the number of iterations.

Example:
```
./Kmeans 1000 5 50
```
Will look for 5 clusters through first 1000 points of dataset and it will iterate 50 times. 

## 3 - Check output
After running program you can check output results with
```
python plot.py
```

### Note
The code is made to work with 3D points but datasetgen.py will generate points with z = 0.0. This is intended to ease result checking with plot.py

## Other versions
- [CUDA](https://github.com/daikon899/Midterm_K-means_CUDA)
- there is also an [Hadoop version](https://github.com/daikon899/Midterm_K-means_hadoop) (no execution time comparison)
