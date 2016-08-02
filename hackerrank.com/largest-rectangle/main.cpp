#include <iostream>
using namespace std;

#ifdef DEBUG
#define COUT cout<<">>> "<<
#else
#define COUT if(0) cout<<
#endif

#define FOR(i,n) for(int i=0;i<n;i++)
#define FORBE(t,i,b,e) for(t* i=b;i<e;i++)

template<class T, int S>
struct Stack {
    T data[S];
    int size;
    Stack(): size(0) {}
    inline void push(const T& value) { data[size++] = value; }
    inline T& peek() { return data[size-1]; }
    inline T pop() { return data[--size]; }
    inline T* end() { return data + size; }
};

const int MAXN = 100001;

struct Fix {
    int position;
    int height;
};

long long test() {
    Stack<Fix, MAXN> fixes;
    fixes.push({ 0, 0 });  // sentinel
    int n;
    cin >> n;
    long long result = 0;
    FOR(pos, n) {
        int height;
        cin >> height;
        Fix& last = fixes.peek();
        if (height == last.height) continue;
        int last_pos = pos;
        // non-optimal: check _-_ case
        while (height < last.height) {
            int width = pos - last.position;
            long long area = last.height * width;
            result = max(area, result);
            COUT "area (" << width << " x " << last.height << "): " << area << "; result: " << result << endl;
            last_pos = last.position;
            fixes.pop();
            last = fixes.peek();
        }
        fixes.push({ last_pos, height });
    }
    COUT "*** finishing stack ***" << endl;
    while (fixes.size > 1) {
        Fix last = fixes.pop();
        long long area = last.height * (n - last.position);
        result = max(area, result);
        COUT "area (" << n - last.position << " x " << last.height << "): " << area << "; result: " << result << endl;
    }
    return result;
}

int main() {
    int T = 1;
#ifdef DEBUG
    cin >> T;
#endif
    while (T--) cout << test() << endl;
    return 0;
}
