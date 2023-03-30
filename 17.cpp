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

int main() {
    string s;
    getline(cin, s);
    vector<ll> numbers = Program::parse_numbers(s);

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
    cout << "Part 2 " << Program(numbers, inputs).get_output() << endl;
    return 0;
}