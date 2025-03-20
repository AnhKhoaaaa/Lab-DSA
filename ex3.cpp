#include <iostream>
#include <string>
using namespace std;

void generateBinaryStrings(int n,string str){
    if(str.length()==n){
        cout<<str<<endl;
        return;
    }
    generateBinaryStrings(n,str+'0');
    generateBinaryStrings(n,str+'1');
}

int main(){
    int n;
    cin>>n;
    string str;
    generateBinaryStrings(n,str);
}