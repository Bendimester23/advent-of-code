//
// Created by bendi on 2023.12.02..
//
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

int max_red = 12;
int max_green = 13;
int max_blue = 14;

struct Round {
    int red;
    int green;
    int blue;
};

vector<Round> parse_rounds(const vector<string>&raw) {
    vector<Round> res;
    res.reserve(raw.size());
    for (auto roundText : raw) {
        vector<string> colorsText;
        boost::trim(roundText);
        split(colorsText, roundText, boost::is_any_of(","));
        Round round{};
        for (auto color : colorsText) {
            boost::trim(color);
            vector<string> parts;
            split(parts, color, boost::is_any_of(" "));
            if (parts[1] == "blue") {
                round.blue = atoi(parts[0].c_str());
            } else if (parts[1] == "red") {
                round.red = atoi(parts[0].c_str());
            } else if (parts[1] == "green") {
                round.green = atoi(parts[0].c_str());
            }
        }
        res.emplace_back(round);
    }
    return res;
}

struct Game {
    int id;
    vector<Round> rounds;
};

bool is_game_valid(Game g) {
    return all_of(g.rounds.begin(), g.rounds.end(), [](const Round r) {
        if (r.red > max_red) return false;
        if (r.green > max_green) return false;
        if (r.blue > max_blue) return false;
        return true;
    });
}

int minimum_power_of_game(const Game &g) {
    int mRed = 0;
    int mGreen = 0;
    int mBlue = 0;
    for (const auto [red, green, blue] : g.rounds) {
        if (red > mRed) mRed = red;
        if (green > mGreen) mGreen = green;
        if (blue > mBlue) mBlue = blue;
    }
    return mRed * mGreen * mBlue;
}

int main() {
    ifstream f("./input.txt");

    vector<string> lines;

    while (f.is_open() && !f.eof()) {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    vector<Game> games;
    games.reserve(lines.size());

    for (const auto &line : lines) {
        int gameId = atoi(line.substr(5, line.find_first_of(":")-5).c_str());
        string roundsText = line.substr(line.find_first_of(":")+2);
        vector<string> roundsRaw;
        split(roundsRaw, roundsText, boost::is_any_of(";"));
        auto game = Game {
            gameId,
            parse_rounds(roundsRaw)
        };
        games.emplace_back(game);
    }
    int sum = 0;
    for (const auto &g : games) {
        if (is_game_valid(g)) sum += g.id;
    }
    cout << "Part1: " << sum << endl;
    sum = 0;
    for (const auto &g : games) {
        sum += minimum_power_of_game(g);
    }
    cout << "Part2: " << sum << endl;
    return 0;
}
