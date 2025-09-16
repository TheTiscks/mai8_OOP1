#include <iostream>
#include <string>
#include <sstream>
#include "closest_pair.h"

using namespace std;

bool isValidInput(const string& input, int& number) {
    if (input.empty()) {
        return false;
    }
    for (char c : input) {
        if (!isdigit(c)) { // строка - только цифры?
            return false;
        }
    }
    stringstream ss(input); // в число
    ss >> number;
    return number > 0;
}

int main() {
    string input;
    while (getline(cin, input)) {
        size_t start = input.find_first_not_of(" \t"); // убираем пробелы
        size_t end = input.find_last_not_of(" \t");
        if (start != string::npos) {
            input = input.substr(start, end - start + 1);
        } else {
            input = "";
        }
        if (input.empty()) {
            continue;
        }
        int upper_limit;
        if (isValidInput(input, upper_limit)) {
            auto result = closest_pair_tonum(upper_limit);
            if (result.first == -1 && result.second == -1) {
                cout << "No solution" << endl;
            } else {
                cout << result.first << " " << result.second << endl;
            }
        } else {
            cout << "Error: invalid input" << endl;
        }
    }
    return 0;
}