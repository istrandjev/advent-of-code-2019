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

string run_with_command(const string& command, Program& program) {
    if (command.size()) {
        for (auto c : command) {
            program.inputs.push((ll)c);
        }
        program.inputs.push(10);
    }
    vector<ll> outputs;
    program.run_till_input_needed(outputs);
    string res;
    for (auto o : outputs) {
        res.push_back((char)o);
    }
    return res;
}

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

vector<string> get_by_section(const string& section_title, Program& program) {
    string temp = run_with_command("inv", program);
    regex directions(section_title + "((\n- .*)+)");
    smatch match;
    regex_search(temp, match, directions);
    vector<string> result;
    for (auto d : split(match.str(1).substr(1), '\n')) {
        result.push_back(d.substr(2));
    }
    return result;
}
vector<string> get_directions(Program& program) {
    return get_by_section("Doors here lead:", program);
}

vector<string> get_items(Program& program) {
    return get_by_section("Items in your inventory:", program);
}

int main() {
    string s;
    getline(cin, s);
    auto numbers = Program::parse_numbers(s);
    Program program(numbers, {});

    auto do_step = [&](const string& command) {
        cout << run_with_command(command, program) << endl;
    };
    do_step("north");
    do_step("take weather machine");
    do_step("north");
    do_step("take klein bottle");
    do_step("east");
    do_step("take spool of cat6");
    do_step("east");
    do_step("east");
    do_step("south");
    do_step("take mug");
    do_step("north");
    do_step("north");
    do_step("east");
    do_step("north");
    do_step("north");
    do_step("take tambourine");
    do_step("south");
    do_step("south");
    do_step("south");
    do_step("take shell");
    do_step("north");
    do_step("west");
    do_step("south");
    do_step("west");
    do_step("west");
    do_step("south");
    do_step("south");
    do_step("east");
    do_step("take antenna");
    do_step("west");
    do_step("north");
    do_step("north");
    do_step("east");
    do_step("south");
    do_step("south");

    vector<string> items = get_items(program);
    for (int mask = 0; mask < (1 << items.size()); ++mask) {
        for (int i = 0; i < (int)items.size(); ++i) {
            if (!(mask & (1 << i))) {
                run_with_command("drop " + items[i], program);
            }
        }
        string res = run_with_command("east", program);

        if (res.find("and you are ejected back to the checkpoint.") == string::npos) {
            cout << "Success!" << endl;
            cout << res << endl;
            break;
        }
        for (int i = 0; i < (int)items.size(); ++i) {
            if (!(mask & (1 << i))) {
                run_with_command("take " + items[i], program);
            }
        }

    }

    return 0;
}