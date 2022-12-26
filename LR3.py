# На вход дается одно число х, нужно вывести все числа от 1 до х, удовлетворяющие условию:
#     3^K*5^L*7^M=x(i)
# где K, L, M - натуральные числа или могут быть равны 0.

import math

x = int(input())
mas = []

mas.append(math.floor(math.log(x, 3)))#добавляем в массив степеней каждого числа
mas.append(math.floor(math.log(x, 5)))
mas.append(math.floor(math.log(x, 7)))

print(mas, x)

for k in range(mas[0] + 1):
    for l in range(mas[1] + 1):
        for m in range(mas[2] + 1):
            X_i = (3 * *k) * (5 * *l) * (7 * *m)#пробегаемся по всем степеням и находим все числа [1, x]
            if (X_i <= x):
                print(X_i)
