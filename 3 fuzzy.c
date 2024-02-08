#include <stdio.h>
#include <math.h>

#define N 5           // Number of data samples
#define M 2           // Number of clusters
#define MAX_ITER 5    // Maximum number of iterations
#define EPSILON 0.001 // Threshold for convergence

void initialize_membership(float membership[N][M])
{
    // Initialize membership matrix with fixed values
    float init_values[N][M] = {
        {0.6, 0.4},
        {0.7, 0.3},
        {0.8, 0.2},
        {0.5, 0.5},
        {0.4, 0.6}};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            membership[i][j] = init_values[i][j];
        }
    }
}

void calculate_cluster_centers(float data[N][2], float membership[N][M], float centroids[M][2])
{
    float numerator[M][2] = {0};
    float denominator[M] = {0};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            float uij_m = pow(membership[i][j], 1.26); // fuzzy membership
            numerator[j][0] += uij_m * data[i][0];
            numerator[j][1] += uij_m * data[i][1];
            denominator[j] += uij_m;
        }
    }

    for (int j = 0; j < M; j++)
    {
        centroids[j][0] = numerator[j][0] / denominator[j];
        centroids[j][1] = numerator[j][1] / denominator[j];
    }
}

float update_membership(float data[N][2], float membership[N][M], float centroids[M][2])
{
    float new_membership[N][M];
    float diff = 0.0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            float dist_ij = sqrt(pow(data[i][0] - centroids[j][0], 2) + pow(data[i][1] - centroids[j][1], 2));
            float sum = 0;
            for (int k = 0; k < M; k++)
            {
                float dist_ik = sqrt(pow(data[i][0] - centroids[k][0], 2) + pow(data[i][1] - centroids[k][1], 2));
                sum += pow(dist_ij / dist_ik, 2.0 / 0.26); // fuzziness factor
            }
            new_membership[i][j] = 1.0 / sum;
            diff += fabs(new_membership[i][j] - membership[i][j]);
            membership[i][j] = new_membership[i][j];
        }
    }

    return diff;
}

void print_clusters(float membership[N][M])
{
    for (int i = 0; i < N; i++)
    {
        printf("Sample %d: ", i + 1);
        for (int j = 0; j < M; j++)
        {
            printf("Cluster %d: %.2f\t", j + 1, membership[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    float data[N][2] = {
        {1.0, 1.0},
        {1.5, 2.0},
        {3.0, 4.0},
        {5.0, 7.0},
        {3.5, 5.0}};
    float membership[N][M];
    float centroids[M][2];

    initialize_membership(membership);

    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        calculate_cluster_centers(data, membership, centroids);
        float diff = update_membership(data, membership, centroids);
        printf("Iteration %d, Membership Difference: %.4f\n", iter + 1, diff);
        print_clusters(membership);
        if (diff < EPSILON)
        {
            printf("Converged.\n");
            break;
        }
    }

    return 0;
}