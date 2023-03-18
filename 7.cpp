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

int get_value(vector<ll>& numbers, int ip, int idx) {
    int val = numbers[ip];
    for (int i = 0; i < 1 + idx; ++i) {
        val /= 10;
    }
    if (val % 10 == 1) {
        return numbers[ip + idx];
    } else {
        return numbers[numbers[ip + idx]];
    }
}

struct Amplifier {
    Amplifier(const vector<ll> original_numbers, const queue<ll>& original_inputs) : numbers(original_numbers), inputs(original_inputs), ip(0) {}
    vector<ll> numbers;
    queue<ll> inputs;
    int ip;
    bool run_till_input_needed(vector<ll>& outputs) {
        outputs.clear();
        for (; numbers[ip] != 99;) {
            switch (numbers[ip] % 100) {
                case 1:
                    numbers[numbers[ip + 3]] = get_value(numbers, ip, 1) + get_value(numbers, ip, 2);
                    ip += 4;
                    break;
                case 2:
                    numbers[numbers[ip + 3]] = get_value(numbers, ip, 1) * get_value(numbers, ip, 2);
                    ip += 4;
                    break;
                case 3:
                    if (inputs.empty()) {
                        return true;
                    } else {
                        numbers[numbers[ip + 1]] = inputs.front();
                        inputs.pop();
                        ip += 2;
                        break;
                    }
                case 4:
                    outputs.push_back(numbers[numbers[ip + 1]]);
                    ip += 2;
                    break;
                case 5:
                    ip = (get_value(numbers, ip, 1) != 0 ? get_value(numbers, ip, 2) : ip + 3);
                    break;
                case 6:
                    ip = (get_value(numbers, ip, 1) == 0 ? get_value(numbers, ip, 2) : ip + 3);
                    break;
                case 7:
                    numbers[numbers[ip + 3]] = int(get_value(numbers, ip, 1) < get_value(numbers, ip, 2));
                    ip += 4;
                    break;
                case 8:
                    numbers[numbers[ip + 3]] = int(get_value(numbers, ip, 1) == get_value(numbers, ip, 2));
                    ip += 4;
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
};
int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers;
    for (auto is : split(s, ',')) {
        numbers.push_back(stoll(is));
    }

    vector<int> phase_seq(5);
    iota(all(phase_seq), 0);
    ll res1 = 0;
    do {
        vector<Amplifier> amps;
        for (auto ps : phase_seq) {
            queue<ll> q;
            q.push(ps);
            amps.push_back({numbers, q});
        }
        ll prev = 0;
        for (int i = 0; i < 5; ++i) {
            amps[i].inputs.push(prev);
            vector<ll> outputs;
            amps[i].run_till_input_needed(outputs);
            prev = outputs.back();
        }
        res1 = max(res1, prev);
    } while (next_permutation(all(phase_seq)));
    cout << "Part 1 " << res1 << endl;
    iota(all(phase_seq), 5);
    ll res2 = 0;
    do {
        vector<Amplifier> amps;
        queue<ll> q;
        q.push(phase_seq[0]);
        q.push(0);
        amps.push_back(Amplifier{numbers, q});
        for (int i = 1; i < 5; ++i) {
            queue<ll> tq;
            tq.push(phase_seq[i]);
            amps.push_back(Amplifier{numbers, tq});
        }
        int idx = 0;
        while (true) {
            vector<ll> outputs;
            bool has_more = amps[idx].run_till_input_needed(outputs);
            for (auto o : outputs) {
                amps[(idx + 1) % amps.size()].inputs.push(o);
            }
            if (!has_more && idx == 4) {
                res2 = max(res2, outputs.back());
                break;
            }
            idx = (idx + 1) % amps.size();
        }
    } while (next_permutation(all(phase_seq)));
    cout << "Part 2 " << res2 << endl;
    return 0;
}