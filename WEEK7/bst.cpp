#include <iostream>
#include <vector>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* Search(NODE* pRoot, int x){
    if(pRoot==nullptr) return nullptr;
    if(pRoot->key==x) return pRoot;
    else if(x<pRoot->key) return Search(pRoot->p_left,x);
    else return Search(pRoot->p_right,x);
}

NODE* createNode(int data){
    NODE* newNODE=new NODE();
    newNODE->key=data;
    newNODE->p_left=nullptr;
    newNODE->p_right=nullptr;
    return newNODE;
}
void Insert(NODE* &pRoot, int x){
    if(pRoot==nullptr){
        NODE* temp=createNode(x);
        pRoot=temp;
        return;
    }
    if(x==pRoot->key){
        cout<<"Already exist a Node with this value!"<<endl;
        return;
    }
    if(x<pRoot->key){
        if(pRoot->p_left==nullptr){
            NODE* temp=createNode(x);
            pRoot->p_left=temp;
            return;
        }
        else{
            Insert(pRoot->p_left,x);
        }
    }
    if(x>pRoot->key){
        if(pRoot->p_right==nullptr){
            NODE* temp=createNode(x);
            pRoot->p_right=temp;
            return;
        }
        else{
            Insert(pRoot->p_right,x);
        }
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
        return;
    }
    else if(pRoot->key>x){
        Remove(pRoot->p_left,x);
    }
    else{
        Remove(pRoot->p_right,x);
    }
}

NODE* createTree(int a[], int n){
    NODE* pRoot=nullptr;
    for(int i=0;i<n;i++){
        Insert(pRoot,a[i]);
    }
    return pRoot;
}

void removeTree(NODE* &pRoot){
    while(pRoot!=nullptr){
        Remove(pRoot,pRoot->key);
    }
    return;
}

int Height(NODE* pRoot){
    if(pRoot==nullptr){
        return -1;
    }
    int leftHeight=Height(pRoot->p_left);
    int rightHeight=Height(pRoot->p_right);
    int maxHeight= leftHeight>=rightHeight ? leftHeight : rightHeight;
    return maxHeight+1;
}

int countLess(NODE* pRoot, int x){
    if(pRoot==nullptr) return 0;
    if(pRoot->key>=x){
        return countLess(pRoot->p_left,x);
    }
    else{
        return 1+ countLess(pRoot->p_left,x) + countLess(pRoot->p_right,x);
    }
}

int countGreater(NODE* pRoot, int x){
    if(pRoot==nullptr) return 0;
    if(pRoot->key<=x){
        return countGreater(pRoot->p_right,x);
    }
    else{
        return countGreater(pRoot->p_left,x) + countGreater(pRoot->p_right,x) + 1;
    }
}

bool InorderKeyCheck(NODE* root, NODE*& prev) {
    if (root == nullptr) return true;
    if (!InorderKeyCheck(root->p_left, prev)) return false;
    if (prev != nullptr && root->key <= prev->key){
        return false;
    }
    prev = root;
    return InorderKeyCheck(root->p_right, prev);
}
bool isBST(NODE* pRoot){
    NODE* prev=nullptr;
    return InorderKeyCheck(pRoot,prev);
}

bool FullBT(NODE* pRoot){
    if(pRoot==nullptr) return true;
    if(pRoot->p_left==nullptr && pRoot->p_right!=nullptr){
        return false;
    }
    if(pRoot->p_left!=nullptr && pRoot->p_right==nullptr){
        return false;
    }
    if(!FullBT(pRoot->p_left)){
        return false;
    }
    return FullBT(pRoot->p_right);
}
bool isFullBST(NODE* pRoot){
    if(!isBST(pRoot)) return false;
    return FullBT(pRoot);
}
