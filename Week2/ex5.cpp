#include <iostream>
using namespace std;

int minLengthSubArray(int n,int* nums,int target){
    int left=0;
    int minLength=n+10;
    int sum=0;
    for(int right=0;right<n;right++){
        //find the sum of value from 0 to right;
        sum+=nums[right];
        //if sum>=target, update the new minLength and then minus the value from left index
        //this step is to find if there is any subarray with less length
        while(sum>=target){
            if(right-left+1<minLength){
                minLength=right-left+1;
            }
            sum-=nums[left];
            left++;
        }
    }
    //if the minLength still not updated, that means we not found the subarray
    if(minLength==n+10){
        return 0;
    }
    else{
        return minLength;
    }
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
    cout << minLengthSubArray(n, nums, target) << endl;
    delete [] nums;
    return 0;
}