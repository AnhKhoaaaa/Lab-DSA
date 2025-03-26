#include <iostream>
using namespace std;

int linearSearchWithSentinel(int *a, int n, int k)
{
    int temp = a[n - 1];
    a[n - 1] = k;
    int i = 0;
    while (a[i] != k)
    {
        i++;
    }
    a[n - 1] = temp;
    if (i < n - 1 || a[n - 1] == k)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

int main()
{
    int n, k;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cin >> k;
    cout << linearSearchWithSentinel(a, n, k) << endl;
    return 0;
}