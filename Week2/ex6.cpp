#include <iostream>
using namespace std;

bool ExistTwoNumber(int* a,int n,int target){
    for(int i=0;i<n;i++){
        if(a[i]>=target){
            return false;
        }
        int left=i+1;
        int right=n-1;
        while(left<=right){
            int mid=left+(right-left)/2;
            if(a[mid]==target-a[i]){
                return true;
            }
            else if(a[mid]>target-a[i]){
                right=mid-1;
            }
            else{
                left=mid+1;
            }
        }
    }
    return false;
}

int main()
{
    int n,target;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cin>>target;
    cout << ExistTwoNumber(a, n, target) << endl;
    delete [] a;
    return 0;
}