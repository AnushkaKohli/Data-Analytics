#include <stdio.h>
#include <math.h>

#define N 10
#define K 5
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

int assignToCluster(Point point, Centroid centroids[], int c)
{
    int cluster = 0;
    double minDistance = euclideanDistance(point, centroids[0]);

    for (int i = 1; i < c; i++)
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

void kMeansClustering(Point points[N], Centroid centroids[], int c)
{
    int clusterAssignment[N];

    int maxIterations = 100;

    for (int iter = 0; iter < maxIterations; iter++)
    {

        for (int i = 0; i < N; i++)
        {
            clusterAssignment[i] = assignToCluster(points[i], centroids, c);
        }

        for (int i = 0; i < c; i++)
        {
            centroids[i] = calculateCentroid(points, clusterAssignment, i);
        }
    }

    // Display the final clusters
    for (int i = 0; i < c; i++)
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
    float sum = 0.0;
    for (int i = 0; i < c; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (clusterAssignment[j] == i)
            {
                sum += pow(centroids[i].x - points[j].x, 2) + pow(centroids[i].y - points[j].y, 2);
            }
        }
    }
    printf("%.1fSSE\n", sum);
}

int main()
{
    Point dataPoints[N];
    for (int i = 0; i < N; i++)
    {
        printf("Enter %d point ", i + 1);
        // printf("\nEnter x: ");
        scanf("%lf", &dataPoints[i].x);
        // printf("\nEnter y: ");
        scanf("%lf", &dataPoints[i].y);
    }
    for (int c = 2; c < K; c++)
    {
        Centroid initialCentroids[c];
        printf("Enter %d centroids ", c);
        for (int i = 0; i < c; i++)
        {
            printf("Enter %d point", i + 1);
            // printf("\nEnter x: ");
            scanf("%lf", &initialCentroids[i].x);
            // printf("\nEnter y: ");
            scanf("%lf", &initialCentroids[i].y);
        }
        kMeansClustering(dataPoints, initialCentroids, c);
    }

    return 0;
}