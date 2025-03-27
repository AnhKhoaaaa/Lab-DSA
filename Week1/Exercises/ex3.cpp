#include <iostream>
#include <string>
using namespace std;

void generateBinaryStrings(int n,string str){
    if(str.length()==n){
        cout<<str<<endl; //when the length of the string equal to N, print the string
        return;
    }
    // Two recursion call to add 0 or 1 to current string, the function will add every possible
    // 0 characters and then add 1
    generateBinaryStrings(n,str+'0'); 
    generateBinaryStrings(n,str+'1');
}

int main(){
    int n;
    cin>>n;
    string str;
    generateBinaryStrings(n,str);
}