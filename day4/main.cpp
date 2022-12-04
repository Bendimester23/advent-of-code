#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct range {
    int start;
    int end;

    static range parse(string raw) {
        int splitIdx = raw.find_first_of("-");

        auto first = raw.substr(0, splitIdx);
        auto second = raw.substr(splitIdx+1, raw.size()-splitIdx-1);

        return range {atoi(first.data()), atoi(second.data())};
    }

    string toString() {
        return to_string(start).append("-").append(to_string(end));
    }

    bool fullyContains(const range &other) {
        return other.start >= start && other.end <= end;
    }

    bool overlaps(const range &other) {
        return (other.start <= end && other.end >= start) || (other.end >= start  && other.start <= end);
    }
};

int main()
{
    ifstream f("./input.txt");

    if (!f.is_open()) return 1;
    
    vector<string> lines;

    while (f.is_open() && !f.eof())
    {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    int part1 = 0;
    int part2 = 0;

    for (auto &e : lines) {
        auto idx = e.find_first_of(",");
        auto rA = range::parse(e.substr(0, idx));
        auto rB = range::parse(e.substr(idx+1, e.size() - idx - 1));

        part1 += rA.fullyContains(rB) || rB.fullyContains(rA);
        part2 += rA.overlaps(rB);
    }

    cout << "Part 1: " << to_string(part1) << endl;
    cout << "Part 2: " << to_string(part2) << endl;

    return 0;
}
