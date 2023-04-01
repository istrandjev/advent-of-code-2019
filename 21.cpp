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

vector<ll> get_ascii(const vector<string>& instructions) {
    vector<ll> result;
    for (auto l : instructions) {
        for (auto c : l) {
            result.push_back((ll)c);
        }
        result.push_back(10);
    }
    return result;
}

ll run_spring_droid(const vector<string>& instructions, const vector<ll>& numbers) {
    auto inputs = get_ascii(instructions);
    Program program(numbers, inputs);
    vector<ll> outputs;
    program.run_till_input_needed(outputs);
    if (outputs.back() > 300) {
        return outputs.back();
    }else {
        string res;
        for (auto o : outputs) {
            res.push_back((char)o);
        }
        cout << res << endl;
        return -1;
    }
}

int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers = Program::parse_numbers(s);
    vector<string> instructions{"NOT A J", "NOT B T", "OR T J", "NOT C T", "OR T J", "AND D J", "WALK"};
    cout << "Part 1 " << run_spring_droid(instructions, numbers) << endl;
    instructions.pop_back();
    instructions.push_back("AND D T");
    instructions.push_back("AND E T");
    instructions.push_back("OR H T");
    instructions.push_back("AND T J");
    instructions.push_back("RUN");
    cout << "Part 2 " << run_spring_droid(instructions, numbers) << endl;

    return 0;
}