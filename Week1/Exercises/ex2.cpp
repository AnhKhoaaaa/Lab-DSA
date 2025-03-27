#include <iostream>
using namespace std;

int factorial(int n)
{
    if (n == 1)
        return 1;
    return factorial(n - 1) * n;
}

int main()
{
    int n;
    cout << "Enter number: ";
    cin >> n;
    cout << factorial(n) << " ";
}