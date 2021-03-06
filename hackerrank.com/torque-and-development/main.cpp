#include <iostream>

#ifdef _DEBUG
#define DBG(S) cout << S
#else
#define DBG(S) 
#endif

using namespace std;
const int NMAX = 100001;

typedef long long i64;

template<class T, int S>
struct Stack {
    T* data;
    T* end;
    T* cap;
    Stack(): data(new T[S]), end(data), cap(data + S) {}
    ~Stack() { delete[] data; }
    inline void extend() {
        int size = (cap - data) * 2;
        T* ndata = new T[size];
        for (T *pc = data, *npc = ndata; pc != end; ++pc, ++npc) *npc = *pc;
        end = ndata + (end - data);
        cap = ndata + size;
        delete[] data;
        data = ndata;
    }
    inline void push(T v) { if (end == cap) extend(); *end++ = v; }
    inline T pop() { return *(--end); }
    inline bool empty() { return end == data; }
    void print() { cout << "["; for (T* pc = data; pc != end; ++pc) cout << " " << *pc; cout << " ]"; }
};

typedef Stack<int, 2> Road;

i64 test() {
    bool visited[NMAX] = {false,};
    Road road[NMAX];
    i64 nc, nr, cl, cr;
    cin >> nc >> nr >> cl >> cr;
    for(int a1 = 0; a1 < nr; a1++){
        int city_1;
        int city_2;
        cin >> city_1 >> city_2;
        road[city_1].push(city_2);
        road[city_2].push(city_1);
    }
    if (nr == 0 || cl <= cr) return nc*cl;
    int isles = 0;
    Stack<int, NMAX> s;
    for (int c = 1; c <= nc; ++c) {
        if (visited[c] == false) {
            isles++;
            s.push(c);
            visited[c] = true;
            DBG("Start from " << c << ":");
            while (!s.empty()) {
                int cc = s.pop();
                DBG(" " << cc);
                Road& r = road[cc];
                for (int* pc = r.data; pc != r.end; ++pc) {
                    if (!visited[*pc]) {
                        s.push(*pc);
                        visited[*pc] = true;
                    }
                }
            }
            DBG(endl);
        }
    }
    return ((nc - isles)*cr + isles*cl);
}

int main(){
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        cout << test() << "\n";
    }
    return 0;
}
