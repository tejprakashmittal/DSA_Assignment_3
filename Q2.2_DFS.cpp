#include<iostream>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<vector>
using namespace std;

vector<pair<int,string>> global_path;

void dfs_helper(vector<vector<pair<int,int>>> &adj, int i, int dest, vector<int> visited, int weight, string path){
    visited[i] = 1;
    if(i==dest){
        //cout<<"hello";
        //cout<<path<<endl;
        global_path.push_back({weight,path});
        return;
    }
    for(int j=0;j<adj[i].size();j++){
        //if(adj[i][j].first == 2) cout<<"hello"<<endl;
        if(visited[adj[i][j].first] == 1) continue;
        int weight_sum = weight + adj[i][j].second;
        string tpath = path+ ' ' + to_string(adj[i][j].first);
        //cout<<tpath<<endl;
        dfs_helper(adj,adj[i][j].first, dest, visited, weight_sum,tpath);
    }
}

void find_path(vector<vector<pair<int,int>>> &adj, int n, int src, int dest, vector<int> visited, int k){
    visited[src]=1;
    dfs_helper(adj,src,dest,visited,0,to_string(src));
}

int main(){
    int n,m;
    cin>>n>>m;
    FILE *fromFile_f;
    string path="./file2.2.txt";
    fromFile_f = fopen(path.c_str(), "r");
    //done.resize(n,0);
    vector<vector<int>> grid(m,vector<int>(3));
    char ch;int i=0,j=0;
    while ((ch = getc(fromFile_f)) != EOF && i<m) {
        if(ch==' ') continue;
        if(ch=='\n'){
            j=0;
            i++;
            continue;
        }
        int e=ch-'0';
        grid[i][j]=e;
        j++;
    }
    int k;
    cin>>k;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<grid.size();i++){
        adj[grid[i][0]].push_back(make_pair(grid[i][1],grid[i][2]));
        adj[grid[i][1]].push_back(make_pair(grid[i][0],grid[i][2]));
    }    
    vector<int> visited(n,0);
    //find_path(adj,n,0,3,visited, k);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
                visited.resize(n,0);
                find_path(adj,n,i,j,visited, k);
        }
    }
    sort(global_path.begin(),global_path.end());
    for(int i=0;i<k;i++){
       cout<<global_path[i].second<<endl;   //<<" "<<global_path[i].first
    }

}