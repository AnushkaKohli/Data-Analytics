#include <stdio.h>
#include <math.h>

#define N 7
#define K 2

typedef struct
{
    double x;
    double y;
} Point;

typedef struct
{
    double x;
    double y;
} Centroid;

double euclideanDistance(Point p1, Centroid p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int assignToCluster(Point point, Centroid centroids[K])
{
    int cluster = 0;
    double minDistance = euclideanDistance(point, centroids[0]);

    for (int i = 1; i < K; i++)
    {
        double distance = euclideanDistance(point, centroids[i]);
        if (distance < minDistance)
        {
            minDistance = distance;
            cluster = i;
        }
    }

    return cluster;
}

Centroid calculateCentroid(Point points[N], int clusterAssignment[N], int cluster)
{
    Centroid newCentroid = {0.0, 0.0};
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        if (clusterAssignment[i] == cluster)
        {
            newCentroid.x += points[i].x;
            newCentroid.y += points[i].y;
            count++;
        }
    }

    if (count > 0)
    {
        newCentroid.x /= count;
        newCentroid.y /= count;
    }

    return newCentroid;
}

void kMeansClustering(Point points[N], Centroid centroids[K])
{
    int clusterAssignment[N];

    // Maximum number of iterations
    int maxIterations = 100;

    for (int iter = 0; iter < maxIterations; iter++)
    {
        // Assign each point to the nearest centroid
        for (int i = 0; i < N; i++)
        {
            clusterAssignment[i] = assignToCluster(points[i], centroids);
        }

        // Update centroids
        for (int i = 0; i < K; i++)
        {
            centroids[i] = calculateCentroid(points, clusterAssignment, i);
        }
    }

    // Display the final clusters
    for (int i = 0; i < K; i++)
    {
        printf("Cluster %d (Centroid %.1f, %.1f): ", i + 1, centroids[i].x, centroids[i].y);
        for (int j = 0; j < N; j++)
        {
            if (clusterAssignment[j] == i)
            {
                printf("(%.1f, %.1f) ", points[j].x, points[j].y);
            }
        }
        printf("\n");
    }
}

int main()
{
    Point dataPoints[N] = {{1.0, 1.0}, {1.5, 2.0}, {3.0, 4.0}, {5.0, 7.0}, {3.5, 5.0}, {4.5, 5.0}, {3.5, 4.5}};
    Centroid initialCentroids[K] = {{1.0, 1.0}, {3.5, 4.5}};

    kMeansClustering(dataPoints, initialCentroids);

    return 0;
}