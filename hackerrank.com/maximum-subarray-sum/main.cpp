#include <iostream>
using namespace std;

#define COUT if(0) cout <<
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORBE(t,i,b,e) for(t* i=b;i<e;i++)
#define MAX(a,b) (a)>(b)?(a):(b)

static const int NMAX = 100001;
typedef unsigned long long int ui64;
typedef long long int T;

template <class T>
struct tNode
{
    T value;
    tNode* l;
    tNode* r;
    tNode(): l(nullptr), r(nullptr) {}
};

template<class T, int S>
struct BinaryTree {
    tNode<T> nodes[S];
    tNode<T>* root;
    int size;
    int depth;
    BinaryTree(): root(nullptr), size(0), depth(0) {}
    tNode<T>* push(T val) {
        tNode<T>* node = &nodes[size++];
        node->value = val;
        if (root == nullptr) {
            root = node;
            depth = 1;
        }
        else {
            tNode<T>* parent = root;
            int nd = 2;
            for (;; nd++) {
                tNode<T>*& candidate = (val <= parent->value) ? parent->l : parent->r;
                if (candidate == nullptr) {
                    candidate = node;
                    break;
                }
                parent = candidate;
            }
            if (nd > depth) depth = nd;
        }
        return node;
    }
    tNode<T>* ceil(T val) {
        tNode<T>* node = root;
        tNode<T>* last = nullptr;
        while (node) {
            if (val == node->value) return node;
            if (val <  node->value) {
                last = node;
                node = node->l;
            }   
            else node = node->r;
        }
        return last;
    }
};

T test() {
    BinaryTree<T, NMAX> array;
    T n, m, val, sum = 0, result = 0;
    cin >> n >> m;
    COUT "    ==== n: " << n << "; m: " << m << " ====" << endl;
    for (int size = 0; size < n; size++) {
        cin >> val;
        if (result == m - 1) continue;
        val %= m;
        sum = (sum + val) % m;
        COUT "*** val: " << val << "; sum: " << sum;
        tNode<T>* ceil = array.ceil(sum + 1);
        if (ceil) {
            T diff = (sum + m - ceil->value);
            if (diff > result) result = diff;
            COUT "; ceil: " << ceil->value << ", diff: " << diff; 
        }
        else if (sum > result) result = sum;
        COUT "; result: " << result << endl;
        array.push(sum);
    }
    cout << "Tree depth: " << array.depth << endl;
    return result;
}

int main() {
    int t;
    cin >> t;
    while (t--) cout << test() << endl;
    return 0;
}
