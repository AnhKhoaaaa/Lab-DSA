#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono> //Time measurement library (reference from the internet)
using namespace std;


//INSERTIONSORT.
void InsertionSort(int* a, int n);

//SELECTIONSORT.
void SelectionSort(int* a, int n);

//BUBBLE SORT.
void bubbleSort(int* a,int n);

//MERGESORT.
void merge(int* a, int left,int mid, int right);
void mergeSort(int* a,int left, int right);

//HEAPSORT
void heapify(int* a, int n,int i);
void heapSort(int* a, int n);

//QUICKSORT: HOARE PARTITION.
int hoarePartition(int* a,int left,int right);
void HoareQuickSort(int* a,int left,int right);

//RADIX SORT.
void countingSort(int* a,int n,int exp);
void radixSort(int* a,int n);

bool readFile(int& n,int*& a, string fileName);
void writeFile(int n,int* a,string fileName);
bool isSorted(int* a,int n);

#endif