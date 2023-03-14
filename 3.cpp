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

char letter_to_move[128];

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

vector<pair<int, int> > parse(const string& s) {
    vector<pair<int, int> > res;
    vector<string> tokens = split(s, ',');
    pair<int, int> c;
    for (const string& t : tokens) {
        int direction = letter_to_move[t[0]];
        int number = stoi(t.substr(1));
        for (int i = 0; i < number; ++i) {
            c.first += moves[direction][0];
            c.second += moves[direction][1];
            res.push_back(c);
        }
    }
    return res;
}
map<pair<int, int>, int > get_steps(const vector<pair<int, int> >& positions) {
    map<pair<int, int>, int> res;    
    for (int i = 0; i < (int)positions.size(); ++i) {
        const pair<int, int>& p = positions[i];
        if (res.count(p)) {
            continue;
        }
        res[p] = i + 1;
    }
    return res;
}
int main() {
    letter_to_move['U'] = 0;
    letter_to_move['R'] = 1;
    letter_to_move['D'] = 2;
    letter_to_move['L'] = 3;

    string s;
    getline(cin, s);
    vector<pair<int, int> > positions1 = parse(s);
    getline(cin, s);
    vector<pair<int, int> > positions2 = parse(s);
    set<pair<int, int> > met(all(positions2));
    ll best = 1LL << 61;
    for (auto p : positions1) {
        if (met.count(p)) {
            best = min(best, (ll)abs(p.first) + (ll)abs(p.second));
        }
    }
    cout << "Part 1 " << best << endl;
    auto steps1 = get_steps(positions1);
    auto steps2 = get_steps(positions2);
    best = 1LL << 60;
    for (auto p: steps1) {
        auto it = steps2.find(p.first);
        if (it == steps2.end()) {
            continue;
        }
        if (p.second + it->second <  best) {
            best = p.second + it->second;
        } 
    }
    cout << "Part 2 " << best << endl; 
    return 0;
}