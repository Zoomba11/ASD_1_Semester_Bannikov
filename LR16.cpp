// НЕрекурсивный прямой обход 

#include <iostream>
#include <vector>
#include <string>

struct BinaryNode
{
    int value;

    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;

    BinaryNode(std::string& s)
    {
        value = getValue(s);
        s.erase(0, digits(value));
        if (s[0] == '(')
            s = unbracket(s);
        else
            return;

        //первый элемент - число? создаю узел! 
        if (isDigit(s[0]))
            left = new BinaryNode(s);
        if (s[0] == ',' && isDigit(s[1]))
            right = new BinaryNode(s.erase(0, 1));
    }


    private:
	//число или скобка? 
	bool isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }

    int digits(int n)
    {   
        if (n)
        {
            n = floor(log10(n) + 1);
            return n;
        }
        else
            return 1;
    }

    int getValue(std::string& s)
    {
        //размерность строки: 16
        int n = s.size();
        int i = 1;
        while (i < n)
            if (!isDigit(s[i++]))
                break;

        return std::stoi(s.substr(0, i));
    }

    //удаляю скобки 
    std::string unbracket(std::string s)
    {
        for (int i = 1, d = 1; i < s.size(); i++, d += (s[i] == '(') - (s[i] == ')'))
            if (!d)
                return s.erase(0, 1).erase(i - 1, 1);
        return s;
    }
};

//реализую бинарное дерево
class BinaryTree
{
    BinaryNode* root = nullptr;

    //заполняю дерево
    void print(const std::string& p, const BinaryNode* n, bool l)
	{
		if (!n) return;
		std::cout << p << (l? "|--" : "|--") << n->value << "\n";
		print(p + (l? "|   " : "    "), n->left, 1);
		print(p + (l? "|   " : "    "), n->right, 0);
	}

public:
	BinaryTree(std::string s) : root(new BinaryNode(s)) { }

void print() { print("", root, 0); };

//реализую нерекурсивный обход
void NonRecursive()
{
    //в stack помещен корень дерева
    std::vector<BinaryNode*> stack = { root };
    while (!stack.empty())
    {
        BinaryNode* n = stack.back();
        stack.pop_back();
        std::cout << n->value << " ";
        if (n->right)
            stack.push_back(n->right);
        if (n->left)
            stack.push_back(n->left);
    }
    std::cout << "\n";
}
};

int main()
{
    //ввожу последовательность
    BinaryTree tree("0(1(3,4),2(5,6))");
//печатаю дерево
tree.print();
//вызываю функцию нерекурсивного обхода
tree.NonRecursive();
}
