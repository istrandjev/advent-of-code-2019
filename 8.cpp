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

int main() {
    int width = 25, height = 6;
    string s;
    getline(cin, s);
    int num_layers = s.size() / (width * height);
    int layer_size = width * height;
    vector<vector<string> > layers;
    for (int i = 0; i < num_layers; ++i) {
        int start = i * layer_size;
        vector<string> layer;
        for (int j = 0; j < height; ++j) {
            layer.push_back(s.substr(start + j * width, width));
        }
        layers.push_back(layer);
    }
    int best = 100000000;
    int res1 = 0;
    cout << layers[0].size() << endl;
    for (auto l : layers) {
        int digits[10] = {0};
        for (auto r: l) {
            for (auto c : r) {
                digits[c - '0']++;
            }
        }
        if (digits[0] < best) {
            best = digits[0];
            res1 = digits[2] * digits[1];
        }
    }
    cout << "Part 1 " << res1 << endl;

    vector<string> result(height, string(width, '@'));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            for (auto l : layers) {
                if (l[i][j] != '2') {
                    result[i][j] = (l[i][j] == '0' ? ' ' : '#');
                    break;
                }
            }
        }
    }
    for (auto l : result) {
        cout << l << endl;
    }
    return 0;
}