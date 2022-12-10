#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>

using namespace std;

int sqr(int a)
{
    return a * a;
}

struct Vector2
{
    int x;
    int y;

    int sqrDst(const Vector2 &other)
    {
        return sqr(x - other.x) + sqr(y - other.y);
    }

    Vector2 operator+(Vector2 other)
    {
        return Vector2{
            x + other.x,
            y + other.y};
    }
};

Vector2 getMovementDir(Vector2 head, Vector2 tail)
{
    if (head.x == tail.x)
    {
        return Vector2{
            0,
            (head.y > tail.y) * 2 - 1,
        };
    }
    else if (head.y == tail.y)
    {
        return Vector2{
            (head.x > tail.x) * 2 - 1,
            0,
        };
    }
    return Vector2{
        (head.x > tail.x) * 2 - 1,
        (head.y > tail.y) * 2 - 1,
    };
}

bool operator==(Vector2 a, Vector2 b)
{
    return a.x == b.x && a.y == b.y;
}

namespace std
{
    template <>
    struct hash<Vector2>
    {
        size_t operator()(const Vector2 &x) const
        {
            return hash<int>()(x.x) | (hash<int>()(x.y) << 16);
        }
    };
}

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

    Vector2 headPos{0, 0};
    Vector2 tailPos{0, 0};
    unordered_set<Vector2> visited;
    visited.insert(headPos);

    for (const auto &e : lines)
    {
        char dir = e[0];
        int count = stoi(e.substr(2));

        for (size_t i = 0; i < count; i++)
        {
            switch (dir)
            {
            case 'U':
                headPos.y++;
                break;

            case 'D':
                headPos.y--;
                break;

            case 'R':
                headPos.x++;
                break;

            case 'L':
                headPos.x--;
                break;

            default:
                break;
            }

            if (headPos.sqrDst(tailPos) > 2)
            {
                tailPos = tailPos + getMovementDir(headPos, tailPos);
                visited.insert(tailPos);
            }
        }
    }

    cout << "Part 1: " << visited.size() << endl;

    headPos = Vector2{0, 0};

    visited.clear();

    Vector2 parts[9];

    for (size_t i = 0; i < 9; i++)
    {
        parts[i] = Vector2{0, 0};
    }
    
    for (const auto &e : lines)
    {
        char dir = e[0];
        int count = stoi(e.substr(2));

        for (size_t i = 0; i < count; i++)
        {
            switch (dir)
            {
            case 'U':
                headPos.y++;
                break;

            case 'D':
                headPos.y--;
                break;

            case 'R':
                headPos.x++;
                break;

            case 'L':
                headPos.x--;
                break;

            default:
                break;
            }

            for (int i = 0; i < 9; i++)
            {
                auto prev = headPos;
                if (i > 0) prev = parts[i-1];
                if (prev.sqrDst(parts[i]) > 2)
                {
                    parts[i] = parts[i] + getMovementDir(prev, parts[i]);
                }
            }
            visited.insert(parts[8]);
        }
    }

    cout << "Part 2: " << visited.size() << endl;

    return 0;
}
