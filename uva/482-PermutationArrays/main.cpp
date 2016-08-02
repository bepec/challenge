#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int NMAX = 1000;
const int LMAX = 4096;

bool test()
{
    int indexes[NMAX];
    char line[LMAX];
    char* numbers[NMAX];

    gets(line);
    if (line[0] == 0) return false;

    int ncount = 0;
    for (char* ws = line; ws != (char*)1; ws = strchr(ws, ' ')+1) {
        sscanf(ws, "%d", &indexes[ncount]);
        ncount++;
    }

    gets(line);
    char* ws = line;
    for (int i = 0; i < ncount; i++) {
        numbers[i] = ws;
        ws = strchr(ws, ' ');
        if (ws == 0) break;
        *ws = 0;
        ws++;
    }

    for (int i = 0; i < ncount; i++) {
        puts(numbers[indexes[i] - 1]);
    }
    puts("");
    return true;
}

int main() {
    int n;
    cin >> n;
    while (n) if (test()) n--;

    return 0;
}
