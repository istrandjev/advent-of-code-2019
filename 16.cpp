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

string do_step(const string& s) {
    string res;
    vector<int> psums(s.size() + 1, 0);
    for (int i = 0; i < (int)s.size(); ++i) {
        psums[i + 1] = psums[i] + (s[i] - '0');
    }
    auto get_sum = [&](int from, int to) {
        return psums[to + 1] - psums[from];
    };
    for (int i = 0; i < (int)s.size(); ++i) {
        int sum = 0;
        int repeats = i + 1;
        for (int j = repeats - 1; j < (int)s.size(); j += repeats * 4) {
            sum += get_sum(j, min(j + repeats - 1, (int)s.size() - 1));
        }

        for (int j = repeats - 1 + 2 * repeats; j < (int)s.size(); j += repeats * 4) {
            sum -= get_sum(j, min(j + repeats - 1, (int)s.size() - 1));
        }
        res.push_back(abs(sum) % 10 + '0');
    }
    return res;
}


int main() {
    string s;
    getline(cin, s);
    string original = s;
    const int total_phases = 100;
    for (int phase = 0; phase < total_phases; ++phase) {
        s = do_step(s);
    }
    cout << "Part 1 " << s.substr(0, 8) << endl;
    s = original;
    for (int i = 0; i < 10000 - 1; ++i) {
        s += original;
    }
    for (int phase = 0; phase < total_phases; ++phase) {
        s = do_step(s);
    }
    int offset = stoi(original.substr(0, 7));
    cout << "Part 2 " << s.substr(offset, 8) << endl;
    return 0;
}