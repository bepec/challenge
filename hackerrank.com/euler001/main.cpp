#include <iostream>
using namespace std;

typedef unsigned long long llu;

inline llu test() {
    int n;
    cin >> n;
    llu res = 0;
    for (int i = 3; i < n; ++i) {
        if (i % 3 == 0 || i % 5 == 0) res += i;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) cout << test() << "\n";
}
