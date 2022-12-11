#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

class Node {
public:
    virtual int get_value(int input) {
        return 0;
    }
};

class Constant: public Node {
    int val;
public:
    Constant(int value): val(value) {
    }

    virtual int get_value(int input) override {
        return val;
    }
};

class InputValue: public Node {
public:
    virtual int get_value(int input) override {
        return input;
    }
};

enum Operator {
    Add,
    Subtract,
    Multiply,
    Divide
};

static Operator parseOperator(char inp) {
    switch (inp) {
            case '+':
                return Operator::Add;
            
            case '-':
                return Operator::Subtract;

            case '*':
                return Operator::Multiply;

            case '/':
                return Operator::Divide;

            default:
                return Operator::Add;
    }
}

struct Expression {
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Operator operation;

    int run(int input) {
        switch (operation) {
            case Operator::Add:
                return left->get_value(input) + right->get_value(input);

            case Operator::Subtract:
                return left->get_value(input) - right->get_value(input);

            case Operator::Multiply:
                return left->get_value(input) * right->get_value(input);

            case Operator::Divide:
                return left->get_value(input) / right->get_value(input);

            default:
                return 0;
        }
    }

    static Expression parse(string raw) {
        int opIdx = raw.find_first_of(' ')+1;
        string first = raw.substr(0, opIdx - 1);
        string last = raw.substr(opIdx + 2);

        Expression ex;

        if (first == "old") {
            ex.left = make_shared<InputValue>(InputValue());
        } else {
            ex.left = make_shared<Constant>(Constant(stoi(first)));
        }

        if (last == "old") {
            ex.right = make_shared<InputValue>(InputValue());
        } else {
            ex.right = make_shared<Constant>(Constant(stoi(last)));
        }

        ex.operation = parseOperator(raw[opIdx]); 

        return ex;
    }
};

struct Monkey {
    int id;
    vector<int> items;
    Expression exp;
    int test; //Check if divisible
    int toT; //Id of target when true;
    int toF; //Id if target when false;
    
    static Monkey parse(vector<string> input) {
        Monkey m;
        string almostNum = input[0].substr(7);
        m.id = stoi(almostNum.substr(0, almostNum.size()-1));

        string itemsList = input[1].substr(18)+", ";
        vector<int> iList;

        do {
            int stopIdx = itemsList.find_first_of(',');
            iList.emplace_back(stoi(itemsList.substr(0, stopIdx)));
            itemsList = itemsList.substr(stopIdx+1);
        } while (itemsList.find_first_of(',') != itemsList.npos);

        m.items = iList;
        
        m.exp = Expression::parse(input[2].substr(19));

        m.test = stoi(input[3].substr(21));

        m.toT = stoi(input[4].substr(29));
        m.toF = stoi(input[5].substr(30)); 
        return m;
    }
};

int main()
{
    ifstream f("./input-demo.txt");

    if (!f.is_open())
        return 1;

    vector<string> lines;

    while (!f.eof())
    {
        string tmp;
        getline(f, tmp);
        lines.emplace_back(tmp);
    }
   
    vector<string> currLines;
    vector<Monkey> monkeys;

    for (auto &e : lines) {
        if (e == "") {
            monkeys.emplace_back(Monkey::parse(currLines));
            currLines.clear();
        } else {
            currLines.emplace_back(e);
        }
    }

    cout << "Found " << monkeys.size() << " monkeys" << endl;

    int count[monkeys.size()];

    for (int i = 0; i < monkeys.size(); i++) {
        count[i] = 0;
    }

    for (int i = 0; i < 20; i++) {
        int k = 0;
        cout << "--------------------\nRound " << (i+1) << endl;
        for (auto &e : monkeys) {
            while (e.items.size() > 0) {
                count[k]++;
                int item = e.items[0];
                e.items.erase(e.items.begin());
                item = e.exp.run(item);
                item = floor(static_cast<float>(item) / 3);
                if (item % e.test == 0) {
                    monkeys[e.toT].items.emplace_back(item);
                } else {
                    monkeys[e.toF].items.emplace_back(item);
                }
            }
            k++; 
        }
        k = 0;
        for (auto &e : monkeys) {
            cout << "Monkey " << (k+1) << ": ";
            for (auto &f : e.items) {
                cout << f << ", ";
            }
            cout << endl;
            k++;
        }
    }

    for (auto &e : count) {
        cout << e << ", ";
    }
    cout << endl;

    int top[2] = {0, 0};

    for (int i = 0; i < monkeys.size(); i++) {
        if (count[i] > top[0]) {
            top[1] = top[0];
            top[0] = count[i];
        } else if (count[i] < top[1]) {
            top[1] = count[i];
        }
    }

    cout << "Part 1: " << (top[0] * top[1]) << endl;

    return 0;
}
