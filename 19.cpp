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

bool check(const vector<ll>& numbers, int x, int y) {
    return Program(numbers, {x, y}).get_output();
}

pair<int, int> get_interval(const vector<ll>& numbers, int y) {
    int step = max(1, y / 15);
    int x = 0;
    while (!check(numbers, x, y)) {
        x += step;
    }
    int beg = 0;
    int end = x;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (check(numbers, mid, y)) {
            end = mid;
        } else {
            beg = mid;
        }
    }
    int minx = end;
    beg = x;
    end = y * 2;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (check(numbers, mid, y)) {
            beg = mid;
        } else {
            end = mid;
        }
    }
    int maxx = beg;
    return {minx, maxx};
}

bool works(const vector<ll>& numbers, int y) {
    auto interval1 = get_interval(numbers, y);
    auto interval2 = get_interval(numbers, y + 99);
    int fromx = max(interval1.first, interval2.first);
    int tox = min(interval1.second, interval2.second);
    return tox - fromx >= 99;
}
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers = Program::parse_numbers(s);
    vector<string> a(50, string(50, '.'));
    int res1 = 0;
    for (int x = 0; x < 50; ++x) {
        for (int y = 0; y < 50; ++y) {
            if (check(numbers, x, y)) a[x][y] = '#';
            res1 += check(numbers, x, y);
        }
    }
    
    cout << "Part 1 " << res1 << endl;
    int beg = 100, end = 50000;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (works(numbers, mid)) {
            end = mid;
        } else {
            beg = mid;
        }
    }
    int y = end;
    int x = get_interval(numbers, end + 99).first;
    cout << "Part 2 " << x * 10000 + y << endl;
    return 0;
}