#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    ifstream f("./input.txt");

    if (!f.is_open())
        return 1;

    vector<string> lines;

    while (!f.eof())
    {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    int ip = 0;
    int cycle = 1;

    char addCounter = 0;

    int rX = 1;

    int strength = 0;

    char screen[6][40];

    for (size_t i = 0; i < 6; i++)
    {
        for (size_t k = 0; k < 40; k++)
        {
            screen[i][k] = 0;
        }
    }

    do {
        auto instruction = lines[ip];

        if ((cycle - 20) % 40 == 0 && cycle < 221) {
            strength += cycle * rX;
        }

        int currPx = cycle % 40;
        int idx = currPx - 1;

        auto dst = rX - (currPx - 1);

        screen[(cycle - 1)/40][idx] = dst;

        if (instruction == "noop") {
            ip++;
            cycle++;
        } else {
            auto x = stoi(instruction.substr(5));

            if (addCounter < 1) {
                cycle++;
                addCounter++;
            } else if (addCounter == 1) {
                cycle++;
                ip++;
                addCounter = 0;

                rX += x;
            }
        }

    } while (ip < lines.size());

    cout << "Part 1: " << strength << endl;
    cout << "----------------[Part 2]----------------" << endl;

    for (auto &e : screen) {
        for (auto &f : e) {
            if (abs(f) < 2) {
                cout << '#';
            } else {
                cout << '.';
            }
        }
        cout << endl;
    }

    return 0;
}
