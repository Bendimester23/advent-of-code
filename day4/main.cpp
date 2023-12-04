//
// Created by bendi on 2023.12.04..
//
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <regex>

using namespace std;

static std::regex rgx("\\s+");

struct Card {
    int id;
    vector<int> winning;
    vector<int> yours;
    int count;
};

vector<int> split_to_ints(string in) {
    vector<int> res{};
    std::sregex_token_iterator iter(in.begin(),
                                        in.end(),
                                        rgx,
                                        -1);
    std::sregex_token_iterator end;
    for (; iter != end; ++iter)
        res.emplace_back(atoi(iter->str().c_str()));
    return res;
}

int main() {
    ifstream f("./input.txt");

    vector<string> lines;

    while (f.is_open() && !f.eof()) {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    vector<Card> cards;
    cards.reserve(lines.size());

    regex pattern{R"(Card\s*(\d+):\s+((\d+\s+)+)\|((\s+\d+)+))"};

    for (const auto& line : lines) {
        if (smatch results; regex_match(line, results, pattern)) {
            auto id = atoi(results[1].str().c_str());
            auto winning = results[2].str();
            auto your = results[4].str();
            boost::trim(winning);
            boost::trim(your);
            auto card = Card{
                id,
                split_to_ints(winning),
                split_to_ints(your),
                1
            };
            cards.emplace_back(card);
        }
    }

    int sum = 0;

    for (const auto& card : cards) {
        int worth = 0;
        for (int winning : card.winning) {
            for (int your : card.yours) {
                if (winning == your) {
                    if (worth == 0) worth = 1;
                    else worth *= 2;
                    break;
                }
            }
        }
        sum += worth;
    }

    cout << "Part 1: " << sum << endl;
    sum = 0;

    int idx = 0;
    for (const auto & card : cards) {
        int matches = 0;
        for (int winning : card.winning) {
            for (int your : card.yours) {
                if (winning == your) {
                    matches++;
                    break;
                }
            }
        }
        for (int k = 0; k < card.count; ++k) {
            for (int i = 0; i < matches; ++i) {
                cards[idx+i+1].count++;
            }
        }
        sum += card.count;
        idx++;
    }
    cout << "Part 2: " << sum << endl;

    return 0;
}
