#include <iostream>
using namespace std;

int hoarePartition(int* a,int left,int right){
    int i=left-1;
    int j=right+1;
    int pivot=a[left];
    while(1){
        do{
            i++;
        }while(a[i]<pivot);
        do{
            j--;
        }while(a[j]>pivot);
        if(i<j){
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
        else return j;
    }
}

void QuickSort(int* a,int left,int right){
    if(left>=right) return;
    int p=hoarePartition(a,left,right);
    QuickSort(a,left,p);
    QuickSort(a,p+1,right);
}

int binarySearch(int *a,int n,int target){
    int left=0;
    int right=n-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(a[mid]==target){
            return mid;
        }
        else if(a[mid]>target){
            right=mid-1;
        }
        else{
            left=mid+1;
        }
    }
    return -1;
}

void findTriplets(int* a, int n){
    QuickSort(a,0,n-1);
    int target;
    //decide how to print triplets
    bool first=true;
    cout<<"[";
    for(int i=0;i<n-2;i++){
        //prevent duplicate triplets
        if(i>0 && a[i]==a[i-1]){
            continue;
        }
        for(int j=i+1;j<n-1;j++){
            //prevent duplicate triplets
            if(j>i+1 && a[j]==a[j-1]){
                continue;
            }
            target=-(a[i]+a[j]);
            int k=binarySearch(a+j+1,n-j-1,target);
            if(k!=-1){
                if(first){
                    cout<<"["<<a[i]<<","<<a[j]<<","<<a[k+j+1]<<"]";
                    first=false;
                }
                else{
                    cout<<", "<<"["<<a[i]<<","<<a[j]<<","<<a[k+j+1]<<"]";
                }
            }
        }
    }
    cout<<"]";
}

int main(){
    //assume that we can use sorting algorithms in this exercise.
    //in this exercise, user have to enter the number of elements and each element's value.
    int n;
    cin>>n;
    int* a=new int[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    findTriplets(a,n);
    delete [] a;
    return 0;
}