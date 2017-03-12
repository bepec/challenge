#include <iostream>
using namespace std;

#define out if(1)cout
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#define abs(a)   (((a)<0)?(-(a)):(a))

static const int MAXN = 10000001;

typedef long long int i64;
static i64 ar[MAXN];

int main()
{
	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b, k;
		cin >> a >> b >> k;
		ar[a] += k;
		ar[b+1] -= k;
	}

	i64 cur = 0;
	i64 max = 0;
	for (int i = 1; i <= N; i++) {
		cur += ar[i];
		if (cur > max) max = cur;
	}
	cout << max << endl;
	return 0;
}
