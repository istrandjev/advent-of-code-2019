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

void run_program(vector<ll>& numbers) {
    int ip = 0;
    for (int ip = 0; numbers[ip] != 99; ip += 4) {
        ll val;
        if (numbers[ip] == 1) {
            val = numbers[numbers[ip + 1]] + numbers[numbers[ip + 2]];
        } else if (numbers[ip] == 2) {
            val = numbers[numbers[ip + 1]] * numbers[numbers[ip + 2]];
        } else {
            cout << "Wrong command " << numbers[ip] << endl; 
        }
        numbers[numbers[ip + 3]] = val;
    }
}
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers;
    for (auto is : split(s, ',')) {
        numbers.push_back(stoll(is));
    }
    vector<ll> part1 = numbers;
    part1[1] = 12;
    part1[2] = 2;
    run_program(part1);
    cout << "Part 1 " << part1[0] << endl;
    bool found = false;
    for (ll val1 = 0; val1 <= 99 && !found; ++val1) {
        for (ll val2 = 0; val2 <= 99 && !found; ++val2) {
            vector<ll> temp = numbers;
            temp[1] = val1;
            temp[2] = val2;
            run_program(temp);
            if (temp[0] == 19690720) {
                cout << "Part 2 " << 100LL * val1 + val2 << endl;
                found = true; 
            }
        }
    }
    return 0;
}