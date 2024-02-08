#include <stdio.h>
#include <math.h>

#define MIN_POINTS 4

typedef struct
{
    double x, y;
    int cluster_id;
    int visited;
} Point;

typedef struct
{
    Point points[13];
    int size;
} PointList;

double euclidean_distance(Point a, Point b)
{
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

void expand_cluster(PointList *points, int index, int cluster_id, double eps, int min_points)
{
    int i;
    int count = 0;
    printf("Neighbors of point%d (%.1f, %.1f): ", index + 1, points->points[index].x, points->points[index].y);
    for (i = 0; i < points->size; ++i)
    {
        if (i != index && euclidean_distance(points->points[index], points->points[i]) <= eps)
        {
            printf("(%0.1f, %0.1f) ", points->points[i].x, points->points[i].y);
            count++;
        }
    }
    if (count >= 4)
        printf("Core Point\n");
    if (count < 3)
        points->points[i].cluster_id = 5;
    printf("\n");
    for (i = 0; i < points->size; ++i)
    {
        if (i != index && euclidean_distance(points->points[index], points->points[i]) <= eps)
        {
            if (points->points[i].cluster_id == -1 || !points->points[i].visited)
            {
                points->points[i].cluster_id = cluster_id;
                if (!points->points[i].visited)
                {
                    points->points[i].visited = 1;
                    expand_cluster(points, i, cluster_id, eps, min_points);
                }
            }
        }
    }
}

void dbscan(PointList *points, double eps, int min_points)
{
    int cluster_id = 0;
    int i;
    for (i = 0; i < points->size; ++i)
    {
        if (!points->points[i].visited)
        {
            points->points[i].visited = 1;
            if (points->points[i].cluster_id == -1)
            {
                points->points[i].cluster_id = cluster_id;
                expand_cluster(points, i, cluster_id, eps, min_points);
                cluster_id++;
            }
        }
    }
}

int main()
{
    PointList points = {
        {{1.0, 2.0, -1, 0},
         {3.0, 4.0, -1, 0},
         {2.5, 4.0, -1, 0},
         {1.5, 2.5, -1, 0},
         {3.0, 5.0, -1, 0},
         {2.8, 4.5, -1, 0},
         {2.5, 4.5, -1, 0},
         {1.2, 2.5, -1, 0},
         {1.0, 3.0, -1, 0},
         {1.0, 5.0, -1, 0},
         {1.0, 2.5, -1, 0},
         {5.0, 6.0, -1, 0},
         {4.0, 3.0, -1, 0}},
        13};

    double eps = 0.6;
    int min_points = MIN_POINTS;

    dbscan(&points, eps, min_points);

    int i;
    for (i = 0; i < points.size; ++i)
    {

        if (points.points[i].cluster_id + 1 > 2)
        {
            printf("Point %d is noise point\n", i + 1);
        }
        else
        {
            printf("Point %d: Cluster ID = %d\n", i + 1, points.points[i].cluster_id + 1);
        }
    }

    return 0;
}