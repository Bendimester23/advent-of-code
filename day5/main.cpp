#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct operation {
    int count;
    int from;
    int to;

    static operation parse(string raw) {
        auto tmp = raw.substr(5, raw.size()-5);
        int count = stoi(raw.substr(5, raw.size()-1-tmp.find_first_of(' ')));

        int begin = to_string(count).size() + 6;
        tmp = tmp.substr(begin, tmp.size()-begin);

        int from = stoi(tmp.substr(0, tmp.find_first_of(' ')));

        int to = stoi(tmp.substr(tmp.find_last_of(' '), tmp.size()-tmp.find_last_of(' ')));

        return operation{count, from, to};
    }

    void execute(vector<vector<char>> *stacks) {
        for (size_t i = 0; i < count; i++)
        {
            auto fromStack = (*stacks)[from-1];
            (*stacks)[to-1].emplace_back(fromStack[fromStack.size()-1]);
            (*stacks)[from-1].pop_back();
        }
    }

    void execute9001(vector<vector<char>> *stacks) {
        auto fromStack = (*stacks)[from-1];
        
        for (size_t i = 0; i < count; i++)
        {
            (*stacks)[to-1].emplace_back(fromStack[fromStack.size()-count+i]);
        }

        for (size_t i = 0; i < count; i++)
        {
            (*stacks)[from-1].pop_back();
        }
        
    }
};

int main()
{
    ifstream f("./input.txt");

    if (!f.is_open())
        return 1;

    vector<string> lines;

    while (f.is_open() && !f.eof())
    {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    int numCols = 0;

    int numRows = 1;

    for (auto &e : lines)
    {
        if (e.substr(0, 2) == " 1")
        {
            auto idx = e.find_last_of(' ');
            auto lastStartIdx = e.substr(0, e.size() - 1).find_last_of(' ');

            numCols = stoi(e.substr(lastStartIdx+1, idx-lastStartIdx-1));
            break;
        }
        numRows++;
    }

    vector<vector<char>> stacks;
    vector<vector<char>> stacks2;

    for (size_t i = 0; i < numCols; i++)
    {
        stacks.emplace_back(vector<char>());
    }
    

    for (size_t i = numRows - 1; i > 0; i--)
    {
        auto e = lines[i-1];
        for (size_t k = 0; k < numCols; k++)
        {
            if (e[k*4+1] != ' ') stacks[k].emplace_back(e[k*4+1]);
        }
    }

    for (auto &e : stacks) {
        stacks2.emplace_back(e);
    }

    for (size_t i = numRows+1; i < lines.size(); i++)
    {
        operation::parse(lines[i]).execute(&stacks);
    }

    for (size_t i = numRows+1; i < lines.size(); i++)
    {
        operation::parse(lines[i]).execute9001(&stacks2);
    }

    cout << "Part 1: ";
    for (auto &e : stacks) {
        cout << e[e.size()-1];
    }
    cout << endl;

    cout << "Part 2: ";
    for (auto &e : stacks2) {
        cout << e[e.size()-1];
    }
    cout << endl;
    

    return 0;
}
