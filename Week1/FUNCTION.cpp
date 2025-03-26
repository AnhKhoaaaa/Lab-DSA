#include <iostream>
using namespace std;

int add(int a, int b)
{
    return a + b;
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        int a = rand() % 1000;
        int b = rand() % 1000;
        cout << "a = " << a << " b = " << b << " a+b = " << add(a, b) << endl;
    }
}