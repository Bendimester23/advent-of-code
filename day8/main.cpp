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

    int width = lines[0].size();

    int count = width * 2 + lines.size() * 2 - 4;
    int highScore = 0;

    for (size_t i = 1; i < lines.size() - 1; i++)
    {
        for (size_t k = 1; k < width - 1; k++)
        {
            auto thisVal = stoi(lines[i].substr(k, 1));
            int score = 1;

            bool visibleBottom = true;
            int viewDst = 0;
            for (size_t l = i + 1; l < lines.size(); l++)
            {
                viewDst++;
                if (stoi(lines[l].substr(k, 1)) >= thisVal) {
                    visibleBottom = false;
                    break;
                }
            }

            score *= viewDst;
            viewDst = 0;

            bool visibleRight = true;
            for (size_t l = k + 1; l < width; l++)
            {
                viewDst++;
                if (stoi(lines[i].substr(l, 1)) >= thisVal) {
                    visibleRight = false;
                    break;
                }
            }

            score *= viewDst;
            viewDst = 0;

            bool visibleTop = true;
            for (int l = i - 1; l >= 0; l--)
            {
                viewDst++;
                if (stoi(lines[l].substr(k, 1)) >= thisVal) {
                    visibleTop = false;
                    break;
                }
            }
            
            score *= viewDst;
            viewDst = 0;

            bool visibleLeft = true;
            for (int l = k - 1; l >= 0; l--)
            {
                viewDst++;
                if (stoi(lines[i].substr(l, 1)) >= thisVal) {
                    visibleLeft = false;
                    break;
                }
            }
            score *= viewDst;

            bool visible = visibleRight || visibleBottom || visibleTop || visibleLeft;

            count += visible;

            if (score > highScore) highScore = score;
        }
    }
    
    cout << "Part 1: " << to_string(count) << endl;
    cout << "Part 2: " << to_string(highScore) << endl;

    return 0;
}
