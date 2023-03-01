#include <iostream>

//подключаю библиотеку для стэка
#include <stack>

//подключаю библиотеку для std::string
#include <string>

using namespace std;

//проверяем скобку с помощью функции из 1-й лабы
bool function(std::string s_string)
{
    // <тип данных> имя
    std::stack<char> C;

    for (int i = 0; i < s_string.length(); i++)
    {
        if ((s_string[i] == '(') || (s_string[i] == '[') || (s_string[i] == '{'))
            C.push(s_string[i]);

        if (C.empty() && (s_string[i] == ')' || s_string[i] == ']' || s_string[i] == '}'))
            return false;

        //"top" - обращение к самому верхнему элементу списка
        if (s_string[i] == ')' && C.top() != '(')
            return false;

        if (s_string[i] == ']' && C.top() != '[')
            return false;

        if (s_string[i] == '}' && C.top() != '{')
            return false;

        //удаляю самый верхний элемента стэка
        if (s_string[i] == ')' && C.top() == '(')
            C.pop();

        if (s_string[i] == ']' && C.top() == '[')
            C.pop();

        if (s_string[i] == '}' && C.top() == '{')
            C.pop();
    }

    if (C.empty())
        return true;

    return false;
}

//функция,которая возвращает число целиком
string length(string str, int& j)
{
    string len;
    for (int i = j; str[i] >= '0' && str[i] <= '9'; i++)
    {
        len += str[i];
        j++;
    }
    j--;
    return len;
}

//функция,которая считает выражение
int count(string str)
{
    // <тип данных> имя   
    std::stack<string> numbers; 

    std::stack<char> elements; 
 
    int a = 0;
    int b = 0;
    str += '=';

    for (int i = 0; str[i] != '='; i++)
    {
        //для начала числа: - вызываю length. Заношу число в стек  
        if (str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '(' && str[i] != ')')
            numbers.push(length(str, i));

        //для мат. опреации:
        if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*')
        {
            //для (не пустого) стэк'а,
            if (!elements.empty())
            {
                //считаю, что (* и / приоритетнее, чем + и -)
                if ((str[i] == '+' || str[i] == '-') && (elements.top() == '/' || elements.top() == '*') && numbers.size() >= 2)
                {
                    //числовую строку в целые числа
                    b = stoi(numbers.top());

                    //удаляю самый верхний элемент стэка
                    numbers.pop();

                    a = stoi(numbers.top());
                    numbers.pop();

                    // проверка на дурака
                    if (b == '0' && elements.top() == '/')
                    {
                        cout << "error! division by zero! ";
                        return 0;
                    }

                    if (elements.top() == '/')
                        numbers.push(to_string(a / b));

                    if (elements.top() == '*')
                        numbers.push(to_string(a * b));

                    //удаляю самый верхний элемент стэка 
                    elements.pop();
                }
            }

            //if стэк не пустой
            if (!elements.empty())
            {
                //if данный элемент совпадает с тем, что находится в начале стэка, то 
                if ((str[i] == '+' || str[i] == '-') && (elements.top() == '+' || elements.top() == '-') && numbers.size() >= 2)
                {
                    //преобразовываю в целые числа
                    b = stoi(numbers.top());
                    //удаляю самый верхний элемент стэка
                    numbers.pop();

                    a = stoi(numbers.top());
                    numbers.pop();

                    if (elements.top() == '+')
                        numbers.push(to_string(a + b));

                    if (elements.top() == '-')
                        numbers.push(to_string(a - b));
                }
            }
        }

        //Иф элемент исходной строки равен скобке открывающей
        if (str[i] == '(')
        {
            //объявляю подстроку
            string str2;

            int left_boarder = 1;
            int right_boarder = 0;

            //нахожу выражение внутри скобки
            for (int j = i + 1; left_boarder != right_boarder; j++) 
            {
                str2 += str[j];
                if (str[j] == '(')
                    left_boarder += 1;
                if (str[j] == ')')
                    right_boarder += 1;
                i++;
            }
            str2.pop_back();

            numbers.push(to_string(count(str2)));
        }

        if (!elements.empty())
        {
            if ((str[i] == '/' || str[i] == '*') && (elements.top() == '/' || elements.top() == '*'))
            {
                b = stoi(numbers.top());
                numbers.pop();
                a = stoi(numbers.top());
                numbers.pop();

                // проверка на дурака
                if (b == '0' && elements.top() == '/')
                {
                    cout << "error! division by zero! ";
                    return 0;
                }

                if (elements.top() == '/' && b != '0')
                    numbers.push(to_string(a / b));

                if (elements.top() == '*')
                    numbers.push(to_string(a * b));

                //удаляю самый верхний элемент стэка
                elements.pop();
                elements.push(str[i]);
            }

            if ((str[i] == '/' || str[i] == '*') && (elements.top() == '+' || elements.top() == '-'))
                elements.push(str[i]);

            if ((str[i] == '+' || str[i] == '-') && (elements.top() != '/' && elements.top() != '*'))
                elements.push(str[i]);
        }

        //добавляю самый первый элемент в стэк
        if ((elements.empty() && (str[i] < '0' || str[i] > '9')) && str[i] != ')')
            elements.push(str[i]);
    }

    while (!elements.empty() && numbers.size() >= 2)
    {
        b = stoi(numbers.top());
        numbers.pop();
        a = stoi(numbers.top());
        numbers.pop();
        // проверка на дурака
        if (b == 0 && elements.top() == '/')
        {
            cout << "error! division by zero! ";
            return 0;
        }

        if (elements.top() == '/' && b != '0')
            numbers.push(to_string(a / b));

        if (elements.top() == '*')
            numbers.push(to_string(a * b));

        if (elements.top() == '+')
            numbers.push(to_string(a + b));

        if (elements.top() == '-')
            numbers.push(to_string(a - b));
        //удаляю самый верхний элемент стэка
        elements.pop();
    }

    return stoi(numbers.top());
}

int main()
{
    std::string str;
    std::cin >> str;
    printf("result is %d", count(str));

}
