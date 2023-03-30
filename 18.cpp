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


ll encode(int y, int x, int mask) {
    return (ll)mask * 10000LL + (ll)y * 100LL + (ll)x;
}

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

ll solve(const int sy, const int sx, const int fromy, const int toy, const int fromx, const int tox, const vector<string>& a) {
    int target_mask = 0;
    for (int i = fromy; i < toy; ++i) {
        for (int j = fromx; j < tox; ++j) {
            if (a[i][j] >= 'a' && a[i][j] <= 'z') {
                target_mask |= (1 << (a[i][j] - 'a'));
            }
        }
    }
    queue<pair<ll, pair<int, int> > > q;
    q.push({0, {sy, sx}});

    unordered_map<ll, int> vis;
    ll tcode = encode(sy, sx, 0);
    vis[tcode] = 0;
    int result = -1;
    ll final_code;
    while (!q.empty() && result == -1) {
        auto c = q.front();
        q.pop();
        int cy = c.second.first;
        int cx = c.second.second;
        ll mask = c.first;
        ll ccode = encode(cy, cx, mask);
        int cd = vis[ccode];
        for (int l = 0; l < 4; ++l) {
            int ty = cy + moves[l][0];
            int tx = cx + moves[l][1];
            if (ty < fromy || ty >= toy || tx < fromx || tx >= tox || a[ty][tx] == '#') {
                continue;
            }

            if (a[ty][tx] >= 'A' && a[ty][tx] <= 'Z' && (target_mask & (1 << (a[ty][tx] - 'A'))) && !(mask & (1 << (a[ty][tx] - 'A')))) {
                continue;
            }

            ll nmask = mask;
            if (a[ty][tx] >= 'a' && a[ty][tx] <= 'z') {
                nmask |= (1 << (a[ty][tx] - 'a'));
            }
            ll kod = encode(ty, tx, nmask);
            if (nmask == target_mask) {
                result = cd + 1;
                final_code = kod;
                break;
            }
            
            if (vis.count(kod)) {
                continue;
            }
            vis[kod] = cd + 1;
            q.push({nmask, {ty, tx}});
        }
    }

    return result;
}
int main() { 
    vector<string> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    int n = a.size();
    int m = a[0].size();
    int sx, sy;
    int target_mask = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '@') {
                sy = i;
                sx = j;
            }
        }
    }
    
    cout << "Part 1 " << solve(sy, sx, 0, n, 0, m, a) << endl;
    for (int l = 0; l < 4; ++l) {
        a[sy + moves[l][0]][sx + moves[l][1]] = '#';
    }
    a[sy][sx] = '#';
    int res2 = 0;
    res2 += solve(sy - 1, sx + 1, 0, sy, sx, m, a);
    res2 += solve(sy - 1, sx - 1, 0, sy, 0, sx, a);
    res2 += solve(sy + 1, sx + 1, sy, n, sx, m, a);
    res2 += solve(sy + 1, sx - 1, sy, n, 0, sx, a);
    cout << "Part 2 " << res2 << endl;
    return 0;
}