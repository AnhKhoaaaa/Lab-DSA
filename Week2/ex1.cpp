#include <iostream>
using namespace std;

int linearSearch(int *a, int n, int k)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (a[i] == k)
        {
            return i;
        }
    }
    return -1;
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
    cout << linearSearch(a, n, k) << endl;
    delete [] a;
    return 0;
}