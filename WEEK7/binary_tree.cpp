#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE{
    int key;
    NODE* left;
    NODE* right;
};

NODE* createNode(int data){
    NODE* newNODE=new NODE();
    newNODE->key=data;
    newNODE->left=nullptr;
    newNODE->right=nullptr;
    return newNODE;
}

// Traversal aproach not using side func.
// Pre-order.
// vector<int> NLR(NODE* pRoot){
//     if(pRoot==nullptr){
//         return {};
//     }
//     vector<int> result;
//     result.push_back(pRoot->key);
//     vector<int> leftKey=NLR(pRoot->left);
//     vector<int> rightKey=NLR(pRoot->right);
//     for(int i=0;i<leftKey.size();i++){
//         result.push_back(leftKey[i]);
//     }
//     for(int i=0;i<rightKey.size();i++){
//         result.push_back(rightKey[i]);
//     }
//     return result;
// }
// In-order.
// vector<int> LNR(NODE* pRoot){
//     if(pRoot==nullptr){
//         return {};
//     }
//     vector<int> leftKey=LNR(pRoot->left);
//     vector<int> rightKey=LNR(pRoot->right);
//     vector<int> result;
//     for(int i=0;i<leftKey.size();i++){
//         result.push_back(leftKey[i]);
//     }
//     result.push_back(pRoot->key);
//     for(int i=0;i<rightKey.size();i++){
//         result.push_back(rightKey[i]);
//     }
//     return result;
// }
// Post-order.
// vector<int>LRN(NODE* pRoot){
//     if(pRoot==nullptr) return {};
//     vector<int> leftKey=LRN(pRoot->left);
//     vector<int> rightKey=LRN(pRoot->right);
//     vector<int> result;
//     for(int x:leftKey){
//         result.push_back(x);
//     }
//     for(int x:rightKey){
//         result.push_back(x);
//     }
//     result.push_back(pRoot->key);
//     return result;
// }

//Traversal aproach using side func with less memory need.
//Pre-order.
void goNLR(vector<int>& res, NODE* pRoot){
    if(pRoot==nullptr) return;
    res.push_back(pRoot->key);
    goNLR(res,pRoot->left);
    goNLR(res,pRoot->right);
}
vector<int> NLR(NODE* pRoot){
    if(pRoot==nullptr) return {};
    vector <int> result;
    goNLR(result,pRoot);
    return result;
}
//In-order.
void goLNR(vector<int>& res,NODE* pRoot){
    if(pRoot==nullptr) return;
    goLNR(res,pRoot->left);
    res.push_back(pRoot->key);
    goLNR(res,pRoot->right);
}
vector<int> LNR(NODE* pRoot){
    if(pRoot==nullptr) return{};
    vector<int> result;
    goLNR(result,pRoot);
    return result;
}
//Post-order.
void goLRN(vector<int>& res,NODE* pRoot){
    if(pRoot==nullptr) return;
    goLRN(res,pRoot->left);
    goLRN(res,pRoot->right);
    res.push_back(pRoot->key);
}
vector<int> LRN(NODE* pRoot){
    if(pRoot==nullptr) return {};
    vector<int> result;
    goLRN(result,pRoot);
    return result;
}

//BFS using queue:
vector<vector<int>> LevelOrder(NODE* pRoot){
    if(pRoot==nullptr) return {};
    queue<NODE*> q;
    vector<vector<int>>result;
    q.push(pRoot);
    while(!q.empty()){
        int levelNums=q.size();
        vector<int> curLevel;
        for(int i=0;i<levelNums;i++){
            NODE* cur=q.front();
            curLevel.push_back(cur->key);
            q.pop();
            if(cur->left!=nullptr){
                q.push(cur->left);
            }
            if(cur->right!=nullptr){
                q.push(cur->right);
            }
        }
        result.push_back(curLevel);
    }
    return result;
}

int countNode(NODE* pRoot){
    if(pRoot==nullptr) return 0;
    int count=1;
    int countLeft=countNode(pRoot->left);
    int countRight=countNode(pRoot->right);
    count+=countLeft+countRight;
    return count;
}

int sumNode(NODE* pRoot){
    if(pRoot==nullptr) return 0;
    int sum=pRoot->key;
    int sumLeft=sumNode(pRoot->left);
    int sumRight=sumNode(pRoot->right);
    sum+=sumLeft+sumRight;
    return sum;
}

NODE* findNode(NODE* pRoot, int value){
    if(pRoot==nullptr) return nullptr;
    if(pRoot->key==value) return pRoot;
    NODE* findLeft=findNode(pRoot->left,value);
    if(findLeft!= nullptr) return findLeft;
    return findNode(pRoot->right,value);
}
int findHeight(NODE* pRoot){
    if(pRoot==nullptr) return -1;
    int leftHeight=findHeight(pRoot->left);
    int rightHeight=findHeight(pRoot->right);
    int maxHeight = leftHeight>=rightHeight ? leftHeight : rightHeight;
    return maxHeight+1;
}
int heightNode(NODE* pRoot, int value){
    NODE* aimNode=findNode(pRoot,value);
    if(aimNode==nullptr) return -1;
    return findHeight(aimNode);
}

int Level(NODE* pRoot, NODE* p){
    if(pRoot==nullptr) return -1;
    if(pRoot==p) return 0;
    int leftLevel=Level(pRoot->left,p);
    if(leftLevel!=-1) return leftLevel+1;
    int rightLevel=Level(pRoot->right,p);
    if(rightLevel!=-1) return rightLevel+1;
    return -1;
}

int countLeaf(NODE* pRoot){
    if(pRoot==nullptr) return 0;
    int leftLeaf=countLeaf(pRoot->left);
    int rightLeaf=countLeaf(pRoot->right);
    if(leftLeaf==0&&rightLeaf==0){
        return 1;
    }
    return leftLeaf+rightLeaf;
}