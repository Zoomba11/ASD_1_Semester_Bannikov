# сложность 0(n*log(n)) поразрядная

using static System.Runtime.InteropServices.JavaScript.JSType;
using System.Drawing;
using System.Xml.Linq;

def get_number_of_digits(number):
    i = 1
    while (number >= 10 * *i):
        i = i + 1
    return i# определяем количество разряда


def get_digit(number, i):
    return number % (10 * *(i + 1))//(10**i)#выделяем цифру


def max_number_of_digits(numbers):# макс кол-во разрядов
    number_of_digits = 1
    for number in numbers:
        current_digits = get_number_of_digits(number)# для каждого числа определяем разряд
        if current_digits > number_of_digits:
            number_of_digits = current_digits
    return number_of_digits


def counting_sort(sequince, position):#описываем алгоритм сортировки распределяющим подсчетам
    min_key = min([get_digit(x, position) for x in sequince])
    max_key = max([get_digit(x, position) for x in sequince])
    n = max_key - min_key + 1
    support = [0 for i in range(n)]# обьявляем вспомогательный элемент
    for element in sequince:
        support[get_digit(element, position) - min_key] += 1
    size = len(sequince)
    for i in range(n - 1, -1, -1):#выполняем обратный проход по вспомогательному элементу
        size -= support[i]
        support[i] = size
    result = [None for i in range(len(sequince))]
    for element in sequince:# заполняем новую последовательность на основании сортируемой и вспомогательной послед
        result[support[get_digit(element, position) - min_key]] = element
        support[get_digit(element, position) - min_key] += 1
    return result


def radix_sort(sequince):# реализует сортировку
    number_of_digits = max_number_of_digits(sequince)
    for i in range(number_of_digits):
        sequince = counting_sort(sequince, i)
    return sequince


numbers = [122, 10, 24, 7, 33]

result = radix_sort(numbers)

print(result)