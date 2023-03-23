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

struct moon {
    ll x, y, z;
    ll vx, vy, vz;
    moon(ll _x, ll _y, ll _z) : x(_x), y(_y), z(_z), vx(0), vy(0), vz(0) {}

    void do_move() {
        x += vx;
        y += vy;
        z += vz;
    }
    ll get_kinetic() const {
        return abs(vx) + abs(vy) + abs(vz);
    }
    ll get_potential() const {
        return abs(x) + abs(y) + abs(z);
    }
    ll get_energy() const {
        return get_kinetic() * get_potential();
    }
};

inline void affect(ll lhs, ll rhs, ll& lhsv, ll& rhsv) {
    if (lhs == rhs) {
        return;
    }
    if (lhs < rhs) {
        lhsv += 1;
        rhsv -= 1;
    } else {
        lhsv -= 1;
        rhsv += 1;
    }
}

void do_gravity(moon& a, moon& b) {
    
    affect(a.x, b.x, a.vx, b.vx);
    affect(a.y, b.y, a.vy, b.vy);
    affect(a.z, b.z, a.vz, b.vz);
}


ll solve(vector<ll> coordinates) {
    int n = coordinates.size();
    vector<ll> velocities(n, 0);
    map<pair<vector<ll>, vector<ll> >, ll > met;
    met.insert({{coordinates, velocities}, 0});
    
    for (ll step = 1;;step++) {
        for (int i =0 ; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                affect(coordinates[i], coordinates[j], velocities[i], velocities[j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            coordinates[i] += velocities[i];
        }
        auto it = met.find({coordinates, velocities});
        if (it == met.end()) {
            met.insert({{coordinates, velocities}, step});
            continue;
        } 
        return step - it->second;
    }
}

long long evkl(long long a, long long b) {
    long long r;
    if (b > a)
        swap(b, a);
    if (a == 0) {
        if (b != 0)
            return b;
        else
            return 1;
    }
    if (b == 0)
        return a;
    while (a % b) {
        r = a % b;
        a = b;
        b = r;
    }
    return b;
}

ll lcm(ll x, ll y) {
    ll d = evkl(x, y);
    return (x / d) * y;
}

int main() {
    regex moon_regex("<x=(-?\\d+), y=(-?\\d+), z=(-?\\d+)>");
    string s;
    vector<moon> moons;
    smatch match;
    while (getline(cin, s)) {
        if (!regex_match(s, match, moon_regex)) {
            cout << "Could not parse " << s << endl;
            exit(1); 
        }
        moons.emplace_back(stoll(match.str(1)), stoll(match.str(2)), stoll(match.str(3)));
    }
    vector<ll> xs, ys, zs;
    for (const auto& m: moons) {
        xs.push_back(m.x);
        ys.push_back(m.y);
        zs.push_back(m.z);
    }
    const int max_steps = 1000;
    for (int step = 0; step < max_steps; ++step) {
        for (int i = 0; i < (int)moons.size(); ++i) {
            for (int j = i + 1; j < (int)moons.size(); ++j) {
                do_gravity(moons[i], moons[j]);
            }
        }
        for (auto& m : moons) {
            m.do_move();
        }
    }
    ll res1 = 0;
    for (const auto& m : moons) {
        res1 += m.get_energy();
    }
    cout << "Part 1 " << res1 << endl;
    ll res2 = solve(xs);
    res2 = lcm(res2, solve(ys));
    res2 = lcm(res2, solve(zs));
    cout << "Part 2 " << res2 << endl;
    return 0;
}