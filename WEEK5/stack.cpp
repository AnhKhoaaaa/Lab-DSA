#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

struct NODE{
    int key;
    NODE* p_next;
};

struct Stack{
    NODE* top;
};

//DECLARATION
Stack* initializeStack();
void push(Stack &s, int key);
int pop(Stack &s);
int size(Stack s);
bool isEmpty(Stack s);


void freeStack(Stack* s);
void printReverse(NODE* top, ofstream& out);
void printStack(Stack s, ofstream& out);

//DEFINITION
Stack* initializeStack(){   
    Stack* s=new Stack();
    s->top=nullptr;
    return s;
}

bool isEmpty(Stack s){
    return s.top==nullptr;
}

void push(Stack &s, int key){
    NODE* newNode=new NODE();
    newNode->key=key;
    newNode->p_next=nullptr;
    if(isEmpty(s)){
        s.top=newNode;
        return;
    }
    newNode->p_next=s.top;
    s.top=newNode;
}

int pop(Stack &s){
    if(isEmpty(s)){
        return -1;
    }
    NODE* temp=s.top;
    int val=temp->key;
    s.top=s.top->p_next;
    delete temp;
    return val;
}

int size(Stack s){
    if(isEmpty(s)){
        return 0;
    }
    else{
        int count=0;
        NODE* cur=s.top;
        while(cur && ++count){
            cur=cur->p_next;
        }
        return count;
    }
}

void printReverse(NODE* top, ofstream& out) {
    if (top == nullptr) return;
    printReverse(top->p_next, out);
    out << top->key << " ";
}

void printStack(Stack s, ofstream& out){
    if(isEmpty(s)){
        out << "EMPTY" << endl;
    }
    else{
        printReverse(s.top, out);
        out << endl;
    }
}

void freeStack(Stack* s){
    if(s==nullptr){
        return;
    }
    NODE* cur=s->top;
    while(cur){
        NODE* temp=cur;
        cur=cur->p_next;
        delete temp;
    }
    delete s;
}

int main(){
    //OPEN READ FILE AND WRITE FILE
    ifstream in("input.txt");
    if(!in.is_open()){
        cout<<"Can not open file input.txt!"<<endl;
        return 0;
    }

    ofstream out("output.txt");
    if(!out.is_open()){
        cout << "Can not open file output.txt!" << endl;
        return 0;
    }

    //READ FILE, MAKE ACTION, WRITE FILE
    string action;
    string line;
    Stack* s=nullptr;
    bool inited=false;
    while(getline(in, line)){
        if(line.empty() || line.substr(0,2)=="//"){
            continue;
        }
        
        stringstream ss(line);
        ss>>action;
        if(action=="init"){
            if(!inited){
                s=initializeStack();
                inited=true;
                printStack(*s,out);
            }
            else{
                freeStack(s);
                s=initializeStack();
                printStack(*s,out);
            }
        }
        else if(action=="push"){
            int val;
            ss>>val;
            if(s==nullptr){
                out<<"Stack was not initialized yet!"<<endl;
                continue;
            }
            push(*s,val);
            printStack(*s,out);
        }
        else if(action=="pop"){
            if(s==nullptr){
                out<<"Stack was not initialized yet!"<<endl;
                continue;
            }
            pop(*s);
            printStack(*s,out);
        }
        else{
            out<<"Undefined action!"<<endl;
            continue;
        }
    }

    //CLOSE INPUT FILE AND OUTPUT FILE
    out.close();
    in.close();

    //FREE MEMORY
    freeStack(s);
    return 0;
}