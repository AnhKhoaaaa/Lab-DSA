#include <iostream>
using namespace std;

void towerOfHanoi(int n,char from, char to, char aux){
    //the main idea is to put n-1 disk to the aux-nod and then put the n disk to to-nod,
    //we divide the problem to smaller problem by recursion and solve it from 1 disk problem to n disks problem
    if(n==1){
        cout<<"Moved disk 1 from "<<from<<" to "<<to<<endl;
        return;
    }
    towerOfHanoi(n-1,from,aux,to);
    cout<<"Moved disk "<<n<<" from "<<from<<" to "<<to<<endl;
    towerOfHanoi(n-1,aux,to,from);
}

int main(){
    int n;
    cin>>n;
    char from='A';
    char to='C';
    char aux='B';
    towerOfHanoi(n,from,to,aux);
    return 0;
}