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
struct ingredient {
    string name;
    ll quantity;
    bool operator<(const ingredient& o) const {
        if (name != o.name) {
            return name < o.name;
        }
        return quantity < o.quantity;
    }
};

vector<ingredient> parse_ingredients(const string& s) {
    vector<ingredient> res;
    regex ingredient_re("\\s?(\\d+) ([A-Z]+)");
    vector<string> parts = split(s, ',');
    smatch match;
    for (auto part : parts) {
        if (!regex_match(part, match, ingredient_re)) {
            cout << "Could not parse ingredient " << part << endl;
            exit(1);
        }
        res.push_back({match.str(2), stoll(match.str(1))});
    }
    return res;
}

ll needed_ore(ll fuel_units, const unordered_map<string, pair<ll, vector<ingredient> > >& formulas) {
    unordered_map<string, ll> needed;
    needed.insert({"FUEL", fuel_units});
    queue<string> q;
    q.push("FUEL");
    ll total_ore = 0;
    while (!q.empty()) {
        string c = q.front();
        q.pop();
        ll cneeded = needed[c];
        if (cneeded <= 0) {
            continue;
        }

        auto cformula = formulas.find(c)->second;
        ll num_formulas = (cneeded + cformula.first - 1) / cformula.first;
        for (auto ing : cformula.second) {
            if (ing.name == "ORE") {
                total_ore += num_formulas * ing.quantity;
                continue;
            }
            auto it = needed.find(ing.name);
            if (it == needed.end() || it->second <= 0) {
                if (it == needed.end()) {
                    it = needed.insert({ing.name, 0}).first;
                }
                it->second += ing.quantity * num_formulas;
                if (it->second > 0) {
                    q.push(ing.name);
                }
            } else {
                it->second += ing.quantity * num_formulas;
            }
        }
        needed[c] -= num_formulas * cformula.first;
    }
    return total_ore;
}

int main() {
    regex reaction_re("(.*) => (\\d+) ([A-Z]+)");
    smatch match;
    string s;

    unordered_map<string, pair<ll, vector<ingredient> > > formulas;
    while (getline(cin, s)) {
        if (!regex_match(s, match, reaction_re)) {
            cout << "Could not parse " << s << endl;
            exit(1);
        }
        auto ingredients = parse_ingredients(match.str(1));
        formulas.insert({match.str(3), {stoll(match.str(2)), ingredients}});
    }
    
    ll res1 = needed_ore(1, formulas);
    cout << "Part 1 " << res1 << endl;
    ll total_ore = 1000000000000LL;
    ll beg = 1, end = total_ore;
    while (end - beg > 1) {
        ll mid = (end + beg) / 2;
        ll needed = needed_ore(mid, formulas);
        if (needed <= total_ore) {
            beg = mid;
        } else {
            end = mid;
        }
    } 
    cout << "Part 2 " << beg << endl;
    return 0;
}