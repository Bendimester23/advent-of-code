#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

template <class T>
bool containsChar(T arr, char item)
{
    for (auto &e : arr)
    {
        if (e == item)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream f("./input.txt");

    if (!f.is_open())
    {
        return 1;
    }

    vector<string> lines;

    while (f.is_open() && !f.eof())
    {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }

    int out = 0;

    for (auto &e : lines)
    {
        int halfSize = e.size() / 2;

        vector<char> first;
        vector<char> second;

        vector<char> both;

        int i = 0;

        for (auto &f : e)
        {
            if (i >= halfSize)
            {
                second.emplace_back(f);
                for (auto &g : first)
                {
                    if (g == f && !containsChar<vector<char>>(both, f))
                    {
                        both.emplace_back(g);
                        break;
                    }
                }
            }
            else
            {
                first.emplace_back(f);
            }

            i++;
        }

        for (auto &f : both)
        {
            if ((f & 0x20) == 0x20)
            {
                // Lowercase
                out += f - 0x60;
            }
            else
            {
                out += f - 0x40 + 0x1A;
            }
        }
    }

    cout << "Part 1: " << to_string(out) << endl;

    vector<char> badges;

    for (size_t i = 0; i < lines.size(); i += 3)
    {
        for (auto &e : lines[i])
        {
            if (containsChar<string>(lines[i + 1], e) && containsChar<string>(lines[i + 2], e))
            {
                badges.emplace_back(e);
                break;
            }
        }
    }

    out = 0;

    for (auto &e : badges)
    {
        if ((e & 0x20) == 0x20)
        {
            // Lowercase
            out += e - 0x60;
        }
        else
        {
            out += e - 0x26;
        }
    }

    cout << "Part 2: " << to_string(out) << endl;

    return 0;
}
