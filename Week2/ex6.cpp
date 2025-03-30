#include <iostream>
using namespace std;

bool existTwoNumber(int n,int a[],int targetSum){
    //the first element will be a[i] and go from left to right
    for(int i=0;i<n-1;i++){
        //check if the targetSum was too small or too large with the array
        if(a[i]>=targetSum || a[i]+a[n-1]<targetSum){
            return false;
        }
        //find the second element equal to targetSum-first element
        int target=targetSum-a[i];
        int left=i+1;
        int right=n-1;
        //binary search the second element with the array from i+1 to n-1
        while(left<=right){
            int mid=left+(right-left)/2;
            if(a[mid]==target){
                return true;
            }
            else if(a[mid]>target){
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
    int n,targetSum;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cin>>targetSum;
    if(existTwoNumber(n, a, targetSum)){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
    delete [] a;
    return 0;
}