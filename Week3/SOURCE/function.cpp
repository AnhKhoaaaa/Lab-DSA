#include "function.h"
long long count_compare=0;

//INSERTIONSORT.
// void InsertionSort(int* a, int n){
//     for(int i=1;++count_compare && i<n;i++){
//         int cur=a[i];
//         int j=i-1;
//         while(++count_compare && j>=0 && ++count_compare && a[j]>cur){
//             a[j+1]=a[j];
//             j--;
//         }
//         a[j+1]=cur;
//     }
// }

void InsertionSort(int* a, int n){
    for(int i=1;i<n;i++){
        int cur=a[i];
        int j=i-1;
        while(j>=0 && a[j]>cur){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=cur;
    }
}

//SELECTIONSORT.
// void SelectionSort(int* a, int n){
//     for(int i=0;++count_compare && i<n;i++){
//         int min=i;
//         for(int j=i+1;++count_compare && j<n;j++){
//             count_compare++;
//             if(a[j]<a[min]){
//                 min=j;
//             }
//         }
//         int temp=a[i];
//         a[i]=a[min];
//         a[min]=temp;
//     }
// }

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

//BUBBLE SORT.
// void bubbleSort(int* a,int n){
//     for(int i=0;++count_compare && i<n-1;i++){
//         for(int j=0;++count_compare && j<n-i-1;j++){
//             count_compare++;
//             if(a[j]>a[j+1]){
//                 int temp=a[j+1];
//                 a[j+1]=a[j];
//                 a[j]=temp;
//             }
//         }
//     }
// }

void bubbleSort(int* a,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                int temp=a[j+1];
                a[j+1]=a[j];
                a[j]=temp;
            }
        }
    }
}

//MERGESORT.
// void merge(int* a, int left,int mid, int right){
//     int* temp=new int[right-left+1];
//     int i=left;
//     int j=mid+1;
//     int k=0;
//     while(++count_compare && i<=mid && ++count_compare &&  j<=right){
//         count_compare++;
//         if(a[i]<a[j]){
//             temp[k]=a[i];
//             k++;
//             i++;
//         }
//         else{
//             temp[k]=a[j];
//             k++;
//             j++;
//         }
//     }
//     while(++count_compare && i<=mid){
//         temp[k]=a[i];
//         k++;
//         i++;
//     }
//     while(++count_compare && j<=right){
//         temp[k]=a[j];
//         k++;
//         j++;
//     }
//     for(int i=left;++count_compare && i<=right;i++){
//         a[i]=temp[i-left];
//     }
//     delete[] temp;
// }
// void mergeSort(int* a,int left, int right){
//     if(++count_compare && left>=right){
//         return;
//     }
//     int mid=left+(right-left) /2;
//     mergeSort(a,left,mid);
//     mergeSort(a,mid+1,right);
//     merge(a,left,mid,right);
// }

void merge(int* a, int left,int mid, int right){
    int* temp=new int[right-left+1];
    int i=left;
    int j=mid+1;
    int k=0;
    while(i<=mid && j<=right){
        if(a[i]<a[j]){
            temp[k]=a[i];
            k++;
            i++;
        }
        else{
            temp[k]=a[j];
            k++;
            j++;
        }
    }
    while(i<=mid){
        temp[k]=a[i];
        k++;
        i++;
    }
    while(j<=right){
        temp[k]=a[j];
        k++;
        j++;
    }
    for(int i=left;i<=right;i++){
        a[i]=temp[i-left];
    }
    delete[] temp;
}
void mergeSort(int* a,int left, int right){
    if(left>=right){
        return;
    }
    int mid=left+(right-left) /2;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid,right);
}

