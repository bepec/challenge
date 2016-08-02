#include <iostream>
using namespace std;

#define COUT if(0) cout <<
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORBE(t,i,b,e) for(t* i=b;i<e;i++)
#define MAX(a,b) (a)>(b)?(a):(b)

static const int NMAX = 100001;
typedef long long int T;

T sum1(T* ar, int size) {
    T sum = 0;
    FOR(i, size) {
        cin >> ar[i];
        sum += ar[i];
    }
    return sum;
}

T sum2(T* array, int n) {
    T sum = 0;
    T* end = array + n;
    FORBE(T, it, array, end) {
        cin >> *it;
        sum += *it;
    }

    return sum;
}

int test() {
    int result = 5;
    return result;
}


int main() {
    cout << test();
    return 0;
}
