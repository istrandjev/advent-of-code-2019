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

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

map<pair<int, int>, int> move_robot(Program& program) {
    map<pair<int, int>, int> used;
    vector<ll> outputs;
    int dir = 0;
    pair<int, int> c(0, 0);
    while (program.run_till_input_needed(outputs)) {
        if (outputs.size() != 2) {
            cout << "Got wrong number of outputs" << endl;
            exit(1);
        }
        used[c] = outputs[0];
        int dir_step = (outputs.back() == 0 ? 3 : 1);
        dir = (dir + dir_step) % 4;
        c.first += moves[dir][0];
        c.second += moves[dir][1];
        auto it = used.find(c);
        if (it == used.end() || it->second == 0) {
            program.inputs.push(0);
        } else {
            program.inputs.push(1);
        }
    }
    return used;
}
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers = Program::parse_numbers(s);
    Program program(numbers, {0});

   
    cout << "Part 1 " << move_robot(program).size() << endl;
    Program program2(numbers, {1});
    auto used = move_robot(program2);
    vector<string> screen(30, string(100, '.'));
    for (auto it : used) {
        if (it.second) {
            screen[it.first.first + 15][it.first.second + 50] = '#';
        }
    }  
    cout << "Part 2" << endl;
    for (auto l : screen) {
        cout << l << endl;
    }
    return 0;
}