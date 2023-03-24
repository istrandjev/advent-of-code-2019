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

struct Program {
    Program(const vector<ll> original_numbers, const vector<ll>& original_inputs) : ip(0), relative_base(0) {
        for (int i = 0; i < (int)original_numbers.size(); ++i) {
            numbers[i] = original_numbers[i];
        }
        for (auto iv : original_inputs) {
            inputs.push(iv);
        }
    }

    int get_opcode(int idx) {
        ll val = numbers[ip];
        for (int i = 0; i < 1 + idx; ++i) {
            val /= 10;
        }
        return val % 10;
    }

    ll get_value(int idx) {
        int opcode = get_opcode(idx);
        if (opcode == 1) {
            return numbers[ip + idx];
        }
        ll offset = (opcode == 2 ? relative_base : 0);
        return numbers[offset + numbers[ip + idx]];
    }

    void set_value(ll idx, ll value) {
        int opcode = get_opcode(idx);
        ll offset = 0;
        if (opcode == 1) {
            cout << "Setting an absolute value!" << endl;
            exit(1);
        } else if (opcode == 2) {
            offset = relative_base;
        } 
        numbers[offset + numbers[ip + idx]] = value;
    }
    bool run_till_input_needed(vector<ll>& outputs) {
        outputs.clear();
        while (true) {
            switch (numbers[ip] % 100) {
                case 1:
                    set_value(3, get_value(1) + get_value(2));
                    ip += 4;
                    break;
                case 2:
                    set_value(3, get_value(1) * get_value(2));
                    ip += 4;
                    break;
                case 3:
                    if (inputs.empty()) {
                        return true;
                    } else {
                        set_value(1, inputs.front());
                        inputs.pop();
                        ip += 2;
                        break;
                    }
                case 4:
                    outputs.push_back(get_value(1));
                    ip += 2;
                    break;
                case 5:
                    ip = (get_value(1) != 0 ? get_value(2) : ip + 3);
                    break;
                case 6:
                    ip = (get_value(1) == 0 ? get_value(2) : ip + 3);
                    break;
                case 7:
                    set_value(3, int(get_value(1) < get_value(2)));
                    ip += 4;
                    break;
                case 8:
                    set_value(3, int(get_value(1) == get_value(2)));
                    ip += 4;
                    break;
                case 9:
                    relative_base += get_value(1);
                    ip += 2;
                    break;
                case 99:
                    return false;
                default:
                    cout << "Wrong command " << numbers[ip] << endl;
                    exit(1);
            }
        }
        return false;
    }

    ll ip;
    ll relative_base;
    queue<ll> inputs;
    unordered_map<ll, ll> numbers;
};


int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers;
    for (auto is : split(s, ',')) {
        numbers.push_back(stoll(is));
    }
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