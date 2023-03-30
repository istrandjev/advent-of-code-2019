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

#include "intcode.h"

#define all(v) v.begin(),v.end()
using namespace std;
typedef long long ll;

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
int dirs[4] = {0, 2, 3, 1};

vector<string> field;
vector<ll> outputs;
void dfs(int y, int x, Program& program) {
    for (int l = 0; l < 4; ++l) {
        int ty = y + moves[dirs[l]][0];
        int tx = x + moves[dirs[l]][1];
        if (tx < 0 || tx > 500 || ty < 0 || ty > 500) {
            continue;
        }
        if (field[ty][tx] != '?') {
            continue;
        }
        program.inputs.push(l + 1);
        program.run_till_input_needed(outputs);
        if (outputs.back() == 0) {
            field[ty][tx] = '#';
            continue;
        }
        
        if (outputs.back() == 1) {
            field[ty][tx] = '.';
        } else {
            field[ty][tx] = '$';
        }
        dfs(ty, tx, program);
        program.inputs.push((l ^ 1) + 1);
    }
}
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers = Program::parse_numbers(s);
    Program program(numbers, {});
    field.clear();
    field.resize(501, string(501, '?'));
    field[250][250] = 'S';
    dfs(250, 250, program);
    int ox, oy = -1;
    for (int i = 0; i < 500 && oy == -1; ++i) {
        for (int j = 0; j < 500; ++j) {
            if (field[i][j] == '$') {
                oy = i;
                ox = j;
                break;
            }
        }
    }
    queue<pair<int, int> > q;
    vector<vector<int> > vis(500, vector<int>(500, -1));
    q.push({250, 250});
    vis[250][250] = 0;
    int res1 = -1;
    while (!q.empty() && res1 == -1) {
        auto c = q.front();
        q.pop();
        for (int l = 0; l < 4; ++l) {
            int ty = c.first + moves[l][0];
            int tx = c.second + moves[l][1];
            if (ty < 0 || ty > 500 || tx < 0 || tx > 500) {
                continue;
            }
            if (field[ty][tx] == '#' || vis[ty][tx] != -1) {
                continue;
            }
            vis[ty][tx] = vis[c.first][c.second] + 1;
            q.push({ty, tx});
            if (field[ty][tx] == '$') {
                res1 = vis[ty][tx];
                break;
            }
        }
    }
    cout << "Part 1 " << res1 << endl;
    queue<pair<int, int> > oq;
    oq.push({oy, ox});
    for (int i = 0; i < (int)vis.size(); ++i) {
        fill(all(vis[i]), -1);
    }   
    vis[oy][ox] = 0;
    int res2 = -1;
    while (!oq.empty()) {
        auto c = oq.front();
        oq.pop();
        for (int l = 0; l < 4; ++l) {
            int ty = c.first + moves[l][0];
            int tx = c.second + moves[l][1];
            if (ty < 0 || ty > 500 || tx < 0 || tx > 500) {
                continue;
            }
            if (field[ty][tx] == '#' || vis[ty][tx] != -1) {
                continue;
            }
            vis[ty][tx] = vis[c.first][c.second] + 1;
            res2 = max(res2, vis[ty][tx]);
            oq.push({ty, tx});
        }
    }
    cout << "Part 2 " << res2 << endl; 
    return 0;
}