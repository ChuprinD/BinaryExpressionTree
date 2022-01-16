#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Node
    {
    public:
        string elem_;
        Node* left_;
        Node* right_;

    Node(string elem)
        {
        elem_ = elem;
        left_ = nullptr;
        right_ = nullptr;
        }

    Node()
        {
        elem_ = "";
        left_ = nullptr;
        right_ = nullptr;
        }
    };

string delete_extreme_parentheses(string s)
    {
    if (s.front() == '(' && s.back() == ')')
        {
        s.erase(0, 1);
        s.pop_back();
        }
    return s;
    }

bool isNumber(string elem)
    {
    for (char const &c : elem)
        if (std::isdigit(c) == 0) return false;
    return true;
    }

Node* create_tree(Node* tree, string str)
    {
    int balance = 0;
    int min_balance = 0;
    int index = 0;
    int size = 0;
    str = delete_extreme_parentheses(str);
    stringstream s;
    s << str;
    string cur;
    s >> cur;
    string elem = cur;

    for (int i = 0; s.tellg() != -1; i++)
        {  
        if (cur == "(")
            balance++;
        if (cur == ")")
            balance--;

        if (!isNumber(cur) && balance <= min_balance)
            {
            min_balance = balance;
            index = s.tellg();
            elem = cur;
            }
        s >> cur;
        size = i;
        }

    if (!tree)
        tree = new Node(elem);
    else
        tree -> elem_ = elem;

    string first = s.str().substr(0, index - 1);
    string second = s.str().substr(index + 1, s.str().size() - index);

    if (size != 0)
        {
        tree->left_ = create_tree(tree->left_, first);
        tree->right_ = create_tree(tree->right_, second);
        }

    return tree;
    }

void print(Node* tree, int level)
    {
    if (tree)
        {
        print(tree->left_, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << tree->elem_ << '\n';
        print(tree->right_, level + 1);
        }
    }

int main()
    {
    string sin;
    getline(cin, sin);
    vector<string> s = {};
    int i = 0;

    while (i < sin.size())
        {
        string tmp = "";
        if (sin[i] != ' ')
        {
            if (!isdigit(sin[i]))
                tmp += sin[i];
            else
            {
                while (isdigit(sin[i]))
                    tmp += sin[i++];
                //i--;
            }
        }
        s.push_back(tmp);
        i++;
            
        }

    for (string str : s)
        cout << str;

    /*Node tree;
    create_tree(&tree, sin);
    print(&tree, 0);*/

    return 0;
    }
