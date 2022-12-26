# Дан текстовый файл с некоторым текстом на русском или
# английском языках произвольной длины (организовать чтение).
# Выбрав некоторую хеш-функцию, создать хеш-таблицу с:
# Лаба №13 “с наложением”

using System.Collections.Generic;

def HashFunction(s):
    result = 0
    for i in range(len(s)):
        result += ord(s[i])
    result = result % 32
    return result

def insert(mas, line):
    key = HashFunction(line)
    if mas[key] != []:
        first = line
        second = mas[key]
        flag = True
        i = 0
        while (first[i] == second[i]):
            i = i + 1
        else:
            flag = False#выход из цикла while с помощью else
        if flag:
            return "This row is already in the table"
        else:
            k = 0
            while mas[key + k] != []:
                k = k + 1
            else:
                mas[key + k] = line
    else:
        mas[key] = line

def delete(mas, line):
    key = HashFunction(line)
    k = 0
    while mas[key + k] != line:
        k = k + 1
    else:
        del mas[key]

def find(mas, line):
    key = HashFunction(line)
    if mas[key] != []:
        k = key
        while k < len(mas):
            if mas[k] == line:
                return mas[k]
            else:
                k = k + 1
    else:
        return "None"

def main():
    mas = [[] for i in range(32)]
    #file = open("File_lab13-14.txt", 'r', encoding="utf-8")
    file = open("File_lab13-14.txt", 'r')
    for line in file:
        line = ' '.join(line.split())
        insert(mas, line)
    for i in range(len(mas)):
        print(i, mas[i])
    a = find(mas, "We all like different genres, but we never argue with each other.")
    print(a)
    b = find(mas, "We begin to prepare in advance")
    delete(mas, "We all like different genres, but we never argue with each other.")
    a = find(mas, "We all like different genres, but we never argue with each other.")
    print(a)
    print(b)

if __name__ == "__main__":
    main()

