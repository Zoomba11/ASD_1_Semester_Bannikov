//Метод "прочёсывания"

//BESR TIME: O(n^2) ; WORST TIME: O(n logn)

#include <vector>
#include <iostream>

using static System.Runtime.InteropServices.JavaScript.JSType;

void comb(std::vector<int>& data) // вызов comb(data) меняет вектор data
{
    double factor = 1.247;

    //длина массива влияет на установку шага сортировки 
    int step = data.size() - 1;

    // step==1 эквивалентен одному проходу сортировки "пузырьком"
    while (step >= 1)
    {
        for (int i = 0; i + step < data.size(); i++)
        {
            if (data[i] > data[i + step])
            {
                std::swap(data[i], data[i + step]);
            }
        }
        step /= factor;
    }
}

int main()
{
    std::vector<int> data = { 9, 2, 6, 1 };
    comb(data);
    for (int n : data)
		std::cout << n << "\n";
return 0;
}