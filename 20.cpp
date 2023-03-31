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

struct Position {
    int x, y;
    int level;
    Position(int _x, int _y, int _level = 0) : x(_x), y(_y), level(_level) {}
    bool operator==(const Position& o) const {
        return x == o.x && y == o.y && level == o.level;
    }
};
struct PositionHash {
    std::size_t operator()(Position const& position) const noexcept
    {
        return std::hash<long long>{}((ll)position.level * 1000000LL + (ll)position.x * 1000LL + (ll)position.y);
    }
};

int bfs(const vector<string>& a, const map<pair<int, int>, pair<int, int> >& portals, const pair<int, int>& source, const pair<int, int>& target, bool nested=false) {
    
    unordered_map<Position, int, PositionHash> vis;
    queue<Position> q;
    Position source_position(source.second, source.first, 0);
    Position target_position(target.second, target.first, 0);
    q.push(source_position);
    vis[source_position] = 0;
    int n = a.size();
    int m = a[0].size();
    int mindotx = 10000, maxdotx = 0, mindoty = 10000, maxdoty = 0;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (a[y][x] != '.') {
                continue;
            }
            mindotx = min(mindotx, x);
            maxdotx = max(maxdotx, x);
            mindoty = min(mindoty, y);
            maxdoty = max(maxdoty, y);
        }
    }
    int res = -1;
    while (!q.empty() && res == -1) {
        auto c = q.front();
        int cd = vis[c];
        q.pop();
        for (int l = 0; l < 4; ++l) {
            Position temp(c.x + moves[l][1], c.y + moves[l][0], c.level);
            if (temp.y < 0 || temp.y >= n || temp.x < 0 || temp.x >= m) {
                continue;
            }
            if (a[temp.y][temp.x] != '.') {
                continue;
            }
            if (vis.count(temp)) {
                continue;
            }
            if (temp == target_position) {
                res = cd + 1;
                break;
            }
            vis[temp] = cd + 1;
            q.push(temp);
        }

        auto it = portals.find({c.y, c.x});
        if (it == portals.end()) {
            continue;
        }
        Position nxt(it->second.second, it->second.first, c.level);

        if (nested) {
            if (c.x == mindotx || c.x == maxdotx || c.y == mindoty || c.y == maxdoty) {
                if (c.level == 0) {
                    continue;
                } else {
                    nxt.level--;
                }
            } else {
                nxt.level++;
            }
        }
        if (vis.count(nxt)) {
            continue;
        }
        if (nxt == target_position) {
            res = cd + 1;
            break;
        }
        vis[nxt] = cd + 1;
        q.push(nxt);
    }   
    return res;
}

int main() {
    vector<string> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    map<pair<int, int>, pair<int, int> > portals;
    int n = a.size();
    int m = a[0].size();
    unordered_map<string, vector<pair<int, int> > > by_code;
    pair<int, int> source, target;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!isalpha(a[i][j])) {
                continue;
            }
            string code;
            code.push_back(a[i][j]);
            pair<int, int> dots(-1, -1);
            for (int l = 0; l < 4; ++l) {
                int ty = i + moves[l][0];
                int tx = j + moves[l][1];
                if (ty < 0 || ty >= n || tx <0 || tx >= m) {
                    continue;
                }
                if (isalpha(a[ty][tx])) {
                    code.push_back(a[ty][tx]);
                    if (l == 1 || l == 2) {
                        reverse(all(code));
                    }
                }
                if (a[ty][tx] == '.') {
                    dots = {ty, tx};
                }
                
            }
            if (dots.first != -1) {
                if (code == "AA") {
                    source = dots;
                } else if (code == "ZZ") {
                    target = dots;
                } else {
                    by_code[code].push_back(dots);
                }
            }
        }
    }
    for (auto it : by_code) {
        for (int i = 0; i < it.second.size(); ++i) {
            for (int j = i + 1; j < it.second.size(); ++j) {
                portals[it.second[i]] = it.second[j];
                portals[it.second[j]] = it.second[i];
            }
        }
    }
    cout << "Part 1 " << bfs(a, portals, source, target) << endl;
    cout << "Part 2 " << bfs(a, portals, source, target, true) << endl;
    return 0;
}