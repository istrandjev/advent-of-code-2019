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

ll get_fuel(ll module_wieght, bool add_fuel) {
    ll res = (module_wieght / 3  - 2);
    ll req = add_fuel ? res : 0;
    while (req > 0) {
        req = (req / 3 - 2);
        res += max(req, 0LL);
    }
    return res;
}
int main() {
    vector<int> fuels;
    ll res1 = 0;
    ll res2 = 0;
    int f;
    while (scanf("%d", &f) != EOF) {
        res1 += get_fuel(f, false);
        res2 += get_fuel(f, true);
    }
    cout << "Part 1 " << res1 << endl;
    cout << "Part 2 " << res2 << endl;

    return 0;
}