//HEAPSORT.
// void heapify(int* a, int n,int i){
//     int largest=i;
//     int left=2*i+1;
//     int right=2*i+2;
//     if(++count_compare && left<n && ++count_compare &&  a[left]>a[largest]){
//         largest=left;
//     }
//     if(++count_compare && right<n && ++count_compare &&  a[right]>a[largest]){
//         largest=right;
//     }
//     if(++count_compare && largest != i){
//         int temp=a[largest];
//         a[largest]=a[i];
//         a[i]=temp;
//         heapify(a,n,largest);  
//     }
// }
// void heapSort(int* a, int n){
//     for(int i=n/2-1;++count_compare && i>=0;i--){
//         heapify(a,n,i);
//     }
//     for(int i=n-1;++count_compare && i>0;i--){
//         int temp=a[i];
//         a[i]=a[0];
//         a[0]=temp;
//         heapify(a,i,0);
//     }
// }

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

//QUICKSORT: HOARE PARTITION.
// int hoarePartition(int* a,int left,int right){
//     int i=left-1;
//     int j=right+1;
//     int pivot=a[left];
//     while(1){
//         do{
//             i++;
//         }while(++count_compare && a[i]<pivot);
//         do{
//             j--;
//         }while(++count_compare && a[j]>pivot);
//         if(++count_compare && i<j){
//             int temp=a[i];
//             a[i]=a[j];
//             a[j]=temp;
//         }
//         else return j;
//     }
// }
// void HoareQuickSort(int* a,int left,int right){
//     if(++count_compare && left>=right) return;
//     int p=hoarePartition(a,left,right);
//     HoareQuickSort(a,left,p);
//     HoareQuickSort(a,p+1,right);
// }

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

//RADIX SORT.
// void countingSort(int* a,int n,int exp){
//     int count[10]={0};
//     int* output=new int[n];
//     for(int i=0;++count_compare && i<n;i++){
//         count[(a[i]/exp)%10]++;
//     }
//     for(int i=1;++count_compare && i<10;i++){
//         count[i]+=count[i-1];
//     }
//     for(int i=n-1;++count_compare && i>=0;i--){
//         output[count[(a[i]/exp)%10]-1]=a[i];
//         count[(a[i]/exp)%10]--;
//     }
//     for(int i=0;++count_compare && i<n;i++){
//         a[i]=output[i];
//     }
//     delete[] output;
// }
// void radixSort(int* a,int n){
//     int max=a[0];
//     for(int i=1;++count_compare && i<n;i++){
//         if(++count_compare && a[i]>max){
//             max=a[i];
//         }
//     }
//     for(int i=1;++count_compare && max/i>0;i*=10){
//         countingSort(a,n,i);
//     }
// }

void countingSort(int* a,int n,int exp){
    int count[10]={0};
    int* output=new int[n];
    for(int i=0;i<n;i++){
        count[(a[i]/exp)%10]++;
    }
    for(int i=1;i<10;i++){
        count[i]+=count[i-1];
    }
    for(int i=n-1;i>=0;i--){
        output[count[(a[i]/exp)%10]-1]=a[i];
        count[(a[i]/exp)%10]--;
    }
    for(int i=0;i<n;i++){
        a[i]=output[i];
    }
    delete[] output;
}
void radixSort(int* a,int n){
    int max=a[0];
    for(int i=1;i<n;i++){
        if(a[i]>max){
            max=a[i];
        }
    }
    for(int i=1;max/i>0;i*=10){
        countingSort(a,n,i);
    }
}

bool readFile(int& n,int*& a, string fileName){
    ifstream fs(fileName);
    if(!fs.is_open()){
        cout<<"Error in open input file!"<<endl;
        return false;
    }
    fs>>n;
    fs.ignore();
    a=new int[n];
    for(int i=0;i<n;i++){
        fs>>a[i];
    }
    fs.close();
    return true;
}

void writeFile(int n,int* a,string fileName){
    ofstream fs(fileName);
    if(!fs.is_open()){
        cout<<"Error in open output file!"<<endl;
    }
    fs<<n<<endl;
    for(int i=0;i<n;i++){
        fs<<a[i]<<" ";
    }

    fs.close();
}

bool isSorted(int* a,int n){
    for(int i=0;i<n-1;i++){
        if(a[i]>a[i+1]){
            return false;
        }
    }
    return true;
}