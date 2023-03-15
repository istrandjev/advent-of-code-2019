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

bool is_valid(int v, bool check_len=false) {
    if (v < 100000 || v >= 1000000) {
        return false;
    }
    vector<int> digits;
    while (v) {
        if (digits.size() && digits.back() < v % 10) {
            return false;
        }
        digits.push_back(v % 10);
        v /= 10;
    }
    int min_repeated = 0;
    for (int i = 0; i < (int)digits.size(); ++i) {
        int cnt = 1;
        while (i + 1 < (int)digits.size() && digits[i + 1] == digits[i]) {
            i++;
            cnt++;
        }
    
        if (cnt >  1 && (min_repeated == 0 || cnt < min_repeated)) {
            min_repeated = cnt;
        }
    }
    
    return check_len ? min_repeated == 2 : min_repeated != 0;
}

int main() {
    int from, to;
    scanf("%d-%d", &from, &to);
    int res1 = 0;
    int res2 = 0;
    for (int i = from;i <= to; ++i) {
        res1 += is_valid(i);
        res2 += is_valid(i, true);
    }
    cout << "Part 1 " << res1 << endl;
    cout << "Part 2 " << res2 << endl;
    return 0;
}