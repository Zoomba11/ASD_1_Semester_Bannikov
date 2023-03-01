//прямой, центральный и концевой обходы

#include <iostream>
#include <string>

struct BinaryNode
{
    int value;

    //и левый и правый пока равны nullptr
    BinaryNode* left = nullptr;
    BinaryNode* right = nullptr;

    BinaryNode(std::string& s)
    {
        //получаю число
        value = getValue(s);
        s.erase(0, digits(value));
        if (s[0] == '(')
            s = unbracket(s);
        else
            return;

        if (isDigit(s[0]))
            left = new BinaryNode(s);
        if (s[0] == ',' && isDigit(s[1]))
            right = new BinaryNode(s.erase(0, 1));
    }

    private:
	//проверяю скобка передо мной или число 
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
    //объявляю ему корень
    BinaryNode* root = nullptr;

    //заполняю дерево
    void printBT(const std::string& p, const BinaryNode* n, bool l) 
	{
		if (n == nullptr) return;
		std::cout << p << (l? "|--" : "|--") << n->value << "\n";
		printBT(p + (l? "|   " : "    "), n->left, 1);
		printBT(p + (l? "|   " : "    "), n->right, 0);
	}

public:
	BinaryTree(std::string s) : root(new BinaryNode(s)) { }

void print() { printBT("", root, 0); };

void directTraverse(BinaryNode* n)    //прямой (1)
{
    if (!n) return;
    std::cout << n->value << " ";
    directTraverse(n->left);
    directTraverse(n->right);
}

void directTraverse() { directTraverse(root); std::cout << "\n"; }

void symTraverse(BinaryNode* n)       //центральный (2)
{
    if (!n) return;
    symTraverse(n->left);
    std::cout << n->value << " ";
    symTraverse(n->right);
}
void symTraverse() { symTraverse(root); std::cout << "\n"; }

void inverseTraverse(BinaryNode* n)    //концевой (3)
{
    if (!n) return;
    inverseTraverse(n->left);
    inverseTraverse(n->right);
    std::cout << n->value << " ";
}
void inverseTraverse() { inverseTraverse(root); std::cout << "\n"; }
};

int main()
{
    //ввожу последовательность 
    BinaryTree tree("0(1(3,4),2(5,6))");
tree.print();
tree.directTraverse();  //(1)
tree.symTraverse();     //(2)
tree.inverseTraverse(); //(3)
}

