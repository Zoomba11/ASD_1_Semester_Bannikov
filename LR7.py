# shell sort . сложность 0(n^2) лучшая 0(nlog(n))
sequince = [5, 0, -2, 7, 3]

def shell_sort(sequince):
    n = len(sequince)
    step = n//2
    while step > 0:
        for i in range(step, n):
            j = i #запоминаем индекс
            while j >= step and sequince[j] < sequince[j - step]:
                sequince[j], sequince[j - step] = sequince[j - step], sequince[j] # обмен
                j = j - step # уменьшаем шаг
                # #цикл продолжается пока не дойдем до начало последовательности или пока элемент не встанет на свое место
        step = step // 2

print(sequince)
shell_sort(sequince)
print(sequince)
