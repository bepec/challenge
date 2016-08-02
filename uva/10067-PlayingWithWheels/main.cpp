#include <iostream>
using namespace std;

typedef int T;
#define COUT if (0) cout
#define FOR(T, N, M) for (T N=0; N < M; N++)
#define FORI(M) FOR(int, i, M)
//const int maxSize = 10000;

template<int maxSize>
struct Queue {
    T data[maxSize];
    int size;
    int first;
    Queue(): size(0), first(0) {}
    inline void push(T v) {
        //if (size == maxSize) {
            //if (first == 0) throw 999;
            //FORI(size) data[i] = data[first++];
            //first = 0;
        //}
        data[first+size++] = v;
    }
    inline T pop() {
        //if (size == 0) throw 999;
        size--;
        return data[first++];
    }
    inline T* find(T v) {
        FORI(size) if (data[i] == v) return &data[i];
        return NULL;
    }
    inline void print() {
        return;
        COUT << size << ":[ ";
        FORI(size) COUT << data[i] << " ";
        COUT << "]";
    }
};

const int maxNodes = 10000;

void nexts(int v, int c[8]) {
    c[0] = (v % 10 < 9) ? v+1 : v-9;
    c[1] = (v % 100 < 90) ? v+10 : v-90;
    c[2] = (v % 1000 < 900) ? v+100 : v-900;
    c[3] = (v % 10000 < 9000) ? v+1000 : v-9000;
    c[4] = (v % 10 < 1) ? v+9 : v-1;
    c[5] = (v % 100 < 10) ? v+90 : v-10;
    c[6] = (v % 1000 < 100) ? v+900 : v-100;
    c[7] = (v % 10000 < 1000) ? v+9000 : v-1000;
}

struct Graph {
    Queue<8> adj[maxNodes];
    int size;
    int dists[maxNodes];
    Queue<maxNodes> forbs;
    Graph(): size(maxNodes) {
        int mods[8];
        FORI(maxNodes) {
            nexts(i, mods);
            FOR(int, j, 8) edge(i, mods[j]);
        }
    }
    void reset() {
        forbs.size = 0; forbs.first = 0;
        FORI(maxNodes) dists[i] = -1;
    }
    void edge(int a, int b) {
        adj[a].push(b);
    }
    int bfs(int start, int stop) {
        if (start == stop) return 0;
        Queue<maxNodes> q;
        q.push(start);
        dists[start] = 0;
        for (int dist = 0; q.size > 0; dist++) {
            int node = q.pop();
            COUT << "(" << dists[node] << ") " << node << ": ";
            adj[node].print();
            COUT << "; vis:";
            FORI(adj[node].size) {
                int next = adj[node].data[i];
                if (next == stop) return dists[node]+1;
                if (forbs.find(next) != NULL) continue;
                if (dists[next] != -1) { COUT << " " << next; continue; }
                dists[next] = dists[node]+1;
                q.push(next);
            }
            COUT << endl;
        }
        return -1;
    }
};

int readnum() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    return 1000*a + 100*b + 10*c + d;
}

Graph g;

void solve() {
    int src = readnum();
    int dst = readnum();
    int nforb;
    g.reset();
    cin >> nforb;
    FORI(nforb) g.forbs.push(readnum());
    COUT << "src=" << src << "; dst=" << dst << "; forbs="; g.forbs.print(); COUT << endl;
    cout << g.bfs(src, dst) << endl;
}

int main() {
    int count;
    cin >> count;
    FORI(count) solve();
}
