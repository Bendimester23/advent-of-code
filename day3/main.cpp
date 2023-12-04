//
// Created by bendi on 2023.12.03..
//
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

char symbols[] = {'*', '$', '=', '#', '%', '/', '&', '+', '-', '@'};

struct Rectangle {
    int line;
    int index;
    int lenght;
    int value;
    int starX;
    int starY;
};

struct StarPos {
    int x;
    int y;
};

int main() {
    ifstream f("./input.txt");

    vector<string> lines;

    while (f.is_open() && !f.eof()) {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    vector<Rectangle> searchRects;

    for (int i = 0; i < lines.size(); ++i) {
        int k = 0;
        while (k < lines[i].size()) {
            if (std::isdigit(lines[i][k])) {
                vector<char> buf;
                int idx = 0;
                while (k+idx < lines[i].size() && std::isdigit(lines[i][k+idx])) {
                    buf.emplace_back(lines[i][k+idx]);
                    idx++;
                }
                buf.emplace_back(0);
                auto rect = Rectangle {
                    i,
                    max(k-1, 0),
                    static_cast<int>(buf.size()) - 1 + (k == 0 ? 0 : 1) + (k+idx+1 >= lines[i].size() ? 0 : 1),
                    atoi(buf.data()),
                    -1,
                    -1,
                };
                searchRects.emplace_back(rect);
                k += idx;
            } else {
                k++;
            }
        }
    }

    int sum = 0;

    for (const auto &search_rect : searchRects) {
        if (search_rect.line > 0) {
            if (lines[search_rect.line - 1].substr(search_rect.index, search_rect.lenght).find_first_of("*$=#%/&+-@") != string::npos) {
                sum += search_rect.value;
                continue;
            }
        }
        if (lines[search_rect.line].substr(search_rect.index, search_rect.lenght).find_first_of("*$=#%/&+-@") != string::npos) {
            sum += search_rect.value;
            continue;
        }
        if (search_rect.line+1 < lines.size()) {
            if (lines[search_rect.line + 1].substr(search_rect.index, search_rect.lenght).find_first_of("*$=#%/&+-@") != string::npos) {
                sum += search_rect.value;
            }
        }
    }

    cout << "Part1: " << sum << endl;
    sum = 0;

    for (auto & [line, index, lenght, value, starX, starY] : searchRects) {
        if (line > 0) {
            if (int pos = static_cast<int>(lines[line - 1].substr(index, lenght).find_first_of('*')); pos != string::npos) {
                starX = index + pos;
                starY = line - 1;
                continue;
            }
        }
        if (int pos = static_cast<int>(lines[line].substr(index, lenght).find_first_of('*')); pos != string::npos) {
            starX = index + pos;
            starY = line;
            continue;
        }
        if (line+1 < lines.size()) {
            if (int pos = static_cast<int>(lines[line + 1].substr(index, lenght).find_first_of('*')); pos != string::npos) {
                starX = index + pos;
                starY = line + 1;
            }
        }
    }

    vector<StarPos> invalid;

    for (auto & [line, index, lenght, value, starX, starY] : searchRects) {
        if (starX != -1 && starY != -1) {
            for (auto [x, y] : invalid) {
                if (starX == x && starY == y) goto end;
            }
            for (auto &otherRect : searchRects) {
                if (line == otherRect.line && index == otherRect.index) continue;
                for (auto [x, y] : invalid) {
                    if (starX == x && starY == y) goto end;
                }
                if (starX == otherRect.starX && starY == otherRect.starY) {
                    //This is needed to not count them twice
                    auto pos = StarPos{
                        starX,
                        starY
                    };
                    invalid.emplace_back(pos);
                    sum += value * otherRect.value;
                    break;
                }
            }
        }
        end:
    }

    cout << "Part2: " << sum << endl;

    return 0;
}