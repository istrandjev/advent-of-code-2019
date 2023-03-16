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

int run_program(const vector<ll>& original_numbers, int input_value) {
    auto numbers = original_numbers;
    int ip = 0;
    int last_output;
    for (int ip = 0; numbers[ip] != 99;) {
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
                numbers[numbers[ip + 1]] = input_value;
                ip += 2;
                break;
            case 4:
                last_output = numbers[numbers[ip + 1]];
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
            default:
                cout << "Wrong command " << numbers[ip] << endl;
                exit(1);
        }
    }
    return last_output;
}


int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers;
    for (auto is : split(s, ',')) {
        numbers.push_back(stoll(is));
    }
    cout << "Part 1 " << run_program(numbers, 1) << endl;
    cout << "Part 2 " << run_program(numbers, 5) << endl;

    return 0;
}