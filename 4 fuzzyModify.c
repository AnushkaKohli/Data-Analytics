#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10 // Number of data points
#define K 2  // Number of clusters

// Structure to represent a 2D point
struct Point
{
    double x;
    double y;
};

// Function to calculate Euclidean distance between two points
double distance(struct Point a, struct Point b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

// Function to assign each data point to the nearest centroid
void assign_clusters(struct Point data[], struct Point centroids[], int cluster_assignment[])
{
    for (int i = 0; i < N; i++)
    {
        double min_distance = distance(data[i], centroids[0]);
        cluster_assignment[i] = 0;
        for (int j = 1; j < K; j++)
        {
            double dist = distance(data[i], centroids[j]);
            if (dist < min_distance)
            {
                min_distance = dist;
                cluster_assignment[i] = j;
            }
        }
    }
}

// Function to update centroids based on mean of data points in each cluster
void update_centroids(struct Point data[], struct Point centroids[], int cluster_assignment[])
{
    int counts[K] = {0};
    double sum_x[K] = {0}, sum_y[K] = {0};

    for (int i = 0; i < N; i++)
    {
        int cluster = cluster_assignment[i];
        counts[cluster]++;
        sum_x[cluster] += data[i].x;
        sum_y[cluster] += data[i].y;
    }

    for (int i = 0; i < K; i++)
    {
        centroids[i].x = sum_x[i] / counts[i];
        centroids[i].y = sum_y[i] / counts[i];
    }
}

int main()
{
    // Sample data points
    struct Point data[N] = {{1, 1}, {1.5, 2}, {3, 4}, {5, 7}, {3.5, 5}, {4.5, 5}, {3.5, 4.5}, {5.5, 7}, {6, 8}, {4, 5}};

    // Initial centroids
    struct Point centroids[K] = {{1, 1}, {5, 7}};

    // Array to store cluster assignment for each data point
    int cluster_assignment[N];

    // Iterative K-Means algorithm
    for (int iter = 0; iter < 10; iter++)
    { // Maximum 10 iterations
        assign_clusters(data, centroids, cluster_assignment);
        update_centroids(data, centroids, cluster_assignment);
    }

    // Print final cluster assignments
    printf("Final cluster assignments:\n");
    for (int i = 0; i < N; i++)
    {
        printf("Point %d: Cluster %d\n", i + 1, cluster_assignment[i] + 1);
    }

    return 0;
}