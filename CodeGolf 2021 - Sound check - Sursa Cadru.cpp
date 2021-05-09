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

//ofstream fout("output.out");

void f(unsigned char n, unsigned char m, unsigned char ns, s *ss) {
    static vector<vector<int>> soundSources;
    struct soundDirection {
        int val;
        int dir;
    };
    static soundDirection heatmap[500][500];

    auto debugSoundSource = [&]() {
        cout << "\n \n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                cout << soundSources[i][j] << " ";
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
        if (value == 0)
            space = "===";
        return space;
    };//good

    auto checkCase = [&](int x, int y, int intensity, int direction) {
        if (soundSources[x][y] == 0) {
            if (heatmap[x][y].val == 0) {
                heatmap[x][y].val = intensity;
                heatmap[x][y].dir = direction;
            } else {
                if (abs(heatmap[x][y].dir - direction) == 4) {
                    if (intensity < heatmap[x][y].val) {
                        heatmap[x][y].val = intensity;
                        heatmap[x][y].dir = direction;
                    }
                } else {
                    if (heatmap[x][y].dir == direction) {
                        heatmap[x][y].val += intensity;
                    } else {
                        if (abs(heatmap[x][y].dir - direction) == 2 || abs(heatmap[x][y].dir - direction) == 6) {
                            heatmap[x][y].val = (heatmap[x][y].val + intensity) / 2;
                            heatmap[x][y].dir = direction;
                        }
                    }
                }

            }
        }
    };

    auto displayMatrix = [&]() {//good
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j)
                //cout << heatmap[i][j] << " ";
                cout << stringCreator(heatmap[i][j].val) << " ";
            cout << '\n';
        }
    };

    soundSources.resize(n, vector<int>(m, 0));

    if (ns != 0) {

        for (int it = 0; it < ns; ++it) {
            if ((ss[it].l - 1 >= 0 && ss[it].l - 1 < n) && (ss[it].c - 1 >= 0 && ss[it].c - 1 < m))
                soundSources[ss[it].l - 1][ss[it].c - 1] += ss[it].i;
        }

        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < m; ++y) {
                if (soundSources[x][y] != 0) {
                    int len = soundSources[x][y];
                    heatmap[x][y].val = soundSources[x][y];
                    ///line -
                    int intensity = soundSources[x][y] - 1;
                    for (int j = y + 1; j <= y + len - 1; ++j)
                        if (j < m) {
                            checkCase(x, j, intensity, 3);
                            intensity--;
                        }
                    intensity = soundSources[x][y] - 1;
                    for (int j = y - 1; j >= y - len + 1; --j)
                        if (j >= 0) {
                            checkCase(x, j, intensity, 7);
                            intensity--;
                        }
                    ///column |
                    intensity = soundSources[x][y] - 1;
                    for (int i = x + 1; i <= x + len - 1; ++i)
                        if (i < n) {
                            checkCase(i, y, intensity, 5);
                            intensity--;
                        }
                    intensity = soundSources[x][y] - 1;
                    for (int i = x - 1; i >= x - len + 1; --i)
                        if (i >= 0) {
                            checkCase(i, y, intensity, 1);
                            intensity--;
                        }

                    ///diagonal /
                    int i = x - 1;
                    int j = y + 1;
                    intensity = soundSources[x][y] - 1;
                    while (j < y + len && i >= 0 && j < m) {
                        checkCase(i, j, intensity, 2);
                        --intensity;
                        --i;
                        ++j;
                    }
                    i = x + 1;
                    j = y - 1;
                    intensity = soundSources[x][y] - 1;
                    while (i < x + len && i < n && j >= 0) {
                        checkCase(i, j, intensity, 6);
                        --intensity;
                        ++i;
                        --j;
                    }

                    ///diagonal '\'
                    i = x + 1;
                    j = y + 1;
                    intensity = soundSources[x][y] - 1;
                    while (i < x + len && i < n && j < m) {
                        checkCase(i, j, intensity, 4);
                        --intensity;
                        ++i;
                        ++j;
                    }
                    i = x - 1;
                    j = y - 1;
                    intensity = soundSources[x][y] - 1;
                    while (i >= x - len + 1 && i >= 0 && j >= 0) {
                        checkCase(i, j, intensity, 8);
                        --intensity;
                        --i;
                        --j;
                    }
                }
            }
        }
    }
    displayMatrix();
    //debugSoundSource();
    //todo luat teste incepand cu 15 si notat observatii
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