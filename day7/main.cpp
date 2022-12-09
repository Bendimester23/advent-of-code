#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s)
{
    string delimiter = "/";
    vector<string> res;

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        res.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    res.emplace_back(s);

    return res;
}

struct node
{
    string name;
    vector<node> children;
    bool isDir;
    int size;

    node *find(string name)
    {
        for (size_t i = 0; i < children.size(); i++)
        {
            if (children[i].name == name)
            {
                return &children[i];
            }
        }

        return nullptr;
    }

    node *mkdir(string name)
    {
        children.emplace_back(node{name, vector<node>(), true, 0});
        return &children.back();
    }

    void addFile(string name, int size)
    {
        children.emplace_back(node{name, vector<node>(), false, size});
    }

    vector<node> getChildDirs()
    {
        vector<node> res;
        for (auto &e : children)
        {
            if (e.isDir)
            {
                res.emplace_back(e);
                auto recurse = e.getChildDirs();
                for (auto &f : recurse)
                {
                    res.emplace_back(f);
                }
            }
        }
        return res;
    }

    int calcSize()
    {
        if (isDir)
        {
            int s = 0;
            for (auto &e : children)
            {
                s += e.calcSize();
            }
            return s;
        }
        return size;
    }
};

struct fs
{
    node root{"", vector<node>(), true, 0};

    void mkdir(string path)
    {
        auto parts = split(path);
        int i = 0;

        node *curr = &root;

        for (auto &e : parts)
        {
            if (i == 0)
            {
                i++;
                continue;
            }

            auto tmp = curr->find(e);
            if (tmp == nullptr)
                curr = curr->mkdir(e);
            else
                curr = tmp;

            i++;
        }
    }

    void addFile(string path, string name, int size)
    {
        auto parts = split(path);
        int i = 0;

        node *curr = &root;

        for (auto &e : parts)
        {
            if (i == 0)
            {
                i++;
                continue;
            }

            auto tmp = curr->find(e);
            if (tmp == nullptr)
                curr = curr->mkdir(e);
            else
                curr = tmp;

            i++;
        }

        curr->addFile(name, size);
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

    string path = "/";

    fs files;

    for (auto &e : lines)
    {
        if (e[0] == '$')
        {
            if (e.substr(0, 4) == "$ cd")
            {
                auto arg = e.substr(5, e.length() - 4);
                if (arg == "/")
                    path = "/";
                else if (arg == "..")
                {
                    path = path.substr(0, path.substr(0, path.length() - 1).find_last_of('/')) + "/";
                }
                else
                    path += arg + "/";
            }
            else if (e.substr(0, 4) == "$ ls")
            {
                //Nothing here
            }
        }
        else
        {
            if (e.substr(0, 3) == "dir") {
                files.mkdir(path + e.substr(4, e.length()-4));
            } else {
                int splitIdx = e.find_first_of(' ');
                int size = stoi(e.substr(0, splitIdx));
                string name = e.substr(splitIdx+1);

                files.addFile(path, name, size);
            }
        }
    }

    auto asd = files.root.getChildDirs();

    int total = 0;

    for (auto &e : asd) {
        if (e.calcSize() <= 100000 && e.name != "") {
            total += e.calcSize();
        }
    }

    cout << "Part 1: " << to_string(total) << endl;

    int toDelete = 2 << 28;

    for (auto &e : asd) {
        int s = e.calcSize();
        if (s >= 8381165 && s < toDelete && e.name != "") {
            toDelete = s;
        }
    }

    cout << "Part 2: " << to_string(toDelete) << endl;

    return 0;
}
