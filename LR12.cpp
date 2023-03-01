//внешн.многофазн.
//подключаю библиотеку
#include <fstream>
#include <iostream>

using System;
using System.Diagnostics.Metrics;
using System.Drawing;

int main()
{

    std::ifstream in, in1, in2; // создаю объекты файлового ввода
    std::ofstream out, out1, out2; //создаю объекты файлового вывода

    int a, b = 0;
    //кол-во чисел
    int size = 0;
    int countA, countB, count = 0;
    bool flag = true;
    bool Afull, Bfull = true;

	in.open("input.txt");
	out.open("result.txt");

    while (in >> a)
	{
		out << a << " ";
    size++;
}
	
	in.close();
	out.close();
/*длина серий:
В исходном файле 1,
после первого шага 2, после второго – 4,
после третьего – 8, после k -го шага – 2k*/
for (int partSize = 1; partSize < size; partSize *= 2)
{
		//первоначальный файл разбивается на 2 вспомогательных
		in.open("result.txt");
    out1.open("A.txt");
    out2.open("B.txt");
    count = 0;
    while (in >> a)
		{
    count++;
    if (flag)
        out1 << a << " ";
    else
        out2 << a << " ";

    if (count == partSize)
    {
        count = 0;
        flag = !flag;
    }
}
		in.close();
out1.close();
out2.close();

in1.open("A.txt");
in2.open("B.txt");
		out.open("result.txt");

//вспомогательные сливаются, одиночные образуют пары
if (in1 >> a)
    Afull = true;
else
    Afull = false;

if (in2 >> b)
    Bfull = true;
else
    Bfull = false;
//пары переходят в четверки.
for (int i = 0; i < size; i += 2 * partSize)
{
    countA = 0; countB = 0;
    while (countA < partSize && Afull && countB < partSize && Bfull)
        if (a < b)
        {
					out << a << " ";
            if (in1 >> a)
                Afull = true;
            else
                Afull = false;
            countA++;
        }
        else
        {
					out << b << " ";
            if (in2 >> b)
                Bfull = true;
            else
                Bfull = false;
            countB++;
        }
    //Потом, сливаю четверки в восьмерки и т.д.,
    //каждый раз удваиваю длину до тех пор, пока файл не будет упорядочен целиком
    while (countA < partSize && Afull)
    {
				out << a << " ";
        if (in1 >> a)
            Afull = true;
        else
            Afull = false;
        countA++;
    }
    while (countB < partSize && Bfull)
    {
				out << b << " ";
        if (in2 >> b)
            Bfull = true;
        else
            Bfull = false;
        countB++;
    }

}

in1.close();
in2.close();
		out.close();
remove("A.txt");
remove("B.txt");
	}
	return 0;
}
