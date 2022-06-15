# Intro

This implementation of k-means algorithm is made for execution time comparison wrt [GPU accelerated version](https://github.com/sim-pez/k_means_gpu). For this reason the algorithm will not end when reaching convergence, but you need to specify the number of iterations when launching the program.

# Generating dataset

You can generate an _N_ points dataset using ```datasetgen.py```. You have to write also the number of clusters _K_ and the standard deviation. The command will be like:
```
python datasetgen.py N K STD
```
example:
```
python datasetgen.py 1000 3 0.45
```

### Note
The code is made to work on 3 axis but the script will generate points with the third coordinate equal to _0.0_. This is to ease the result checking with ```plot.py```


# Plotting
You can check output results with
```
python plot.py
```

# Other versions
- [GPU accelerated version](https://github.com/sim-pez/k_means_gpu)
- there is also a [distributed system version](https://github.com/sim-pez/k_means_distributed)

# Acknowledgments
Parallel Computing - Computer Engineering Master Degree @[University of Florence](https://www.unifi.it/changelang-eng.html).
