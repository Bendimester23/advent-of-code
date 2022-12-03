#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream f("./input.txt");

    vector<string> lines;

    while (f.is_open() && !f.eof()) {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    vector<int> elves;
    elves.emplace_back(0);

    for (auto &e : lines) {
        if (e == "") {
            elves.emplace_back(0);
            continue;
        }
        elves[elves.size() - 1] += atoi(e.data());
    }

    int max = elves[0];

    for (auto &e : elves) {
        if (e > max) max = e;
    }

    cout << "Part 1: " << to_string(max) << endl;

    int top[3];

    for (auto &e : elves) {
        if (e > top[0]) {
            top[2] = top[1];
            top[1] = top[0];
            top[0] = e;
            continue;
        }
        if (e > top[1]) {
            top[2] = top[1];
            top[1] = e;
            continue;
        }
        if (e > top[2]) {
            top[2] = e;
        }
    }

    cout << "Part 2: " << to_string(top[0] + top[1] + top[2]) << endl;

    return 0;
}
