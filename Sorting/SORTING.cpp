#include <iostream>
using namespace std;

void InsertionSort(int* a, int n){
    for(int i=1;i<n;i++){
        int cur=a[i];
        int j=i-1;
        while(j>=0 && a[j]>cur){
            a[j+1]=a[j];
            j=j-1;
        }
        a[j+1]=cur;
    }
}

void SelectionSort(int* a, int n){
    for(int i=0;i<n;i++){
        int min=i;
        for(int j=i;j<n;j++){
            if(a[j]<a[min]){
                min=j;
            }
        }
        int temp=a[i];
        a[i]=a[min];
        a[min]=temp;
    }
}

//MERGESORT
void merge(int* a, int left,int mid, int right){
 //B1: copy nội dung từ left-mid vào array 1; từ mid+1 tới right vào array 2
 //B2: vòng lặp chạy với điều kiện: i<size array1 và j<size array2
 //B3: trong vòng lặp này, so sánh từng phần tử tại i và j, nếu i bé hơn thì bỏ vào a[left], sau đó i++, left++; tương tự với j
 //B4: sau khi kết thúc vòng lặp trên, gán các phần tử còn thừa của array 1 và array 2 vào a[left]; tiếp tục left++; 
}

void mergeSort(int* a,int left, int right){
    if(left>=right){
        return;
    }
    int mid=(left+right) /2;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid,right);
}

//HEAPSORT
void heapify(int* a, int n,int i){
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    if(left<n && a[left]>a[largest]){
        largest=left;
    }
    if(right<n && a[right]>a[largest]){
        largest=right;
    }
    if(largest != i){
        int temp=a[largest];
        a[largest]=a[i];
        a[i]=temp;
        heapify(a,n,largest);  
    }
}

void heapSort(int* a, int n){
    for(int i=n/2-1;i>=0;i--){
        heapify(a,n,i);
    }
    for(int i=n-1;i>0;i--){
        int temp=a[i];
        a[i]=a[0];
        a[0]=temp;

        heapify(a,i,0);
    }
}

//QUICKSORT: LOMUTO PARTITION
int partition(int* a,int left, int right){
    int i=left-1, j=left;
    int pivot=right;
    while(j<right){
        if(a[j]<=a[pivot]){
            i++;
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
        j++;
    }
    i++;
    int temp=a[i];
    a[i]=a[pivot];
    a[pivot]=temp;
    return i;
}

void quickSort(int* a,int left,int right){
    if(left>=right) return;
    int mid=partition(a,left,right);
    quickSort(a,left,mid-1);
    quickSort(a,mid+1,right);
}

//QUICKSORT: HOARE PARTITION
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

void HoareQuickSort(int* a,int left,int right){
    if(left>=right) return;
    int p=hoarePartition(a,left,right);
    HoareQuickSort(a,left,p);
    HoareQuickSort(a,p+1,right);
}


int main(){
    int n;
    cin>>n;
    srand(time(NULL));
    int *a=new int[n];
    for(int i=0;i<n;i++){
        a[i]=rand() % 1000;
    }
    HoareQuickSort(a,0,n-1);
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
}