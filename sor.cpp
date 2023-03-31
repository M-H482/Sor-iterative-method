#include "myheader.h"

void printX(int it, int n, float* x)
{
    printf("it = %d\n", it);
    for (int i = 0; i < n; i++)
        printf("%f  ", x[i]);
    printf("\n\n");
}

bool check(int n, float threshold, float* ref, float* ans)
{
    for (int i = 0; i < n; i++) {
        if (isnanf(ans[i]) || fabsf(ref[i] - ans[i]) > threshold)
            return false;
    }
    return true;
}

bool isConvergent(int n, float* x_ref, float* x_ans)
{
    float diff = 0.0f;
    for (int i = 0; i < n; i++) {
        diff = max(diff, fabsf(x_ans[i] - x_ref[i]));
    }
    return diff <= 0.000005;
}

int SOR(float w, int n, float* A, float* b, float* x_ans, float* x_ref)
{
    float s[n] = { 0 };
    for (int i = 0; i < n; i++) {
        float t = 0.0f;
        for (int j = i + 1; j < n; j++) {
            t += A[i * n + j];
        }
        s[i] = t;
    }

    int cnt = 0;
    while (cnt < 10) {
        for (int i = 0; i < n; i++) {
            float xg = (b[i] - s[i]) / A[i * n + i];
            x_ans[i] = (1 - w) * x_ans[i] + w * xg;
            s[i] = 0.0f;

            for (int j = 0; j < n; j++) {
                if (j == i)
                    continue;
                s[j] = s[j] + A[j * n + i] * x_ans[i];
            }
        }
        cnt++;

        printX(cnt, n, x_ans);
        if (isConvergent(n, x_ref, x_ans))
            break;
    }
    return cnt;
}

int main(int argc, char** argv)
{
    float w = 1.03f;
    int n = 3;

    if (argc == 2) {
        w = stof(argv[1]);
    } else if (argc > 2) {
        printf("Usage: exe w!\n");
        return 0;
    }

    float A[n * n] = { 4, -1, 0, -1, 4, -1, 0, -1, 4 };
    float b[n] = { 1, 4, -3 };
    float x_ans[n] = { 0, 0, 0 };
    float x_ref[n] = { 0 };

    solve(n, A, b, x_ref);

    int cnt = SOR(w, n, A, b, x_ans, x_ref);

    printf("cnt = %d\n", cnt);

    return 0;
}
