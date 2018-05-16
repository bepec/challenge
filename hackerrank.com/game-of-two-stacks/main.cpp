#include <iostream>
#include <string>
using namespace std;

#define MAX(a,b) ((a)>(b)?(a):(b))

typedef long i32;
typedef unsigned long ui32;

const int NMAX = 1e5;

template<class T, int N>
struct TStack {
	T data[N];
	int size;
	TStack() : size(0) {}
	void push(const T& v) { data[size++] = v; }
	T& push() { return data[size++]; }
	T& peek() { return data[size-1]; }
	T pop() { return data[--size]; }
};

typedef TStack<int, NMAX> Stack;

int test() {
	int result = 0;
	Stack a;
	int n, m, x;
	cin >> n >> m >> x;
	int asum = 0;
	int bsum = 0;
	int read;
	while (n--) {
		cin >> read;
		if (asum <= x) {
			asum += read;
			a.push(asum);
			if (asum > x) {
				a.pop();
			}
		}
	}
	result = a.size;
	for (int bi = 1; bi <= m; bi++) {
		cin >> read;
		if (bsum > x) continue;
		bsum += read;
		if (bsum <= x) {
			while (a.size && a.peek() + bsum > x) {
				a.pop();
			}
			result = MAX(result, a.size + bi);
		}
	}
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int T;
	cin >> T;
	while (T--) cout << test() << endl;
	return 0;
}