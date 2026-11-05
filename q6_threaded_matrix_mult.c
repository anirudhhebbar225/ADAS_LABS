#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3

int A[N][N], B[N][N], C[N][N];

void *multiply(void *arg)
{
    int row = *(int *)arg;

    for (int j = 0; j < N; j++)
    {
        C[row][j] = 0;

        for (int k = 0; k < N; k++)
        {
            C[row][j] += A[row][k] * B[k][j];
        }
    }

    return NULL;
}

int main()
{
    pthread_t t[N];
    int row[N];

    printf("Enter matrix A:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &B[i][j]);

    // Create threads
    for (int i = 0; i < N; i++)
    {
        row[i] = i;
        pthread_create(&t[i], NULL, multiply, &row[i]);
    }

    // Wait for threads
    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    // Print result
    printf("Matrix C = A * B:\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", C[i][j]);

        printf("\n");
    }

    return 0;
}