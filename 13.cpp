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
    vector<ll> numbers = Program::parse_numbers(s);
    Program program(numbers, {});
    vector<ll> outputs;
    program.run_till_input_needed(outputs);
    int res1 = 0;
    for (int i = 2; i < (int)outputs.size(); i += 3) {
        res1 += (outputs[i] == 2);
    }
    cout << "Part 1 " << res1 << endl;
    numbers[0] = 2;
    Program program2(numbers, {});
    int res2 = 0;
    int bx = -1, by = -2;
    int bdx = 0, bdy = 0;
    int px = -2, py;
    for (int step = 0;program2.run_till_input_needed(outputs); step++) {
        for (int i = 0; i < (int)outputs.size(); i += 3) {
            if (outputs[i] == -1 && outputs[i + 1] == 0) {
                res2 = outputs[i + 2];
                continue;
            }
            char current;
            switch(outputs[i + 2]) {
                case 0: current = ' '; break;
                case 1: current = '#'; break;
                case 2: current = '*'; break;
                case 3: current = '-'; break;
                case 4: current = 'o'; break;
            }
            if (current == 'o') {
                if (bx != -1) {
                    bdx = outputs[i] - bx;
                    bdy = outputs[i + 1] - by;
                }
                bx = outputs[i];
                by = outputs[i + 1];
            }
            if (current == '-') {
                px = outputs[i];
                py = outputs[i + 1];
            }
        }
        if (by == py - 1 && px == bx) {
            program2.inputs.push(0);
        } else if (bx + bdx > px) {
            program2.inputs.push(1);
        } else if (bx + bdx < px) {
            program2.inputs.push(-1);
        } else {
            program2.inputs.push(0);
        }
    }

    for (int i = 0; i < (int)outputs.size(); i += 3) {
        if (outputs[i] == -1 && outputs[i + 1] == 0) {
            res2 = outputs[i + 2];
            continue;
        }
    }
    cout << "Part 2 " << res2 << endl;
    return 0;
}