#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream f("./input.txt");

    vector<string> lines;

    while (f.is_open() && !f.eof()) {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    int sum = 0;

    for (auto line : lines) {
        int firstNum = 0;
        int lastNum = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] >= 48 && line[i] <= 57) {
                firstNum = line[i] - 48;
                break;
            }
        }
        for (int i = line.size() - 1; i >= 0; --i) {
            if (line[i] >= 48 && line[i] <= 57) {
                lastNum = line[i] - 48;
                break;
            }
        }
        sum += firstNum * 10 + lastNum;
    }

    cout << "Part1: " << sum << endl;

    string numbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    sum = 0;


    vector<string> linesOther;

    for (auto line : lines) {

    }

    for (auto line : lines) {
        int firstNum = 0;
        int firstIndex = line.size();
        int lastNum = 0;
        int lastIndex = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] >= 48 && line[i] <= 57) {
                firstNum = line[i] - 48;
                firstIndex = i;
                break;
            }
        }
        for (int i = 0; i < 10; ++i) {
            int n = line.find(numbers[i]);
            if (n == string::npos) continue;
            if (firstIndex > n) {
                firstNum = i;
                firstIndex = n;
            }
        }

        for (int i = line.size() - 1; i >= 0; --i) {
            if (line[i] >= 48 && line[i] <= 57) {
                lastNum = line[i] - 48;
                lastIndex = i;
                break;
            }
        }
        for (int i = 0; i < 10; ++i) {
            int n = line.rfind(numbers[i]);
            if (n == string::npos) continue;
            if (lastIndex < n) {
                lastNum = i;
                lastIndex = n;
            }
        }

        sum += firstNum * 10 + lastNum;
    }

    cout << "Part2: " << sum << endl;

    return 0;
}
