#include <iostream>
using namespace std;

int minLengthSubArray(int* nums,int n,int target){
    int length=INT_MAX;
    int left=0;
    int sum=0;
    for(int right=0;right<n;right++){
        sum+=nums[right];
        while(sum>=target){
            if(length>right-left+1){
                length=right-left+1;
            }
            sum-=nums[left];
            left++;
        }
    }
    if(length==INT_MAX)
        return 0;
    else
        return length;
}

int main()
{
    //Assume that in this exercise, the user will enter the array "nums" himself.
    int n,target;
    cin >> n;
    int *nums = new int[n];
    for (int i = 0; i < n; i++){
        cin >> nums[i];
    }
    cin>>target;
    cout << minLengthSubArray(nums, n, target) << endl;
    delete [] nums;
    return 0;
}