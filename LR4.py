#сортировка перечесывания. comb sort. сложность 0(n^2)
sequince = [4,0,-9,10,2]
def comb_sort(sequince):
    step = int(len(sequince)/1.247)
    swap = 1
    while step > 1 or swap > 0:
        #Инициализируйте обмен как false, чтобы мы могли
        #проверить, произошла ли замена или нет
        swap = False
        i = 0
        #Сравниваем все элементы с текущим разрывом
        while i + step < len(sequince):
            if sequince[i] > sequince[i+step]:
                sequince[i], sequince[i+step] = sequince[i+step], sequince[i]
                swap += 1
            i = i + 1
        if step > 1 :
            step = int(step/1.247)


print(sequince)
comb_sort(sequince)
print(sequince)

