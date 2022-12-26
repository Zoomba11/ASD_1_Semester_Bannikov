#selection sort . 0(n^2)
source = [4, 2, 1, 10, 5, 3, 200]
for i in range(len(source)):
    mini = min(source[i:]) #найдем минимальный элемент
    min_index = source[i:].index(mini) #находим индекс минимального элемента
    source[i + min_index] = source[i] #заменяем элемент в min_index на первый элемент
    source[i] = mini                  #заменяем местами первый элемент и минимальный
print(source)