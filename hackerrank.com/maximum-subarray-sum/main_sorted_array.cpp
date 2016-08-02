#include <iostream>
using namespace std;

#define COUT if(0) cout <<
#define FOR(i,n) for(int i=0;i<n;i++)
#define FORBE(t,i,b,e) for(t* i=b;i<e;i++)
#define MAX(a,b) (a)>(b)?(a):(b)

static const int NMAX = 100001;
typedef unsigned long long int ui64;
typedef long long int T;

T* sorted_array_find(T* data, ui64 size, T value) {
    while (size > 1) {
        ui64 p = size / 2;
        if (data[p] == value) {
            while (p < size - 1 && data[p+1] == value) p++;
            return &data[p];
        }
        else if (data[p] > value) size = p;
        else {
            data += p + 1;
            size -= p + 1;
        }
    }
    if (size == 0) return data;
    return (*data < value ? data + 1 : data);
}

T* sorted_array_push(T* data, ui64 size, T value) {
    T* pos = sorted_array_find(data, size, value);
    if (*pos == value) pos++;
    T* end = data + size;
    for (T* it = end; it > pos; it--) *it = *(it - 1);
    *pos = value;
    return pos;
}

T test() {
    T array[NMAX];
    T n, m, val, sum = 0, result = 0;
    cin >> n >> m;
    //COUT "    ==== n: " << n << "; m: " << m << " ====" << endl;
    for (int size = 0; size < n; size++) {
        cin >> val;
        if (result == m - 1) continue;
        val %= m;
        sum = (sum + val) % m;
        //COUT "*** val: " << val << "; sum: " << sum;
        T* pos = sorted_array_push(array, size, sum);
        //COUT "; push at [" << pos - array << "]";
        if (sum > result) result = sum;
        if (pos != array + size) {
            T diff = (sum + m - *(pos + 1));
            //COUT "; diff [" << pos - array + 1 << "]: " << *(pos + 1) << " == " << diff; 
            if (diff > result) result = diff;
        }
        //COUT "; result: " << result << endl;
    }
    return result;
}

T test_bf2() {
    T array[NMAX];
    T n, m;
    cin >> n >> m;

    T* end = array + n;
    FORBE(T, it, array, end) {
        cin >> *it;
        *it %= m;
    }
   
    T maxsum = 0;
    FORBE(T, it, array, end) {
        maxsum = MAX(*it, maxsum);
        for (T* jt = it - 1; jt >= array; jt--) {
            *jt += *it;
            if (*jt >= m) *jt -= m;
            maxsum = MAX(*jt, maxsum);
        }
    }

    return maxsum;
}

long long test_bf() {
    long long int array[NMAX];
    long long int n, m;
    cin >> n >> m;
    COUT "n: " << n << "; m: " << m << endl;
    COUT "read numbers: ";
    FOR(i, n) {
        long long int num;
        cin >> num;
        COUT num << " ";
        array[i] = num % m;
        COUT array[i] << ", ";
    }
    COUT endl;
   
    long long int maxsum = 0;
    FOR(i, n) {
        long long int cursum = 0;
        for (int j = i; j < n; j++) {
            cursum = (cursum + array[j]) % m;
            COUT " " << cursum;
            if (cursum > maxsum) {
                maxsum = cursum;
                COUT "!"; 
            }
        }
        for (int j = i; j < n-1; j++) {
            cursum = (m + cursum - array[j]) %m;
            COUT " " << cursum;
            if (cursum > maxsum) {
                maxsum = cursum;
                COUT "!"; 
            }
        }
    }
    COUT endl;
    
    return maxsum;
}

int main() {
    int t;
    cin >> t;
    while (t--) cout << test() << endl;
    return 0;
}
