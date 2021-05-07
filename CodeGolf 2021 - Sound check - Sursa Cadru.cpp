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

ofstream fout("output.out");

void f(unsigned char n, unsigned char m, unsigned char ns, s *ss) {
    static vector<vector<string>> heatmap;
    heatmap.resize(n, vector<string>(m, "==="));

    if(ns != 0)
    {
        s *it = ss;
        //while(it != NULL)
        //{
            switch (it->i) {
                case 1:
                    heatmap[it->l - 1][it->c - 1] = "00" + to_string(it->i);
                    break;
                case 3:
                    heatmap[it->l - 1][it->c - 1] = "00" + to_string(it->i);
                    int itr = it->i;
                    for(int i = it->l; i <= it->l + 1; ++i)
                    {
                        --itr;
                        heatmap[i][it->c - 1] = "00" + to_string(itr);
                    }
                    itr = it->i;
                    for(int j = it->c; j <= it->c + 1; ++j)
                    {
                        --itr;
                        heatmap[it->l - 1][j] = "00" + to_string(itr);
                    }
                    int i = it->l;
                    int j = it->c;
                    itr = it->i;
                    while (i <= it->l + 1)
                    {
                        --itr;
                        heatmap[i][j] = "00" + to_string(itr);
                        ++i, ++j;
                    }
            }
        //}
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
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