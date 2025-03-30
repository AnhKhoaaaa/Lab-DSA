#include <iostream>
using namespace std;

int sumWeight(int n, int* weight){
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=weight[i];
    }
    return sum;
}

int leastWeightCapacity(int n,int* weight,int days){
    //the least weight we are looking must between the largest weight of the array and the total weight
    //so we will use binary search in between that two value
    int min=weight[n];
    int max=sumWeight(n,weight);
    while(min<=max){
        int i=1;
        int dayCount=1;
        int mid=min+(max-min)/2;
        int temp=mid;
        //this loop will find how many days it need to shipped all packages
        while(i<=n){
            if(temp-weight[i]<0){
                dayCount++;
                temp=mid;
            }
            temp-=weight[i];
            i++;
        }
        //if dayCount more than the giving days, increase the min to mid+1
        if(dayCount>days){
            min=mid+1;
        }
        //if dayCount is equal to or less than, set max value to mid-1
        else{
            max=mid-1;
        }
    }
    return min;
}


int main(){
    //the array is 1-based and assume that the array had been sorted in ascending order
    int n, days;
    cin >> n;
    int *weight = new int[n+1];
    for (int i = 1; i <= n; i++)
    {
        cin >> weight[i];
    }
    cin>>days;
    cout << leastWeightCapacity(n, weight, days) << endl;
    delete [] weight;
    return 0;
}