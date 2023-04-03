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

enum ShuffleType {
    DEAL = 1,
    CUT = 2,
    SKIP = 3
};
ll total_cards;

ll save_mul(ll x, ll y) {
    ll res = 0;
    ll c = x;
    while (y) {
        if (y % 2) {
            res = (res + c) % total_cards;
        }
        y /= 2;
        c = (c + c) % total_cards;
    }
    return res;
}
ll stepen(ll x, ll y) {
    ll res = 1;
    ll p = x;
    while (y) {
        if (y % 2) {
            res = save_mul(res, p);
        }
        p = save_mul(p, p);
        y /= 2;
    }
    return res;
}

ll rev(ll x) {
    // or phi(total_cards) - 1 if total_cards is not prime
    return stepen(x, total_cards - 2);
}

pair<ll, ll> reverse_shuffle(ShuffleType shuffle_type, ll amount, const pair<ll, ll>& coefs) {
    if (shuffle_type == ShuffleType::DEAL) {
        return {save_mul(total_cards - 1, coefs.first), (save_mul(total_cards - 1, coefs.second) + total_cards - 1LL) %total_cards };
    } else if (shuffle_type == ShuffleType::CUT) {
        if (amount < 0) {
            amount = total_cards + amount;
        }
        return {coefs.first, (coefs.second + amount) % total_cards};
    } else if (shuffle_type == ShuffleType::SKIP) {
        ll rev_amount = rev(amount);
        return {save_mul(coefs.first, rev_amount), save_mul(coefs.second, rev_amount)};
    }
    throw "Uknown shuffle type";
}

ll reverse_shuffles(ll index, const vector<pair<ShuffleType, ll> >& moves, ll times) {
    pair<ll, ll> coefs(1, 0);
    for (int i = (int)moves.size() - 1; i >= 0; --i) {
        coefs = reverse_shuffle(moves[i].first, moves[i].second, coefs);
    }
    ll an = stepen(coefs.first, times);
    ll res = save_mul(index, an);
    ll temp = save_mul(an + total_cards - 1, rev(coefs.first + total_cards - 1));
    temp = save_mul(temp, coefs.second);
    return (temp + res) % total_cards;
}

int main() {
    const string deal = "deal into new stack";
    regex cut("cut (-?\\d+)");
    regex skip_deal("deal with increment (\\d+)");
    smatch match;
    string s;
    vector<pair<ShuffleType, ll> > moves;
    while (getline(cin, s)) {
        if (s == deal) {
            moves.push_back({ShuffleType::DEAL, 0});
        } else if (regex_match(s, match, cut)) {
            ll amount = stoll(match.str(1));
            moves.push_back({ShuffleType::CUT, amount});
        } else if (regex_match(s, match, skip_deal)) {
            ll skip = stoll(match.str(1));
            moves.push_back({ShuffleType::SKIP, skip});
        } else {
            cout << "Could not parse shuffle " << s << endl;
            exit(1);
        }
    }
    total_cards = 10007;
    for (int i = 0; i < total_cards; ++i) {
        if (reverse_shuffles(i, moves, 1) == 2019) {
            cout << "Part 1 " << i << endl;
            break;
        }
    }

    total_cards = 119315717514047LL;
    ll index = 2020;
    cout << "Part 2 " << reverse_shuffles(index, moves, 101741582076661LL) << endl;
    return 0;
}