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

int moves[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

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
    vector<string> a;
    string current;
    for (auto c : outputs) {
        if (c == 10) {
            if (current.size()) {
                a.push_back(current);
            }
            current = "";
        } else {
            current.push_back(char(c));
        }
    }
    if (current.size()) {
        a.push_back(current);
    }
    
    int n = a.size();
    int m = a[0].size();
    int res1 = 0;
    int cx, cy;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '.') {
                continue;
            }
            if (a[i][j] != '#') {
                cy = i;
                cx = j;
            }
            int cnt = 0;
            for (int l = 0; l < 4; ++l) {
                int ty = i + moves[l][0];
                int tx = j + moves[l][1];
                if (ty < 0 || ty >= n || tx < 0 || tx >= m) {
                    continue;
                }
                cnt += (a[ty][tx] != '.');
            }
            if (cnt == 4) {
                res1 += i * j;
                a[i][j] = 'o';
            }
        }
    }

    cout << "Part 1 " << res1 << endl;

    int dir;
    switch (a[cy][cx]) {
        case '^': dir = 0; break;
        case '>': dir = 1; break;
        case 'v': dir = 2; break;
        case '<': dir = 3; break;
        default: cout << "Could not parse " << a[cy][cx] << endl; exit(1);
    }
    string solution;
    int clen = 0;
    int last_dir = dir;
    while (true) {
        a[cy][cx] = (a[cy][cx] == 'o' ? 'o' : '@');
        int ty = cy + moves[dir][0];
        int tx = cx + moves[dir][1];
        if (ty < 0 || ty >= n || tx < 0 || ty >= m || (a[ty][tx] != '#' && a[ty][tx] != 'o')) {
            if (clen) {
                if (solution.size()) {
                    solution.push_back(',');
                }
                solution += to_string(clen);
                clen = 0;
            }
            
            dir = (dir + 1) % 4;
            if (dir == last_dir) {
                break;
            }
            continue;
        }
        if (dir != last_dir && clen == 0) {
            if (dir == (last_dir + 1) % 4) {
                if (solution.size()) {
                    solution.push_back(',');
                }
                solution.push_back('R');
            } else if (dir == (last_dir + 3) % 4) {
                if (solution.size()) {
                    solution.push_back(',');
                }
                solution.push_back('L');
            } else {
                cout << "Uknown turn" << endl;
            }
        }
        last_dir = dir;
        cy = ty;
        cx = tx;
        clen++;
    }
    if (clen) {
        if (solution.size()) {
            solution.push_back(',');
        }
        solution += to_string(clen);
    }

    // I used solution to figure out the routines
    // cout << solution << endl;

    vector<string> routines{
        "C,C,A,B,A,B,A,B,C,B",
        "R,4,R,6,R,6,R,4,R,4",
        "L,8,R,6,L,10,L,10",
        "R,6,L,8,R,8"
    };
    numbers[0] = 2;
    vector<ll> inputs;
    for (auto routine : routines) {
        for (auto c : routine) {
            inputs.push_back(int(c));
        }
        inputs.push_back(10);
    }
    inputs.push_back(int('n'));
    inputs.push_back(10);
    Program program2(numbers, inputs);
    program2.run_till_input_needed(outputs);
    cout << "Part 2 " << outputs.back() << endl;
    return 0;
}