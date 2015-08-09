#include <iostream>
using namespace std;

#define COUT if (0) cout

const int maxNodes = 201;

struct Array {
    int data[maxNodes];
    int size;
    Array(): size(0) {};
    void push(const int& value) {
        data[size++] = value;
    }
};

void printArray(int data[], int size) {
    COUT << size << ":[";
    for (int i = 0; i < size; i++)
        COUT << (i == 0 ? "" : ",") << data[i];
    COUT << "]";
}

struct Graph {
    Array adj[maxNodes];
    int size;
    enum Color { None, Black, White };
    Color colors[maxNodes];
    Graph(): size(0) {
        for (int i = 0; i < maxNodes; i++) colors[i] = None;
    }
    void addEdge(int a, int b) {
        adj[a].push(b);
        adj[b].push(a);
    }
    bool dig(int node, Color color = Black) {
        COUT << node << "(" << colors[node] << "), new color " << color << endl;
        if (colors[node] != None) return (colors[node] == color);
        colors[node] = color;
        color = (color == Black) ? White : Black;
        for (int i = 0; i < adj[node].size; i++) {
            if (!dig(adj[node].data[i], color)) return false;
        }
        return true;
    }
};

int main() {
    while (1) {
        int nodes, edges;
        cin >> nodes;
        if (nodes == 0) return 0;
        cin >> edges;
        Graph g;
        for (int i = 0; i < edges; i++) {
            int a, b;
            cin >> a >> b;
            g.addEdge(a, b);
        }
        cout << (g.dig(0) ? "" : "NOT ") << "BICOLORABLE." << endl;
    }
    return 0;
}

