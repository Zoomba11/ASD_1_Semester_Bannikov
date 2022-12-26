# На вход подаётся математическое выражение. Элементы - числа. Операции - "+ - * /".
# Также есть скобочки. Окончанием выражения служит "=". Программа должна вывести результат выражения
# Пример ввода:
# 2+7*(3/9)-5=
# Замечание:
# Программа также должна делать "проверку на дурака": нет деления на 0, все скобки стоят верно (см лабу №1) и т.п.
import sys

def Check_brackets(s):
    mas = []
    flag = False
    for i in range(len(s)):
        if s[i] == '(':
            mas.append(i)
            flag = True
        if s[i] == ')':
            mas.pop()
    if (len(mas) == 0 and flag):
        return 2
    if (len(mas)==0 and not flag):
        return 1
    else:
        return 0


def Search_internal_brackets(mas):
    #проверка на внутренние скобки
    start = 0
    end = 0
    i = 0
    while mas[i]!=')':
        if mas[i] == '(':
            start = i+1
        i+=1
    else:
        end = i-1
    return start, end


def Calculation(mas, first, second):
    res = 0#решение выражения в скобках
    if mas[first + 1] == '+':
        res = float(mas[first]) + float(mas[second])
    if mas[first + 1] == '-':
        res = float(mas[first]) - float(mas[second])
    if mas[first + 1] == '*':
        res = float(mas[first]) * float(mas[second])
    if (mas[first + 1] == '/'):
        res = float(mas[first]) / float(mas[second])
    print(res)
    mas[first] = str(res)
    del mas[first+1:second+1]
    return mas


def Splitting_into_an_array(s):
    #заполнение массива
    mas = []
    i = 0
    while i<len(s):
        if (s[i].isdigit()):#если символ - число
            k = 0
            while s[i+k].isdigit():
                k += 1
            else:
                mas.append(s[i:i+k])
                i = i+k
        else:
            mas.append(s[i])
            i += 1
    return mas

s = str(input())
mas = Splitting_into_an_array(s)
print(mas)
x = Check_brackets(s)
print(x)
if x == 0:
    print("The expression is incorrect")
if x == 2:#Проверка на правильность выражения
    while '(' in mas:
        start, end = Search_internal_brackets(mas)
        new_end = end
        print(start, end)
        while new_end != start:
            k = 0
            if (('*' in mas[start:end]) or ('/' in mas[start:end])):#первостепенные действия * и /
                for i in range(start, end):
                    if i < len(mas):
                        try:
                            if mas[i] == '*' or mas[i] == '/':
                                mas = Calculation(mas, i-1, i+1)
                                k += 1
                                print(mas)
                        except ZeroDivisionError:#исключение на дение на нуль
                            print("Division by zero!")
                            sys.exit(0)#прерываем работу программы
                    else:
                        break
                new_end = new_end - 2*k
            else:
                for i in range(start, new_end):
                    if i < len(mas):
                        if mas[i] == '-' or mas[i] == '+':#потом уже считаем сумму и разность
                            mas = Calculation(mas, i-1, i+1)
                            k += 1
                            print(mas)
                    else:
                        break
                new_end = new_end - 2*k
        print(start, mas)
        del mas[start+1]
        del mas[start-1]

while len(mas) > 2:
    k = 0
    if ('*' or '/') in mas:#первостепенные действия * и /
        for i in range(len(mas)):
            if i < len(mas):
                try:
                    if mas[i] == '*' or mas[i] == '/':
                        mas = Calculation(mas, i - 1, i + 1)
                        k += 1
                        print(mas)
                except ZeroDivisionError:#исключение на дение на нуль
                    print("Division by zero!")
                    sys.exit(0)#прерываем работу программы
            else:
                break
    else:#потом уже считаем сумму и разность
        for i in range(len(mas)):
            if i < len(mas):
                if mas[i] == '-' or mas[i] == '+':
                    mas = Calculation(mas, i - 1, i + 1)
                    k += 1
                    print(mas)
            else:
                break
print(float(mas[0]))
