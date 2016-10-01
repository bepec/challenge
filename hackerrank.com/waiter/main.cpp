#include <iostream>
using namespace std;

#define COUT if(1)cout<<
#define FOR(i,n) for(int i=0;i<n;i++)

template<class T, int S>
struct Stack {
    T data[S];
    int size;
    Stack(): size(0) {}
    inline void push(T v) { data[size++] = v; }
    inline T pop() { return data[--size]; }
    inline T& peek() { return data[size-1]; }
};

const int NMAX = 50000;
const int nMAX = 10000;
const int PMAX = 2000;

bool is_prime(int n) {
    for (int i = 2; i*i < n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    Stack<int, PMAX> primes;
    primes.push(2);
    for (int i = 3; i < nMAX; i++) {
        if (is_prime(i)) primes.push(i);
    }
    COUT "primes <= " << nMAX << ": " << primes.size << "; last: " << primes.peek() << endl;

    int n, q;
    cin >> n >> q;

    Stack<int, NMAX> div;
    Stack<int, NMAX> nondiv;
    Stack<int, NMAX> temp;
    FOR(i, n) {
        temp.size++;
        cin >> temp.peek();
    }

    for (int iq = 0; iq < q; iq++) {
        int prime = primes.data[iq];
        COUT ">>> prime " << prime;
        while (nondiv.size) {
            temp.size++;
            temp.peek() = nondiv.pop();
        }
        while (temp.size) {
            int num = temp.pop();
            if (num % prime == 0) div.push(num);
            else nondiv.push(num);
        }
        while (div.size) cout << div.pop() << endl;
        COUT "; div.size: " << div.size << "; nondiv.size: " << nondiv.size << endl;
    }

    while (nondiv.size) cout << nondiv.pop() << endl;
    return 0;
}
