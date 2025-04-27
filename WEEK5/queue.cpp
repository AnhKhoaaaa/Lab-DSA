#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct NODE{
    int key;
    NODE* p_next;
};

struct Queue{
    NODE* head;
    NODE* tail;
};

//DECLARATION
Queue* initializeQueue();
void enqueue(Queue &q, int key);
int dequeue(Queue &q);
int size(Queue q);
bool isEmpty(Queue q);

void printQueue(Queue q, ofstream& out);
void freeQueue(Queue* q);

//DEFINITION
Queue* initializeQueue(){
    Queue* q=new Queue();
    q->head=nullptr;
    q->tail=nullptr;
    return q;
}

bool isEmpty(Queue q){
    return q.head==nullptr;
}

void enqueue(Queue &q, int key){
    NODE* newNode=new NODE();
    newNode->key=key;
    newNode->p_next=nullptr;
    if(isEmpty(q)){
        q.head=newNode;
        q.tail=newNode;
        return;
    }
    q.tail->p_next=newNode;
    q.tail=newNode;
}

int dequeue(Queue &q){
    if(isEmpty(q)){
        return -1;
    }
    NODE* temp=q.head;
    q.head=q.head->p_next;
    if(q.head==nullptr){
        q.tail=nullptr;
    }
    int val=temp->key;
    delete temp;
    return val;
}

int size(Queue q){
    if(isEmpty(q)){
        return 0;
    }
    NODE* cur=q.head;
    int count=0;
    while(cur && ++count){
        cur=cur->p_next;
    }
    return count;
}

void printQueue(Queue q, ofstream& out){
    if(isEmpty(q)){
        out<<"EMPTY"<<endl;
        return;
    }
    NODE* cur=q.head;
    while(cur){
        out<<cur->key<<" ";
        cur=cur->p_next;
    }
    out<<endl;
}

void freeQueue(Queue* q){
    if(q==nullptr){
        return;
    }
    NODE* cur=q->head;
    while(cur){
        NODE* temp=cur;
        cur=cur->p_next;
        delete temp;
    }
    delete q;
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
    Queue* q=nullptr;
    string action;
    string line;
    bool inited=false;
    while(getline(in,line)){
        if(line.empty() || line.substr(0,2)=="//"){
            continue;
        }
        stringstream ss(line);
        ss>>action;
        if(action=="init"){
            if(!inited){
                q=initializeQueue();
                inited=true;
                printQueue(*q,out);
            }
            else{
                freeQueue(q);
                q=initializeQueue();
                printQueue(*q,out);
            }
        }
        else if(action=="enqueue"){
            int val;
            ss>>val;
            if(q==nullptr){
                out<<"Queue was not initialized yet!"<<endl;
                continue;
            }
            enqueue(*q,val);
            printQueue(*q,out);
        }
        else if(action=="dequeue"){
            if(q==nullptr){
                out<<"Queue was not initialized yet!"<<endl;
                continue;
            }
            dequeue(*q);
            printQueue(*q,out);
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
    freeQueue(q);
    return 0;
}