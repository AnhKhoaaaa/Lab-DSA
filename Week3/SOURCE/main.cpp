#include "function.h"

int main(int argc, char* argv[]){
    //Read input argument
    if(argc!=7){
        cout<<"Unidentify command!"<<endl;
        cout<<"Try again, format: main.exe -a [sorting type] -i [input file name] -o [output file name]"<<endl;
        return 0;
    }
    string sortType,inputFile,outputFile;
    for(int i=1;i<argc;i++){
        string arg=argv[i];
        if(arg=="-a" && i+1<argc){
            sortType=argv[++i];
        }
        if(arg=="-i" && i+1<argc){
            inputFile=argv[++i];
        }
        if(arg=="-o" && i+1<argc){
            outputFile=argv[++i];
        }
    }

    //create new array and read data from file
    int n;
    int* a;
    if(!readFile(n,a,inputFile)){
        delete[] a;
        return 0;
    }

    long long count_compare=0;//count the number of comparison in algorithms

    //start time record
    auto start = chrono::high_resolution_clock::now();
    //decide which algorithms to use
    if(sortType=="insertion-sort"){
        InsertionSort(a,n);
    }
    else if(sortType=="selection-sort"){
        SelectionSort(a,n);
    }
    else if(sortType=="bubble-sort"){
        bubbleSort(a,n);
    }
    else if(sortType=="heap-sort"){
        heapSort(a,n);
    }
    else if(sortType=="merge-sort"){
        mergeSort(a,0,n-1);
    }
    else if(sortType=="quick-sort"){
        HoareQuickSort(a,0,n-1);
    }
    else if(sortType=="radix-sort"){
        radixSort(a,n);
    }
    else{
        cout<<"Unvalid sort type!"<<endl;
        delete[] a;
        return 0;
    }
    //end the time record
    auto end = chrono::high_resolution_clock::now();
    //calculate time consume
    double elapsed = chrono::duration<double, milli>(end - start).count();
    cout<<"Time: "<<elapsed<<endl;
    if(count_compare!=0)
        cout<<"Numbers of comparison: "<<count_compare<<endl;

    //check if the array was sorted
    if(isSorted(a,n)){
        cout<<"Sorted!"<<endl;
    }
    else{
        cout<<"Not sorted!"<<endl;
    }

    //write data into file.
    writeFile(n,a,outputFile);
    delete[] a;
    return 0;
}