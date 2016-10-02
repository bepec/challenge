#include <stdio.h>

#ifdef _DEBUG
#define DBG(...) printf(__VA_ARGS__)
#else
#define DBG(...)
#endif

#define MAX(a,b) ((a)>(b)?(a):(b))

#define KMAX 100 

static int rems[KMAX];
static int* rems_sorted[KMAX];
int N;
int k;

template <class T>
inline void swap(T& a, T& b) {
    T t = a; a = b; b = t;
}

void qsort(int** data, int n)
{
    if (n < 2) return;
    int p = *data[n/2];
    int i = 0, j = n - 1;
    for(;; i++, j--) {
        while (*data[i] < p) i++;
        while (*data[j] > p) j--;
        if (i >= j) break;
        swap(data[i], data[j]);
    }
    qsort(data, i);
    qsort(data + i, n-i);
}

int main()
{
    scanf("%d%d", &N, &k);
    for (int i = 0; i < k; i++) {
        rems_sorted[i] = &rems[i];
    }
    int a;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a);
        DBG("%d ", a%k);
        rems[a % k]++;
    }
    DBG("\n");

    int result = (rems[0] > 0);
    rems[0] = 0;
    if (k % 2 == 0) {
        result += (rems[k / 2] > 0);
        rems[k / 2] = 0;
    }

    for (int i = 0; i < k; i++) DBG("[%lu] %d, ", rems_sorted[i] - rems, *rems_sorted[i]);
    DBG("\n");
    qsort(rems_sorted, k);
    for (int i = 0; i < k; i++) DBG("[%lu] %d, ", rems_sorted[i] - rems, *rems_sorted[i]);
    DBG("\n");

    for (int i = k - 1; i >= 0; i--) {
        int irem = rems_sorted[i] - rems;
        if (rems[irem] == 0) continue;
        result += rems[irem];
        rems[k - irem] = 0;
        DBG("Check remainder %d: met %d times, zero remainder %d; result %d\n",
                irem, *rems_sorted[i], k - irem, result);
    }

    printf("%d", result);

    return 0;
}
