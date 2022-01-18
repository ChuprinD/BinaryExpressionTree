#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

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

bool is_extreme_parentheses(vector<string> s)
    {
    int balance = 0;
    for (int i = 0; i < s.size() - 1; i++)
        {
        if (s[i] == "(")
            balance++;
        else if (s[i] == ")")
            balance--;

        if (balance == 0)
            return false;
        }
    
    return true;
    }

bool isNumber(string elem)
    {
    for (char const &c : elem)
        if (std::isdigit(c) == 0) return false;
    return true;
    }


Node* infix_create_tree(Node* tree, vector<string> str)
    {  
    int balance = 0;
    int min_balance = 0;
    int index = 0;

    if (str.size() > 1 && is_extreme_parentheses(str))
        {
        str.pop_back();
        str.erase(str.begin(), str.begin() + 1);
        }

    for (int i = 0; i < str.size(); i++)
        {
        if (str[i] == "(") balance++;
        else if (str[i] == ")") balance--;
        else if (!isNumber(str[i]) && balance <= min_balance)
            {
            min_balance = balance;
            index = i;
            }
        }

    if (!tree)
        tree = new Node(str[index]);
    else
        tree->elem_ = str[index];

    if (index != 0)
        {
        vector <string> first = {};
        balance = 0;
        for (int i = index - 1; i >= 0; i--)
            {
            if (str[i] == "(") balance++;
            if (str[i] == ")") balance--;

            if (str[i] == "(" && balance > 0)
                continue;

            first.push_back(str[i]);
            }
        reverse(first.begin(), first.end());

        vector <string> second = {};
        balance = 0;
        for (int i = index + 1; i < str.size(); i++)
            {
            if (str[i] == "(") balance++;
            if (str[i] == ")") balance--;

            if (str[i] == ")" && balance <= 0)
                continue;

            second.push_back(str[i]);
            }

        tree->left_ = infix_create_tree(tree->left_, first);
        tree->right_ = infix_create_tree(tree->right_, second);
        }

    return tree;
    }

Node* postfix_create_tree(Node* tree, vector<string>& str)
    {
    if (!tree)
        tree = new Node(str[str.size() - 1]);
    else
        tree->elem_ = str[str.size() - 1];

    str.pop_back();

    if (isNumber(tree->elem_)) return tree;

    tree->right_ = postfix_create_tree(tree->right_, str);
    tree->left_ = postfix_create_tree(tree->left_, str);

    return tree;
    }

Node* prefix_create_tree(Node* tree, vector<string>& str)
    {
    if (!tree)
        tree = new Node(str[0]);
    else
        tree->elem_ = str[0];

    str.erase(str.begin());

    if (isNumber(tree->elem_)) return tree;

    tree->left_ = prefix_create_tree(tree->left_, str);
    tree->right_ = prefix_create_tree(tree->right_, str);
  
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

void print_infix(Node* tree)
    {
    if (tree)
        {
        if (!isNumber(tree->elem_))
            cout << "(";
        print_infix(tree->left_);
        cout << tree->elem_;
        print_infix(tree->right_);
        if (!isNumber(tree->elem_))
            cout << ")";
        }
    }

void print_postfix(Node* tree)
    {
    if (tree)
        {
        print_postfix(tree->left_);
        print_postfix(tree->right_);
        cout << tree->elem_ << " ";
        }
    }

void print_prefix(Node* tree)
    {
    if (tree)
        {
        cout << tree->elem_ << " ";
        print_prefix(tree->left_);
        print_prefix(tree->right_);
        }
    }

vector <string> get_string()
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
                i--;
                }
            }
        if (tmp != "")
            s.push_back(tmp);
        i++;
        }

    return s;
    }

int main()
    {
    Node tree;
    string type;
    getline(cin, type);
    vector <string> s = get_string();
    
    if (type == "prefix")
        {
        prefix_create_tree(&tree, s);
        
        cout << "infix: ";
        print_infix(&tree);
        cout << endl;

        cout << "postfix: ";
        print_postfix(&tree);
        cout << endl;
        }
    else if (type == "postfix")
        {
        postfix_create_tree(&tree, s);

        cout << "infix: ";
        print_infix(&tree);
        cout << endl;

        cout << "prefix: ";
        print_prefix(&tree);
        cout << endl;
        }
    else
        {
        infix_create_tree(&tree, s);

        cout << "postfix: ";
        print_postfix(&tree);
        cout << endl;

        cout << "prefix: ";
        print_prefix(&tree);
        cout << endl;
        }

    system("pause");
    return 0;
    }
