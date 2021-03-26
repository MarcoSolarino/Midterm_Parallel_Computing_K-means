import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas
import sys

def plot_k_means_iteration(iteration, k):

    df_dataset = pandas.read_csv('output/k' + str(k) + 'iteration' + str(iteration) + '.csv', header=None)
    df_centroids = pandas.read_csv('output/k' + str(k) + 'centroids' + str(iteration) + '.csv', header=None)

    cluster = []

    for i in range(k):
        cluster.append(df_dataset.loc[df_dataset[3] == i])

    for i in range(k):
        plt.scatter(cluster[i].iloc[:, 0], cluster[i].iloc[:, 1])

    plt.scatter(df_centroids.iloc[:, 0], df_centroids.iloc[:, 1], marker='*', c='black')
    plt.grid()
    plt.gca().set_aspect('equal', adjustable='box')
    plt.show()

k = int(sys.argv[1])
iterations = int(sys.argv[2])

for i in range(1, iterations + 1):
    plot_k_means_iteration(i, k)

