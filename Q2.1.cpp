#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<string> path(n);
        path[k]=to_string(k);
        vector<vector<pair<int,int>>> adj(n);
        vector<int> dist(n);
        for(int i=0;i<times.size();i++){
            adj[times[i][0]].push_back(make_pair(times[i][1],times[i][2]));
            adj[times[i][1]].push_back(make_pair(times[i][0],times[i][2]));
        }
        
        set <pair<int,int>> pq;
        pq.insert({0,k});
        for(int i=0;i<n;i++){
            if(i==k) continue;
            pq.insert({INT_MAX,i});
            dist[i]=INT_MAX;
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
            if(itr!=pq.end() && (*node).first!=INT_MAX){
                if((*itr).first > (val_edge_weight+(*node).first)){
                    auto pare=*itr;
                    pq.erase(itr);
                    pq.insert({val_edge_weight+(*node).first,pare.second});
                    dist[pare.second]=val_edge_weight+(*node).first;
                    path[pare.second]=to_string(pare.second)+' '+path[(*node).second];
                 }
                else if((*itr).first == (val_edge_weight+(*node).first)){
                    string temp=to_string((*itr).second)+' '+path[(*node).second];
                    //cout<<temp<<" "<<path[(*itr).second]<<endl;
                    if(temp < path[(*itr).second]) path[(*itr).second]=temp;
                }
               }
            }
            pq.erase(node);
        }
        
        for(int h=0;h<path.size();h++){
            if(h==k) continue;
            cout<<path[h]<<endl;
        }
        
        if(Max==INT_MAX) Max=-1;
        return Max;
    }
};

int main(){
    int n,m,k;
   // cin>>n>>m;(n,vector<int>(3)); 
    vector<vector<int>> times={{0,1,5},{1,2,5},{2,8 ,5},{8, 9, 5},{0, 4, 15},{4, 9, 5},{0, 3, 5},{0, 5, 5},{0, 6, 5},{0, 7, 5}};    //={{0,1,1},{1,3,2},{0,3,3},{0,2,2},{2,3,1}};
    // for(int i=0;i<n;i++){
    //     cin>>times[i][0]>>times[i][1]>>times[i][2];
    // }
    // cin>>k;
    Solution obj;
    obj.networkDelayTime(times,10,0);
    return 0;
}
