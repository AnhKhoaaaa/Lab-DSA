#include <iostream>
using namespace std;

bool isSorted(int* a, int n){
    if(n==0||n==1){
        return true;
    }
    if(a[0]>a[1]){
        return false;
    }
    return isSorted(a+1,n-1); 
    //instead of traversal the array with loop, we increase the pointer and decrease the n by recursion
    //so that we can still check all the elements of the array is sorted or not. 
}

int main(){
    int n;
    cin>>n;
    int* a=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    if(isSorted(a,n)){
        cout<<"Array is in sorted order."<<endl;
    }
    else cout<<"Array isn't in sorted order."<<endl;
    return 0;
}