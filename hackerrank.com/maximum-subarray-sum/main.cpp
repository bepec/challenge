#include <iostream>
using namespace std;

#define COUT if(0) cout <<
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORBE(t,i,b,e) for(t* i=b;i<e;i++)
#define MAX(a,b) ((a)>(b)?(a):(b))

static const int NMAX = 100001;
typedef unsigned long long int ui64;
typedef long long int T;

template<class T, int S>
struct AvlTree {
    struct Node {
        static Node* getnull() {
            static Node null;
            return &null;
        }
        inline bool isnull() { return this == getnull(); }
        T value;
        int height = -1;
        Node* kids[2] = { nullptr, nullptr };
        Node(const T& v): value(v), height(0) {
            kids[0] = getnull();
            kids[1] = getnull();
        }
        Node() {}
        Node(const Node&) = default;
        Node& operator= (const Node&) = default;
    };

    Node nodes[S];
    Node* root = Node::getnull();
    int size = 0;

    Node* insert(T val) {
        return insert(val, root);
    }

    Node* insert(T val, Node*& node) {
        if (node->isnull()) {
            node = &nodes[size++];
            *node = Node(val);
            return node;
        }
        Node*& kid = node->kids[val > node->value];
        Node* inserted = insert(val, kid);
        node->height = MAX(node->height, kid->height + 1);
        node = balance(node);
        return inserted;
    }

    Node* rotate(Node* node, int dir) {
        node->height -= 2;
        Node* kid = node->kids[dir];
        node->kids[dir] = kid->kids[!dir];
        kid->kids[!dir] = node;
        return kid;
    }

    // true if right kid is heavier, false otherwise
    bool bias(Node* node) {
        return (node->kids[0]->height - node->kids[1]->height < 0);
    }

    Node* balance(Node* node) {
        if (node->height < 2) return node;
        // right goes negative
        int bal = node->kids[0]->height - node->kids[1]->height;
        if (bal >= -1 && bal <=1 ) return node;
        bool dir = bias(node);
        Node* heavy_kid = node->kids[dir];
        if (bias(heavy_kid) != dir) {
            node->kids[dir] = rotate(heavy_kid, !dir);
        }
        return rotate(node, dir);
    }

    Node* find(T val, Node* node) {
        if (node->isnull()) return nullptr;
        if (node->value > val) return node;
        return find(val, node->kids[val > node->value]);
    }

    Node* ceil(T val) {
        Node* node = root;
        Node* last = nullptr;
        while (!node->isnull()) {
            if (node->value == val) return node;
            if (node->value < val) node = node->kids[1];
            else {
                last = node;
                node = node->kids[0];
            }
        }
        return last;
    }

    template<class F> void iterate(F& func) { iterate(func, root); }
    template<class F> bool iterate(F& func, Node* node) {
        if (node->isnull()) return true;
        if (iterate(func, node->kids[0]) == false) return false;
        if (func(node) == false) return false;
        return iterate(func, node->kids[1]);
    }
};


T test() {
    AvlTree<T, NMAX> array;
    T n, m, val, sum = 0, result = 0;
    cin >> n >> m;
    COUT "    ==== n: " << n << "; m: " << m << " ====" << endl;
    for (int size = 0; size < n; size++) {
        cin >> val;
        if (result == m - 1) continue;
        val %= m;
        sum = (sum + val) % m;
        COUT "*** val: " << val << "; sum: " << sum;
        auto ceil = array.ceil(sum + 1);
        if (ceil) {
            T diff = (sum + m - ceil->value);
            if (diff > result) result = diff;
            COUT "; ceil: " << ceil->value << ", diff: " << diff; 
        }
        else if (sum > result) result = sum;
        COUT "; result: " << result << endl;
        array.insert(sum);
    }
    //cout << "Tree depth: " << array.depth << endl;
    return result;
}

int main() {
    int t;
    cin >> t;
    while (t--) cout << test() << endl;
    return 0;
}
