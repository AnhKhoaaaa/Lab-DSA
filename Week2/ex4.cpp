#include <iostream>
using namespace std;

int sumWeight(int* a,int n){
    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=a[i];
    }
    return sum;
}

int leastWeightCapacity(int* a, int n, int k){
    int min=a[n];
    int max=sumWeight(a,n);
    while(min<=max){
        int mid = min+ (max-min)/2;
        int temp=mid;
        int i=1;
        int day=1;
        while(i<=n){
            if(temp-a[i]<0){
                temp=mid;
                day++;
            }
            temp-=a[i];
            i++;
        }
        if(day>k){
            min=mid+1;
        }
        else{
            max=mid-1;
        }
    }
    return min;
}


int main()
{
    int n, k;
    cin >> n;
    int *a = new int[n+1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    cin>>k;
    cout << leastWeightCapacity(a, n, k) << endl;
    delete [] a;
    return 0;
}