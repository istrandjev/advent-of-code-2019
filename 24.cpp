#define _CRT_SECURE_NO_DEPRECATE
#include <iostream> 
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <map>
#include <set>
#include <math.h>
#include <stack>
#include <deque>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <regex>

#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;
int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int get_code(const vector<string>& a) {
    int res = 0;
    int mul = 1;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < (int)a[0].size(); ++j) {
            res += mul * (a[i][j] == '#');
            mul *= 2;
        }
    }
    return res;
}

int sum_side(int tx, int ty, const vector<string>& a) {
    int n = a.size();
    int m = a[0].size();
    int res = 0;
    if (tx == 0) {
        int si = (ty == 1 ? 0 : m - 1);
        for (int i = 0; i < n; ++i) {
            res += (a[i][si] == '#');
        }
    } else {
        int si = (tx == 1 ? 0 : n - 1);
        for (int i = 0; i < m; ++i) {
            res += (a[si][i] == '#');
        }
    }
    return res;
}

int main() {
    vector<string> a(5);
    for (int i = 0 ;i < 5; ++i) {
        getline(cin, a[i]);
    }
    vector<string> original_a = a;

    unordered_set<int> codes;
    codes.insert(get_code(a));
    int n = a.size();
    int m = a[0].size();
    while (true) {
        vector<string> b(5, string(5, '.'));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int cnt = 0;
                for (int l = 0; l < 4; ++l) {
                    int tx = i + moves[l][0];
                    int ty = j + moves[l][1];
                    if (tx < 0 || ty < 0 || tx >= n || ty >= m) {
                        continue;
                    }
                    cnt += (a[tx][ty] == '#');
                }
                if (cnt == 1 || (cnt == 2 && a[i][j] == '.')) {
                    b[i][j] = '#';
                }
            }
        }
        int current_code = get_code(b);
        if (codes.insert(current_code).second == false) {
            cout << "Part 1 " << current_code << endl;
            break;
        }
        a = b;
    }  
    
    vector<vector<string> > levels(500, vector<string>(5, string(5, '.')));
    const int depth_offset = 220;
    levels[depth_offset] = original_a;
    const int total_steps = 200;
    for (int step = 0; step < total_steps; ++step) {
        vector<vector<string> > new_levels(500, vector<string>(5, string(5, '.')));
        for (int depth = 1; depth < (int)levels.size() - 1; ++depth) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (i == n / 2 && j == m / 2) {
                        continue;
                    }
                    int cnt = 0;
                    for (int l = 0; l < 4; ++l) {
                        int tx = i + moves[l][0];
                        int ty = j + moves[l][1];

                        if (tx == n / 2 && ty == m / 2) {
                            cnt += sum_side(moves[l][0], moves[l][1], levels[depth + 1]);
                        } else if (ty < 0 || ty >= m || tx < 0 || tx >= n) {
                            int cx = n / 2 + moves[l][0];
                            int cy = m / 2 + moves[l][1];
                            cnt += (levels[depth - 1][cx][cy] == '#'); 
                        } else {
                            cnt += (levels[depth][tx][ty] == '#');
                        }                
                    }
                    if (cnt == 1 || (cnt == 2 && levels[depth][i][j] == '.')) {
                        new_levels[depth][i][j] = '#';
                    }
                }
            }
        }
        levels = new_levels;
    }
    int sum = 0;
    for (auto l : levels) {
        for (auto r : l) {
            for (auto c : r) {
                sum += (c == '#');
            }
        }
    }
    cout << "Part 2 " << sum << endl;
    return 0;
}