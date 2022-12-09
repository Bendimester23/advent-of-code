#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

bool allDifferent(char a, char b, char c, char d)
{
    return a != b && a != c && a != d && b != c && b != d && c != d;
}

int main()
{
    ifstream f("./input.txt");

    if (!f.is_open())
        return 1;

    string l;
    getline(f, l);

    for (size_t i = 3; i < l.size(); i++)
    {
        if (allDifferent(l[i], l[i - 1], l[i - 2], l[i - 3]))
        {
            cout << "Part 1: " << i + 1 << endl;
            break;
        }
    }

    for (size_t i = 13; i < l.size(); i++)
    {
        set<char> toCheck;
        bool same = true;
        for (size_t k = 0; k < 14; k++)
        {
            if (!(toCheck.insert(l[i - k]).second))
            {
                same = false;
                break;
            }
        }
        if (same)
        {
            cout << "Part 2: " << i + 1 << endl;
            break;
        }
    }

    return 0;
}
