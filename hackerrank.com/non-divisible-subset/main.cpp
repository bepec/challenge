#include <stdio.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

#define KMAX 100 

int main()
{
    static int rems[KMAX];
    int N, k, a;

    scanf("%d%d", &N, &k);
    while (N--) {
        scanf("%d", &a);
        rems[a % k]++;
    }

    int result = (rems[0] > 0);
    rems[0] = 0;
    if (k % 2 == 0) {
        result += (rems[k / 2] > 0);
        rems[k / 2] = 0;
    }

    for (int i = 1, j = k - 1; i < j; i++, j--) {
        result += MAX(rems[i], rems[j]);
    }

    printf("%d", result);

    return 0;
}
