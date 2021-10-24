#include<iostream>
#include<queue>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

vector<pair<int,string>> global_path;
vector<int> done;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<string> path(n);
        path[k]=to_string(k);
        vector<int> dist(n);
        vector<vector<pair<int,int>>> adj(n);
        for(int i=0;i<times.size();i++){
            adj[times[i][0]].push_back(make_pair(times[i][1],times[i][2]));
            adj[times[i][1]].push_back(make_pair(times[i][0],times[i][2]));
        }
        
        set <pair<int,int>> pq;
        pq.insert({0,k});
        for(int i=0;i<n;i++){
            if(i==k) continue;
            pq.insert({__INT_MAX__,i});
            dist[i]=__INT_MAX__;
        }
        int Max=-1;
        
        while(pq.empty()==false){
            auto node=pq.begin();
            Max=max(Max,(*node).first);
            
            for(int i=0;i<adj[(*node).second].size();i++){
                //Relax
                int node_no=(adj[(*node).second][i]).first;
                int val_edge_weight=(adj[(*node).second][i]).second;
                auto itr=pq.find({dist[node_no],node_no});
                //cout<<(*itr).first<<" "<<(*node).first<<" "<<val_edge_weight<<endl;
            if(itr!=pq.end() && (*node).first!=__INT_MAX__){
                if((*itr).first > (val_edge_weight+(*node).first)){
                    auto pare=*itr;
                    pq.erase(itr);
                    pq.insert({val_edge_weight+(*node).first,pare.second});
                    dist[pare.second]=val_edge_weight+(*node).first;
                    path[pare.second]=path[(*node).second]+' '+to_string(pare.second);
                    if(done[pare.second]==0)
                    global_path.push_back({dist[pare.second],path[pare.second]});
                 }
                else if((*itr).first == (val_edge_weight+(*node).first)){
                    string temp=path[(*node).second]+' '+to_string((*itr).second);
                    //cout<<temp<<" "<<path[(*itr).second]<<endl;
                    if(temp < path[(*itr).second]){
                        path[(*itr).second]=temp;
                        if(done[(*itr).second]==0)
                        global_path.push_back({dist[(*itr).second],temp});
                    }
                }
               }
            }
            pq.erase(node);
        }
        
        for(int h=0;h<path.size();h++){
            if(h==k) continue;
            //cout<<path[h]<<endl;
        }
        
        if(Max==__INT_MAX__) Max=-1;
        return Max;
    }
};

void all_pairs( vector<vector<int>> &times,int n){
    Solution obj;

    for(int i=0;i<n;i++){
        done[i]=1;
        obj.networkDelayTime(times,n,i);
    }
    sort(global_path.begin(),global_path.end());
    for(int i=0;i<3;i++){
        cout<<global_path[i].second<<endl;   //<<" "<<global_path[i].first
    }
    //obj.networkDelayTime(times,4,3);
}

int main(){
    int n,m;
    cin>>n>>m;
    FILE *fromFile_f;
    string path="./file2.2.txt";
    fromFile_f = fopen(path.c_str(), "r");
    done.resize(n,0);
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
    all_pairs(grid,n);
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<3;j++){
    //         cout<<grid[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}