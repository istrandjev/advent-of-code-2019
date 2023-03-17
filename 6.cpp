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

vector<vector<int> > ne;
vector<int> dad;
int dfs(int v, int depth) {
    int res = depth;
    for (auto nxt : ne[v]) {
        if (nxt == dad[v]) {
            continue;
        }
        res += dfs(nxt, depth + 1);
    }
    return res;
}
vector<string> split(const string& s, char delim=' ') {
    vector<string> res;
    string cur;
    for (auto c : s) {
        if (c == delim) {
            res.push_back(cur);
            cur = "";
        } else {
            cur.push_back(c);
        }
    }
    if (s.back() != delim) {
        res.push_back(cur);
    }
    return res;
}

int bfs(int source, int destination) {
    queue<int> q;
    q.push(source);
    vector<int> vis(dad.size(), -1);
    vis[source] = 0;
    while (!q.empty() && vis[destination] == -1) {
        int c = q.front();
        q.pop();
        for (auto nxt : ne[c]) {
            if (vis[nxt] != -1) {
                continue;
            } 
            vis[nxt] = vis[c] + 1;
            q.push(nxt);
        }
    }
    return vis[destination];
}
int main() {
    unordered_map<string, int> encode;
    auto get_code = [&](const string &s) {
        auto it = encode.find(s);
        if (it != encode.end()) {
            return it->second;
        }
        int res = (int)encode.size();
        encode.insert({s, encode.size()});
        return res;
    };
    string ls;
    while (getline(cin, ls)) {
        auto temp = split(ls, ')');
        int code1 = get_code(temp[0]);
        int code2 = get_code(temp[1]);
        while (ne.size() <= max(code1, code2)) {
            ne.push_back({});
        }
        while(dad.size() <= max(code1, code2)) {
            dad.push_back(0);
        }
        ne[code1].push_back(code2);
        ne[code2].push_back(code1);
        dad[code2] = code1;
    }
    cout << "Part 1 " << dfs(encode["COM"], 0) << endl;
    cout << "Part 2 " << bfs(dad[encode["YOU"]], dad[encode["SAN"]]) << endl; 
    return 0;
}