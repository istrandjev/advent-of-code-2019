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
    cout << "Part 1 " << Program(numbers, {1}).get_output() << endl;
    cout << "Part 2 " << Program(numbers, {5}).get_output() << endl;

    return 0;
}