// I/O
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
// Containers
#include <list>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <stack>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
// Other
#include <algorithm>
#include <bitset>
#include <functional>
#include <iterator>
#include <tuple>
#include <string>
#include <utility>

using namespace std;

struct s {
    unsigned char i;
    unsigned char l;
    unsigned char c;
};

void f(unsigned char n, unsigned char m, unsigned char ns, s *ss) {
    string heatmap[(int)n + 1][(int)m + 1];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            heatmap[i][j] = "===";

    if(ns != 0)
    {
        //set of instructions
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            cout << heatmap[i][j] << " ";
        cout << '\n';
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        cout << "No arguments";
        return 0;
    }
    string sInputFile = argv[1];
    ifstream in("test.txt");

    static int n;
    static int m;

    static int ns;
    static s *ss;

    in >> n >> m;

    in >> ns;
    ss = new s[ns];
    for (int index = 0; index < ns; index++) {
        int i, l, c;
        in >> i >> l >> c;
        ss[index].i = i;
        ss[index].l = l;
        ss[index].c = c;
    }

    f(n, m, ns, ss);
    delete[] ss;
    return 0;
}