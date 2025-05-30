#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

/*
adjacency matrix
directed:
9
0 0 1 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0
0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0 0
0 0 0 1 0 0 0 1 0
0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0

undirected:
9
0 0 1 0 0 1 0 0 0
0 0 0 0 0 0 1 0 0
1 0 0 0 0 0 1 0 0
0 0 0 0 1 0 0 0 0
0 0 0 1 0 1 0 0 0
1 0 0 0 1 0 0 1 0
0 1 1 0 0 0 0 0 0
0 0 0 0 0 1 0 0 1
0 0 0 0 0 0 0 1 0

adjacency list
directed:
9
2 2 5
1 6
1 6
1 4
1 5
2 3 7
0
2 2 8
0

undirected:
9
2 2 5 
1 6
2 0 6
1 4
2 3 5
3 0 4 7
2 1 2
2 5 8
1 7
*/
//1. The file contains an adjacency matrix. Read the file and output the corresponding adjacency list:
vector<vector<int>> convertMatrixToList(const string& filename){
    ifstream in(filename);
    if(!in.is_open()){
        cout<<"Can not open file "<<filename<<endl;
        return {};
    }
    vector<vector<int>> list;
    int n,x;
    in>>n;
    list.resize(n);
    for(int i=0;i<n;i++){
        list[i].push_back(0);
        for(int j=0;j<n;j++){
            in>>x;
            if(x==1){
                list[i][0]++;
                list[i].push_back(j);
            }
        }
    }
    in.close();
    return list;
}
//2. The file contains an adjacency list. Read the file and output the corresponding adjacency matrix:
vector<vector<int>> convertListToMatrix(const string& filename){
    ifstream in(filename);
    if(!in.is_open()){
        cout<<"Can not open file "<<filename<<endl;
        return {};
    }
    int n,x,j;
    in>>n;
    vector<vector<int>> matrix(n,vector<int>(n,0));
    for(int i=0;i<n;i++){
        in>>j;
        while(j--){
            in>>x;
            matrix[i][x]=1;
        }
    }
    in.close();
    return matrix;
}
//3. Implement functions to provide the following information about a given graph:
bool isDirected(const vector<vector<int>>& adjMatrix){
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=0;j<adjMatrix.size();j++){
            if(adjMatrix[i][j]==1){
                if(adjMatrix[j][i]==0) return true;
            }
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}

int countEdges(const vector<vector<int>>& adjMatrix){
    int countEdges=0;
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=0;j<adjMatrix.size();j++){
            if(adjMatrix[i][j]==1){
                countEdges++;
            }
        }
    }
    if(isDirected(adjMatrix)){
        return countEdges;
    }
    else{
        return countEdges/2;
    }
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    vector<int> isolatedList;
    for(int i=0;i<adjMatrix.size();i++){
        bool isolated=true;
        for(int j=0;j<adjMatrix.size();j++){
            if(adjMatrix[i][j]==1 || adjMatrix[j][i]==1){
                isolated=false;
            }
        }
        if(isolated){
            isolatedList.push_back(i);
        }
    }
    return isolatedList;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=0;j<adjMatrix.size();j++){
            if(j==i) continue;
            if(adjMatrix[i][j]==0) return false;
        }
    }
    return true;
}

bool isBipartite(const std::vector<std::vector<int>>& adjMatrix){
    vector<int> color(adjMatrix.size(),-1);
    for(int i=0;i<adjMatrix.size();i++){
        if(color[i]==-1){
            queue<int> q;
            q.push(i);
            color[i]=0;
            while(!q.empty()){
                int cur=q.front();
                q.pop();
                for(int j=0;j<adjMatrix.size();j++){
                    if(adjMatrix[cur][j]==1){
                        if(color[j]==-1){
                            color[j]=1-color[cur];
                            q.push(j);
                        }
                        if(color[j]==color[cur]) return false;
                    }
                }
            }
        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    vector<int> color(adjMatrix.size(),-1);
    for(int i=0;i<adjMatrix.size();i++){
        if(color[i]==-1){
            queue<int> q;
            q.push(i);
            color[i]=0;
            while(!q.empty()){
                int cur=q.front();
                q.pop();
                for(int j=0;j<adjMatrix.size();j++){
                    if(adjMatrix[cur][j]==1){
                        if(color[j]==-1){
                            color[j]=1-color[cur];
                            q.push(j);
                        }
                        if(color[j]==color[cur]) return false;
                    }
                }
            }
        }
    }
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=0;j<adjMatrix.size();j++){
            if((color[i]!=color[j])&&(adjMatrix[i][j]==0)){
                return false;
            }
        }
    }
    return true;
}
//4. Generate a base undirected graph from a given directed graph:
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    vector<vector<int>> newMatrix=adjMatrix;
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=i+1;j<adjMatrix.size();j++){
            if(newMatrix[i][j]==1 || newMatrix[j][i]==1){
                newMatrix[j][i]=1;
                newMatrix[i][j]=1;
            }
        }
    }
    return newMatrix;
}
// 5. Generate a complement graph from a given undirected graph and output its adjacency matrix (*undirected graph):
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    vector<vector<int>> complementMatrix=adjMatrix;
    for(int i=0;i<adjMatrix.size();i++){
        for(int j=i+1;j<adjMatrix.size();j++){
            complementMatrix[i][j]=1-adjMatrix[i][j];
            complementMatrix[j][i]=1-adjMatrix[j][i];
        }
    }
    return complementMatrix;
}
//6. Determine the Euler cycle from a given graph using Hierholzer’s Algorithm:
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    int n=adjMatrix.size();
    vector<int> inEdges(n,0);
    vector<int> outEdges(n,0);
    bool Directed=isDirected(adjMatrix);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjMatrix[i][j]==1){
                outEdges[i]++;
                inEdges[j]++;
            }
        }
    }
    if(Directed){
        for(int i=0;i<n;i++){
            if(inEdges[i]!=outEdges[i]) return {}; //Not a Euler cycle.
        }
    }
    else{
        for(int i=0;i<n;i++){
            if(outEdges[i]%2==1) return {}; //Not a Euler cycle.
        }
    }

    vector<vector<bool>> haveWent(n,vector<bool>(n,0)); //have went through this edge before!
    stack<int> s;
    vector<int> res;
    int start=0;
    for(int i=0;i<n;i++){
        if(outEdges[i]>0){
            start=i;
            break;
        } 
    }
    s.push(start);
    while(!s.empty()){
        int cur=s.top();
        for(int i=0;i<n;i++){
            if(adjMatrix[cur][i]==1 && haveWent[cur][i]==0){
                s.push(i);
                haveWent[cur][i]=1;
                if(!Directed){
                    haveWent[i][cur]=1;
                }
                outEdges[cur]--;
                break;
            }
        }
        if(outEdges[cur]==0){
            res.push_back(cur);
            s.pop();
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(adjMatrix[i][j]==1 && haveWent[i][j]==0) return {};
        }
    }
    reverse(res.begin(),res.end());
    return res;
}

