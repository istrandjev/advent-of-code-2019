#ifndef __INTCODE_H
#define __INTCODE_H

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <unordered_map>

// vector<string> split(const string& s, char delim=' ') {
//     vector<string> res;
//     string cur;
//     for (auto c : s) {
//         if (c == delim) {
//             res.push_back(cur);
//             cur = "";
//         } else {
//             cur.push_back(c);
//         }
//     }
//     if (s.back() != delim) {
//         res.push_back(cur);
//     }
//     return res;
// }

struct Program {
    Program(const std::vector<long long> original_numbers, const std::vector<long long>& original_inputs) : ip(0), relative_base(0) {
        for (int i = 0; i < (int)original_numbers.size(); ++i) {
            numbers[i] = original_numbers[i];
        }
        for (auto iv : original_inputs) {
            inputs.push(iv);
        }
    }
    static std::vector<long long> parse_numbers(const std::string& line) {
        std::vector<long long> result;
        std::string cur = "";
        for (auto c : line) {
            if (c == ',') {
                result.push_back(stoll(cur));
                cur = "";
            } else {
                cur.push_back(c);
            }
        }
        result.push_back(stoll(cur));
        return result;
    }

    int get_opcode(int idx) {
        long long val = numbers[ip];
        for (int i = 0; i < 1 + idx; ++i) {
            val /= 10;
        }
        return val % 10;
    }

    long long get_value(int idx) {
        int opcode = get_opcode(idx);
        if (opcode == 1) {
            return numbers[ip + idx];
        }
        long long offset = (opcode == 2 ? relative_base : 0);
        return numbers[offset + numbers[ip + idx]];
    }

    void set_value(long long idx, long long value) {
        int opcode = get_opcode(idx);
        long long offset = 0;
        if (opcode == 1) {
            std::cout << "Setting an absolute value!" << std::endl;
            exit(1);
        } else if (opcode == 2) {
            offset = relative_base;
        } 
        numbers[offset + numbers[ip + idx]] = value;
    }
    bool run_till_input_needed(std::vector<long long>& outputs) {
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
                    std::cout << "Wrong command " << numbers[ip] << std::endl;
                    exit(1);
            }
        }
        return false;
    }

    long long get_output() {
        std::vector<long long> outputs;
        run_till_input_needed(outputs);
        return outputs.back();
    }

    long long ip;
    long long relative_base;
    std::queue<long long> inputs;
    std::unordered_map<long long, long long> numbers;
};

#endif