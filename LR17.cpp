// Операции над БДП: поиск, добавление, удаление

#include <iostream>
#include <vector>
#include <string>

struct BinaryNode
{
    int value;
    BinaryNode* left = nullptr, * right = nullptr;

	BinaryNode(std::string& s)                              
    {
        value = getValue(s);
        s.erase(0, digits(value));
        if (s[0] == '(') s = unbracket(s); else return;
        if (isDigit(s[0])) left = new BinaryNode(s);
        if (s[0] == ',' && isDigit(s[1])) right = new BinaryNode(s.erase(0, 1));
    }

    void add(int x) // a - добавление
    {
        std::string s = std::to_string(x);
        if (x > value && right)
            right->add(x); 
        if (x > value && !right)
            right = new BinaryNode(s);
        if (x < value && left)
            left->add(x);
        if (x < value && !left)
            left = new BinaryNode(s);
    }

    void remove(int x) // r -удаление
    {
    
        if (x > value && right && right->value == x)
            right = nullptr;
        if (x > value && right && right->value != x)
            right->remove(x);
        if (x < value && left && left->value == x)
            left = nullptr;
        if (x < value && left && left->value != x)
            left->remove(x);
    }

    bool contains(int x) // c - поиск
    {
        return find(x);
    }

    BinaryNode* find(int x)
    {
        if (x == value)
            return this;
        if (x > value && right)
            return right->find(x);
        if (x < value && left)
            return left->find(x);
        return nullptr;
    }

    //возвращаю элементы
    void getElements(std::vector<int>& v)
    {
        //добавляю элемент в конец
        v.push_back(value);
        //возвращаю
        if (left)
            left->getElements(v);
        if (right)
            right->getElements(v);
    }

    private:
	bool isDigit(char c) { return c >= '0' && c <= '9'; }
    int digits(int n) { return n ? floor(log10(n) + 1) : 1; }

    int getValue(std::string& s)
    {
        int n = s.size(), i = 1;
        while (i < n) if (!isDigit(s[i++])) break;
        return std::stoi(s.substr(0, i));
    }

    std::string unbracket(std::string s)
    {
        for (int i = 1, d = 1; i < s.size(); i++, d += (s[i] == '(') - (s[i] == ')'))
            if (!d) return s.erase(0, 1).erase(i - 1, 1);
        return s;
    }
};

class BinaryTree
{
    BinaryNode* root = nullptr;

    void print(const std::string& p, const BinaryNode* n, bool l)
	{
		if (!n) return;
		std::cout << p << (l? "|--" : "|--") << n->value << "\n";
		print(p + (l? "|   " : "    "), n->left, true);
		print(p + (l? "|   " : "    "), n->right, false);
	}
public:

	BinaryTree(std::string s = "")

    {
    if (!s.empty()) root = new BinaryNode(s);
}

void print() { if (root) print("", root, 0); else std::cout << "|--\n"; };

void add(int x)
{
    std::string s = std::to_string(x);
    if (root) root->add(x);
    else root = new BinaryNode(s);
}

void remove(int x)
{
    if (!root) return;

    BinaryNode* n;
    if (root->value == x) n = root;
    else n = root->find(x);

    std::vector<int> branch;
    if (n->left) n->left->getElements(branch);
    if (n->right) n->right->getElements(branch);

    if (root->value == x) root = nullptr;
    else root->remove(x);
    for (int e : branch) add(e);
	}

	bool contains(int x) { return root ? root->contains(x) : false; }
};

int main()
{
    BinaryTree tree;
    std::string command;
    // х буду вводить в дерево
    int x;
    tree.print();
    //бесконечный цикл
    while (1)
    {
        std::cin >> command >> x;
        //добавление х
        if (command == "a") tree.add(x), tree.print();
        //удаление х
        if (command == "r") tree.remove(x), tree.print();
        //случай нахождения х в дереве
        if (command == "c")
            std::cout << x << (tree.contains(x) ? " exists\n" : " not exists\n");
    }
}
