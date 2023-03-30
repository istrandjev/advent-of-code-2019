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
    vector<ll> outputs;
    Program program(numbers, {1});
    program.run_till_input_needed(outputs);
    cout << "Part 1 " << outputs.back() << endl;
    Program program2(numbers, {2});
    program2.run_till_input_needed(outputs);
    cout << "Part 2 " << outputs.back() << endl;
    return 0;
}