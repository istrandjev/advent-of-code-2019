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

bool check(const vector<ll>& numbers, int x, int y) {
    Program program(numbers, {x, y});
    vector<ll> outputs;
    program.run_till_input_needed(outputs);
    return outputs.back();
}

pair<int, int> get_interval(const vector<ll>& numbers, int y) {
    int step = max(1, y / 15);
    int x = 0;
    while (!check(numbers, x, y)) {
        x += step;
    }
    int beg = 0;
    int end = x;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (check(numbers, mid, y)) {
            end = mid;
        } else {
            beg = mid;
        }
    }
    int minx = end;
    beg = x;
    end = y * 2;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (check(numbers, mid, y)) {
            beg = mid;
        } else {
            end = mid;
        }
    }
    int maxx = beg;
    return {minx, maxx};
}

bool works(const vector<ll>& numbers, int y) {
    auto interval1 = get_interval(numbers, y);
    auto interval2 = get_interval(numbers, y + 99);
    int fromx = max(interval1.first, interval2.first);
    int tox = min(interval1.second, interval2.second);
    return tox - fromx >= 99;
}
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers;
    for (auto is : split(s, ',')) {
        numbers.push_back(stoll(is));
    }

    vector<string> a(50, string(50, '.'));
    int res1 = 0;
    for (int x = 0; x < 50; ++x) {
        for (int y = 0; y < 50; ++y) {
            if (check(numbers, x, y)) a[x][y] = '#';
            res1 += check(numbers, x, y);
        }
    }
    
    cout << "Part 1 " << res1 << endl;
    int beg = 100, end = 50000;
    while (end - beg > 1) {
        int mid = (end + beg) / 2;
        if (works(numbers, mid)) {
            end = mid;
        } else {
            beg = mid;
        }
    }
    int y = end;
    int x = get_interval(numbers, end + 99).first;
    cout << "Part 2 " << x * 10000 + y << endl;
    return 0;
}