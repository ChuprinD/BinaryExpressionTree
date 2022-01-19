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

    void print(int level);
    Node* infix_create_tree(vector<string> str);
    Node* postfix_create_tree(vector<string>& str);
    Node* prefix_create_tree(vector<string>& str);
    void print_infix();
    void print_postfix();
    void print_prefix();
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

void Node::print(int level)
    {
    if (this)
        {
        this->left_->print(level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << this->elem_ << '\n';
        this->right_->print(level + 1);
        }
    }

Node* Node::infix_create_tree(vector<string> str)
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

    this->elem_ = str[index];

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

            if (str[i] == ")" && balance < 0)
                continue;

            second.push_back(str[i]);
            }
        this->left_ = new Node();
        this->left_ = this->left_->infix_create_tree(first);

        this->right_ = new Node();
        this->right_ = this->right_->infix_create_tree(second);
        }

    return this;
    }

Node* Node::postfix_create_tree(vector<string>& str)
    {
    this->elem_ = str[str.size() - 1];

    str.pop_back();

    if (isNumber(this->elem_)) return this;

    this->right_ = new Node();
    this->right_ = this->right_->postfix_create_tree(str);

    this->left_ = new Node();
    this->left_ = this->left_->postfix_create_tree(str);

    return this;
    }

Node* Node::prefix_create_tree(vector<string>& str)
    {
    this->elem_ = str[0];

    str.erase(str.begin());

    if (isNumber(this->elem_)) return this;

    this->left_ = new Node();
    this->left_ = this->left_->prefix_create_tree(str);

    this->right_ = new Node();
    this->right_ = this->right_->prefix_create_tree(str);
  
    return this;
    } 


void Node::print_infix()
    {
    if (this && this->elem_ != "")
        {
        if (!isNumber(this->elem_))
            cout << "(";
        this->left_->print_infix();
        cout << this->elem_;
        this->right_->print_infix();
        if (!isNumber(this->elem_))
            cout << ")";
        }
    }

void Node::print_postfix()
    {
    if (this && this->elem_ != "")
        {
        this->left_->print_postfix();
        this->right_->print_postfix();
        cout << this->elem_ << " ";
        }
    }

void Node::print_prefix()
    {
    if (this && this->elem_ != "")
        {
        cout << this->elem_ << " ";
        this->left_->print_prefix();
        this->right_->print_prefix();
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
        tree.prefix_create_tree(s);
        
        cout << "infix: ";
        tree.print_infix();
        cout << endl;

        cout << "postfix: ";
        tree.print_postfix();
        cout << endl;
        }
    else if (type == "postfix")
        {
        tree.postfix_create_tree(s);

        cout << "infix: ";
        tree.print_infix();
        cout << endl;

        cout << "prefix: ";
        tree.print_prefix();
        cout << endl;
        }
    else
        {
        tree.infix_create_tree(s);

        cout << "postfix: ";
        tree.print_postfix();
        cout << endl;

        cout << "prefix: ";
        tree.print_prefix();
        cout << endl;
        }

    system("pause");
    return 0;
    }
