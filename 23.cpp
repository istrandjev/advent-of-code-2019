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

int main() {
    string s;
    getline(cin, s);
    auto numbers = Program::parse_numbers(s);
    vector<Program> computers;
    for (int i = 0; i < 50; ++i) {
        computers.emplace_back(numbers, vector<ll>{i});
    }
    ll res1 = -1;
    pair<ll, ll> nat_values;
    ll res2 = -1;
    while (true) {
        bool all_idle = true;
        for (int i = 0; i < 50; ++i) {
            vector<ll> outputs;
            if (computers[i].inputs.empty()) {
                computers[i].inputs.push(-1);
            } else {
                all_idle = false;
            }
            if (!computers[i].run_till_input_needed(outputs)) {
                continue;
            }
            for (int j = 0; j < (int)outputs.size(); j += 3) {
                if (outputs[j] == 255) {
                    if (res1 == -1) {
                        res1 = outputs[j + 2];
                    }
                    nat_values = {outputs[j + 1], outputs[j + 2]};
                } else {
                    for (int l = j + 1; l < j + 3; ++l) {
                        computers[outputs[j]].inputs.push(outputs[l]);
                    }
                }
            }
        }
        if (all_idle) {
            if (nat_values.second == res2) {
                break;
            }
            computers[0].inputs.push(nat_values.first);
            computers[0].inputs.push(nat_values.second);
            res2 = nat_values.second;
        }
    }
    cout << "Part 1 " << res1 << endl;
    cout << "Part 2 " << res2 << endl;
    return 0;
}