//7. Find the spanning tree of a given graph using(*undirected graph):
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n=adjMatrix.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    vector<bool> visited(n,0);
    stack<int> s;
    s.push(start);
    visited[start]=1;
    while(!s.empty()){
        int cur=s.top();
        s.pop();
        for(int i=0;i<n;i++){
            if(adjMatrix[cur][i]==1 && !visited[i]){
                visited[i]=1;
                s.push(i);
                res[cur][i]=1;
            }
        }
    }
    return res;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n=adjMatrix.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    vector<bool> visited(n,0);
    queue<int> q;
    q.push(start);
    visited[start]=1;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        for(int i=0;i<n;i++){
            if(adjMatrix[cur][i]==1 && !visited[i]){
                q.push(i);
                visited[i]=1;
                res[cur][i]=1;
            }
        }
    }
    return res;
}

//8. Verify the connection between two vertices of a given graph:
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    int n=adjMatrix.size();
    vector<bool> visited(n,0);
    queue<int> q;
    q.push(u);
    visited[u]=1;
    while(!q.empty()){
        int m=q.size();
        for(int j=0;j<m;j++){
            int cur=q.front();
            if(cur==v) return true;
            q.pop();
            for(int i=0;i<n;i++){
                if(adjMatrix[cur][i]==1 && !visited[i]){
                    q.push(i);
                    visited[i]=1;
                }
            }
        }
    }
    if(isDirected(adjMatrix)){
        fill(visited.begin(), visited.end(), false);
        q.push(v);
        visited[v]=1;
        while(!q.empty()){
            int m=q.size();
            for(int j=0;j<m;j++){
                int cur=q.front();
                if(cur==u) return true;
                q.pop();
                for(int i=0;i<n;i++){
                    if(adjMatrix[cur][i]==1 && !visited[i]){
                        q.push(i);
                        visited[i]=1;
                    }
                }
            }
        }
    }
    return false;
}
//9. Find the shortest path between two vertices of a given graph using (*Weighted Graph):
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    int n=adjMatrix.size();
    vector<int> distance(n,INT_MAX); //save distance to each node.
    vector<int> prev(n,-1); //save the shortest way from a previous node to cur node.
    vector<bool> visited(n,0);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    //I have referenced this way to create priority_queue from Chat GPT

    distance[start]=0;
    pq.push({0,start});
    while(!pq.empty()){
        int cur=pq.top().second; //get the node from the top of queue.
        pq.pop();
        if(visited[cur]) continue;
        visited[cur]=true;
        for(int i=0;i<n;i++){
            if(adjMatrix[cur][i]!=0){
                int weight=adjMatrix[cur][i];
                if(distance[cur]+weight<distance[i]){
                    distance[i]=distance[cur]+weight;
                    prev[i]=cur;
                    pq.push({distance[i],i});
                }
            }
        }
    }
    if(distance[end]==INT_MAX) return {};
    vector<int> shortestPath;
    int i=end;
    while(i!=-1){
        shortestPath.push_back(i);
        i=prev[i];
    }
    reverse(shortestPath.begin(),shortestPath.end());
    return shortestPath;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    int n=adjMatrix.size();
    vector<int> distance(n,INT_MAX); //save distance to each node.
    vector<int> prev(n,-1); //save the shortest way from a previous node to cur node.
    distance[start]=0;
    for(int k=0;k<n-1;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(adjMatrix[i][j]!=0){
                    int weight=adjMatrix[i][j];
                    if(distance[i]+weight<distance[j]){
                        distance[j]=distance[i]+weight;
                        prev[j]=i;
                    }
                }
            }
        }
    }
    if(distance[end]==INT_MAX) return {};
    vector<int> path;
    int i=end;
    while(i!=-1){
        path.push_back(i);
        i=prev[i];
    }
    reverse(path.begin(),path.end());
    return path;
}
