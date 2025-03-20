#include <iostream>
using namespace std;

int N;
int** chessBoard;
//global count
int solution=0;

bool isSafe(int row,int col){
    for(int i=0;i<row;i++){
        //check cols
        if(chessBoard[i][col]==1){
            return false;
        }
        //check negative diagonal
        if(col-row+i>=0 && chessBoard[i][col-row+i]==1){
            return false;
        }
        //check positive diagonal
        if(col+row-i<N && chessBoard[i][col+row-i]==1){
            return false;
        }
    }
    return true;
}

void NqueensSolve( int row){
    if(row==N){
        solution++;
        return;
    }
    for(int col=0;col<N;col++){
        if(isSafe(row,col)){
            chessBoard[row][col]=1;
            NqueensSolve(row+1);
            chessBoard[row][col]=0;
        }
    }
}

int main(){
    cin>>N;
    chessBoard=new int*[N];
    for(int i=0;i<N;i++){
        chessBoard[i]=new int[N]();
    }
    NqueensSolve(0);
    cout<<"There are "<<solution<<" solutions for "<<N<<"*"<<N<<" chess board!"<<endl;

    //delete memory
    for(int i=0;i<N;i++){
        delete[] chessBoard[i];
    }
    delete[] chessBoard;
    return 0;
}