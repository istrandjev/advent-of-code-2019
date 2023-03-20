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

    ll assert_single_output() {
        vector<ll> outputs;
        run_till_input_needed(outputs);
        if (outputs.size() != 1) {
            cerr << "Expected 1 output got ";
            for (int i = 0; i < (int)outputs.size(); ++i) {
                printf("%lld%c", outputs[i], ((i + 1) != (int)outputs.size() ? ' ' : '\n'));
            }
            exit(1);
        }
        return outputs.back();
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
    Program program(numbers, {1});
    cout << "Part 1 " << program.assert_single_output() << endl;
    Program program2(numbers, {2});
    cout << "Part 2 " << program2.assert_single_output() << endl;
    return 0;
}