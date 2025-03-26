#include <iostream>
using namespace std;

int minOfRotatedArray(int *a, int n)
{
    int left = 0;
    int right = n - 1;
    if (a[left] < a[right])
    {
        return a[left];
    }
    while (left <= right)
    {
        int mid = (right + left) / 2;
        if (a[mid] > a[right])
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return a[left];
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
    cout << minOfRotatedArray(a, n) << endl;
    return 0;
}