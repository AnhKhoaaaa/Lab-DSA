#include <iostream>
#include <vector>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data){
    NODE* newNODE=new NODE();
    newNODE->key=data;
    newNODE->p_left=nullptr;
    newNODE->p_right=nullptr;
    newNODE->height=0;
    return newNODE;
}

int getHeight(NODE* node) {
    if (node==nullptr){
        return -1;
    }
    return node->height;
}
int getBalanceFactor(NODE* node) {
    if(node==nullptr){
        return 0;
    }
    return getHeight(node->p_left)-getHeight(node->p_right);
}
void updateHeight(NODE* node) {
    if (node != nullptr) {
        int maxHeight=(getHeight(node->p_left)>=getHeight(node->p_right)) ? getHeight(node->p_left) : getHeight(node->p_right);
        node->height=1+maxHeight;
    }
}
NODE* rotateRight(NODE* b) { //b is the imbalance node.
    NODE* a = b->p_left;
    NODE* c = a->p_right;
    a->p_right = b;
    b->p_left = c;
    updateHeight(b);
    updateHeight(a);
    return a;
}
NODE* rotateLeft(NODE* b) { //b is the imbalance node.
    NODE* a = b->p_right;
    NODE* c = a->p_left;
    a->p_left = b;
    b->p_right = c;
    updateHeight(b);
    updateHeight(a);
    return a;
}
void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        NODE* temp=createNode(x);
        pRoot=temp;
        return;
    }
    if(x==pRoot->key){
        cout<<"Already exist a Node with this value!"<<endl;
        return;
    }
    else if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    }
    else{
        Insert(pRoot->p_right, x);
    }
    updateHeight(pRoot);

    //Rebalance the tree.
    int balanceFactor = getBalanceFactor(pRoot);
    if (balanceFactor > 1 && x < pRoot->p_left->key) { //left left case
        pRoot = rotateRight(pRoot);
    }
    else if (balanceFactor < -1 && x > pRoot->p_right->key) { // right right case
        pRoot = rotateLeft(pRoot);
    }
    else if (balanceFactor > 1 && x > pRoot->p_left->key) { // left right case
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balanceFactor < -1 && x < pRoot->p_right->key) { //right left case
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

void Remove(NODE* &pRoot, int x){
    if(pRoot==nullptr){
        cout<<"Can not find Node with given value: "<<x<<endl;
        return;
    }
    if(pRoot->key==x){
        if(pRoot->p_left==nullptr && pRoot->p_right==nullptr){
            NODE* temp=pRoot;
            pRoot=nullptr;
            delete temp;
        }
        else if(pRoot->p_left!=nullptr && pRoot->p_right==nullptr){
            NODE* temp=pRoot;
            pRoot=pRoot->p_left;
            delete temp;
        }
        else if(pRoot->p_left==nullptr && pRoot->p_right!=nullptr){
            NODE* temp=pRoot;
            pRoot=pRoot->p_right;
            delete temp;
        }
        else{
            NODE* rightMostNode=pRoot->p_left;
            while(rightMostNode->p_right!=nullptr){
                rightMostNode=rightMostNode->p_right;
            }
            pRoot->key=rightMostNode->key;
            Remove(pRoot->p_left,rightMostNode->key);
        }
    }
    else if(pRoot->key>x){
        Remove(pRoot->p_left,x);
    }
    else{
        Remove(pRoot->p_right,x);
    }
    if(pRoot==nullptr) return; //delete a leaf node.
    
    //Rebalance the tree.
    updateHeight(pRoot);
    int balanceFactor=getBalanceFactor(pRoot);
    if (balanceFactor > 1 && x < pRoot->p_left->key) { //left left case
        pRoot = rotateRight(pRoot);
    }
    else if (balanceFactor < -1 && x > pRoot->p_right->key) { // right right case
        pRoot = rotateLeft(pRoot);
    }
    else if (balanceFactor > 1 && x > pRoot->p_left->key) { // left right case
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    else if (balanceFactor < -1 && x < pRoot->p_right->key) { //right left case
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

bool isAVL(NODE* pRoot){
    if(pRoot==nullptr) return true;
    if(getBalanceFactor(pRoot)>1 ||getBalanceFactor(pRoot)<-1) return false;
    if(!isAVL(pRoot->p_left)) return false;
    return isAVL(pRoot->p_right);
}