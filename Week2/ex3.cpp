#include <iostream>
using namespace std;

int minOfRotatedArray(int n,int* a){
    int left=0;
    int right=n-1;
    while(left<right){
        //split the array in half and find the point which make the array from sorted to unsorted
        //that point is the smallest value of unrotated array.
        int mid=left+ (right-left)/2;

        //if a[left]<a[right] means that the index from left-right already sorted, it's means a[left] is minimum value.
        if(a[left]<a[right]){
            return a[left];
        }
        //if a[mid]>a[right], the smallest value that we are looking for is in the right part of the array.
        else if(a[mid]>a[right]){
            left=mid+1;
        }
        //else, that value maybe a[mid] or at the left part of the array.
        else{
            right=mid;
        }
    }
    return a[left];
}

int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << minOfRotatedArray(n, a) << endl;
    delete [] a;
    return 0;
}