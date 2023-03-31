#include "myheader.h"

int find_max(int n, float* A, int j)
{
    int r = j;
    float v = fabsf(A[j * n + j]);
    for (int i = j; i < n; i++) {
        float u = fabsf(A[i * n + j]);
        if (u > v) {
            v = u;
            r = i;
        }
    }
    return r;
}

void myswap(int n, float* A, float* b, int i, int j, float* tmp)
{
    memcpy(tmp, A + i * n, sizeof(float) * n);
    memcpy(A + i * n, A + j * n, sizeof(float) * n);
    memcpy(A + j * n, tmp, sizeof(float) * n);

    swap(b[i], b[j]);
}

void guass_elimination(int n, float* A, float* b)
{
    float* tmp = new float[n];
    for (int j = 0; j < n - 1; j++) {
        int l = find_max(n, A, j);
        if (l != j)
            myswap(n, A, b, l, j, tmp);
        if (A[j * n + j] > -1e-6 && A[j * n + j] < 1e-6) {
            printf("A is singular! exit now!\n");
            return;
        }

        float Ajj = A[j * n + j];

        for (int i = j + 1; i < n; i++) {
            A[i * n + j] /= Ajj;
        }

        for (int k = j + 1; k < n; k++) {
            float Ajk = A[j * n + k];

            for (int i = j + 1; i < n; i++) {
                A[i * n + k] -= A[i * n + j] * Ajk;
            }
        }
    }
    delete[] tmp;
}

void getY(int n, float* A, float* b, float* y)
{ // LY=b
    for (int j = 0; j < n; j++) {
        float yj = y[j] = b[j];

        for (int i = j + 1; i < n; i++) {
            b[i] = b[i] - A[i * n + j] * yj;
        }
    }
}

void getX(int n, float* A, float* y, float* x)
{ // Ux=y
    for (int j = n - 1; j >= 0; j--) {
        x[j] = y[j] / A[j * n + j];
        float xj = x[j];

        for (int i = 0; i < j; i++) {
            y[i] = y[i] - A[i * n + j] * xj;
        }
    }
}

void solve(int n, float* A, float* b, float* x)
{
    float* y = new float[n];
    float* tA = new float[n * n];
    float* tb = new float[n];

    memcpy(tA, A, sizeof(float) * n * n);
    memcpy(tb, b, sizeof(float) * n);

    guass_elimination(n, tA, tb);

    getY(n, tA, tb, y);

    getX(n, tA, y, x);

    delete[] y;
    delete[] tA;
    delete[] tb;
}