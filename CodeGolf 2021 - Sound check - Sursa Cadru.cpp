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

    auto displayMatrix = [&]() {//good
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << heatmap[i][j] << " ";
            cout << '\n';
        }
    };

    auto stringCreator = [&](int value) {
        string space;
        if (value > 99)
            space = to_string(value);
        else if (value > 9)
            space = "0" + to_string(value);
        else
            space = "00" + to_string(value);
        if(value == 0)
            space = "===";
        return space;
    };//good

    heatmap.resize(n, vector<string>(m, "==="));

    if (ns != 0) {
        for (int it = 0; it < ns; ++it) {
            int len = ss[it].i;
            int intensity = ss[it].i;
            heatmap[ss[it].l - 1][ss[it].c - 1] = stringCreator(intensity);
            intensity--;
            ///line -
            for (int j = ss[it].c; j <= ss[it].c + len - 2; ++j)
                if (j < m) {
                    heatmap[ss[it].l - 1][j] = stringCreator(intensity);
                    intensity--;
                } //todo this 7 more times (total 8) maybe do func
            intensity = ss[it].i - 1;
            for (int j = ss[it].c - 2; j >= ss[it].c - len; --j)
                if (j >= 0) {
                    heatmap[ss[it].l - 1][j] = stringCreator(intensity);
                    intensity--;
                }

            ///column |
            intensity = ss[it].i - 1;
            for (int i = ss[it].l; i <= ss[it].l + len - 2; ++i)
                if (i < n) {
                    heatmap[i][ss[it].c - 1] = stringCreator(intensity);
                    intensity--;
                }
            intensity = ss[it].i - 1;
            for (int i = ss[it].l - 2; i >= ss[it].l - len; --i)
                if (i >= 0) {
                    heatmap[i][ss[it].c - 1] = stringCreator(intensity);
                    intensity--;
                }

            ///diagonal /
            int i = ss[it].l - 2;
            int j = ss[it].c;
            intensity = ss[it].i - 1;
            while (j < ss[it].c + len - 1 && j < m && i >= 0) {
                heatmap[i][j] = stringCreator(intensity);
                intensity--;
                j++;
                i--;
            }
            i = ss[it].l;
            j = ss[it].c - 2;
            intensity = ss[it].i - 1;
            while (i < ss[it].l + len - 1 && j >= 0 && i < n) {
                heatmap[i][j] = stringCreator(intensity);
                intensity--;
                j--;
                i++;

            }

            ///diagonal '\'
            i = ss[it].l;
            j = ss[it].c;
            intensity = ss[it].i - 1;
            while (i < ss[it].l + len - 1 && j < m && i < n) {
                heatmap[i][j] = stringCreator(intensity);
                intensity--;
                j++;
                i++;
            }
            i = ss[it].l - 2;
            j = ss[it].c - 2;
            intensity = ss[it].i - 1;
            while (i >= ss[it].l - len  && j >= 0 && i >= 0) {
                heatmap[i][j] = stringCreator(intensity);
                intensity--;
                j--;
                i--;
            }
        }
    }

    displayMatrix();
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