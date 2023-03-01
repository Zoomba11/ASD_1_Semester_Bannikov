//сортирую "слиянием" 
//СЛОЖНОСТЬ: в лучшем случае : O(n* logn).; в худшем случае : O(n2).

#include <iostream>
using namespace std;

//сливаю массивы
void Merge(int* A, int first, int last)
{
    int middle, start, final, j;
    int* mas = new int[100];
    middle = (first + last) / 2; //ср.эл.
    start = first; //начало левой части
    final = middle + 1; //начало правой
    for (j = first; j <= last; j++) 
        if ((start <= middle) && ((final > last) || (A[start] < A[final])))
        {
            mas[j] = A[start];
            start++;
        }
        else
        {
            mas[j] = A[final];
            final++;
        }
    //возвращаю результат
    for (j = first; j <= last; j++) A[j] = mas[j];
    delete[] mas;
};

//рекурсия
void MergeSort(int* A, int first, int last)
{
    {
        if (first < last)
        {
            MergeSort(A, first, (first + last) / 2); //сортирую левую части
            MergeSort(A, (first + last) / 2 + 1, last); //сортирую правую
            Merge(A, first, last); //слияние
        }
    }
};
void main()
{
    setlocale(LC_ALL, "Rus");
    int i, n;
    int* A = new int[100];
    cout << "Размер массива > "; cin >> n;
    for (i = 1; i <= n; i++)
    {
        cout << i << " элемент > "; cin >> A[i];
    }
    MergeSort(A, 1, n); 
    cout << "Упорядоченный массив: "; 
    for (i = 1; i <= n; i++) cout << A[i] << " ";
    delete[] A;
    system("pause>>void");
}

