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

struct point {
    ll x, y;
    ll code() const {
        return x * (1LL << 31) + y;
    }
};
ostream& operator<<(ostream& out, const point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
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

ll area(point a, point b, point c) {
    return a.x * b.y + a.y * c.x + b.x * c.y - a.y * b.x - a.x * c.y - b.y * c.x;
}
int sign(ll x) {
    if (x == 0) {
        return 0;
    }
    return (x < 0 ? -1 : 1);
}

struct vektor {
    vektor(const point& a, const point& o) : dx(a.x - o.x), dy(a.y - o.y), center(o) {
        ll d = evkl(abs(dx), abs(dy));
        dx /= d;
        dy /= d;
    }
    bool operator<(const vektor& other) const {
        if (dy == 0 && other.dy == 0) {
            return dx < other.dx;
        }
        if (sign(dy) != sign(other.dy)) {
            return sign(dy) > sign(other.dy);
        }
        point t1{center.x + dx, center.y + dy};
        point t2{center.x + other.dx, center.y + other.dy};    
        return sign(area(center, t1, t2)) < 0;
    }
    bool operator==(const vektor& other) const {
        return dx == other.dx && dy == other.dy;
    }
    ll dx, dy;
    point center;
};

int main() {
    string s;
    vector<string> a;
    while (getline(cin, s)) {
        a.push_back(s);
    }
    vector<point> points;
    for (int i = 0 ; i < (int)a.size(); ++i) {
        for (int j = 0; j < a[i].size(); ++j) {
            if (a[i][j] == '#') {
                points.push_back({i, j});
            }
        }
    }
    int res1 = 0;
    int best_center_idx;
    for (int i = 0; i < (int)points.size(); ++i) {
        set<vektor> visible;
        for (int j = 0; j < points.size(); ++j) {
            if (j == i) {
                continue;
            }
            visible.insert(vektor(points[j], points[i]));
        }
        if (visible.size() > res1) {
            res1 = visible.size();
            best_center_idx = i; 
        }
    }
    cout << "Part 1 " << res1 << endl;
    set<vektor> temp;
    for (int i = 0; i < (int)points.size(); ++i) {
        if (i == best_center_idx) {
            continue;
        }
        temp.insert(vektor(points[i], points[best_center_idx]));
    }
    vector<vektor> help(all(temp));
    ll answerx = points[best_center_idx].x + help[199].dx;
    ll answery = points[best_center_idx].y + help[199].dy;
    cout << "Part 2 " << answery * 100 + answerx << endl;
    return 0;
}