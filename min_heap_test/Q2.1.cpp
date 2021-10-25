#include<iostream>
#include<algorithm>
#include<vector>
#include<limits.h>
using namespace std;

void swap(vector<pair<int,int>> &A, int smallest,int i){
    auto temp=A[smallest];
    A[smallest]=A[i];
    A[i]=temp;
}

void heapify(vector<pair<int,int>> &A, int i){
    int left=2*i+1,right=2*i+2;
    int smallest=i;
    if(left < A.size() && A[left] < A[i]) smallest=left;
    else smallest = i;
    if(right < A.size() && A[right] < A[smallest]) smallest=right;
    if(smallest != i){
        swap(A,smallest,i);
        heapify(A,smallest);
    }
}

pair<int,int> getMin(vector<pair<int,int>> &A){
    return A[0];
}

void deleteMin(vector<pair<int,int>> &A){
    if(A.size() > 0){
        A[0]=A[A.size()-1];
        A.pop_back();
        heapify(A,0);
    }
}

int find_key(vector<pair<int,int>> &A,pair<int,int> key){
    for(int i=0;i<A.size();i++){
        if(A[i]==key) return i;
    }
    return -1;
}

int parent_index(int i){
    if(i%2 == 0) return i/2-1;
    else return i/2;
}

void decreaseKey(vector<pair<int,int>> &A,pair<int,int> key, int index){
    //int index=find_key(A,key);
    if(index != -1){
        A[index] = key;
        while(index > 0 && A[parent_index(index)] > A[index]){
            swap(A,index,parent_index(index));
            index = parent_index(index);
        }
    }
}

void BuildHeap(vector<pair<int,int>> A){
     int n=A.size();
     for(int i=(n-1)/2;i>=0;i--){
         heapify(A,i);
     }
}

void insert_in_heap(vector<pair<int,int>> &A, pair<int,int> key){
    A.push_back(key);
    int index = A.size()-1;
    while(index > 0 && A[parent_index(index)] > A[index]){
        swap(A,index,parent_index(index));
        index = parent_index(index);
    }
}

/*Min Heap implements ends*/

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
        
        //set <pair<int,int>> pq;
        vector<pair<int,int>> minHeap;
        insert_in_heap(minHeap,{0,k});
        for(int i=0;i<n;i++){
            if(i==k) continue;
            insert_in_heap(minHeap,{INT_MAX,i});
            dist[i]=INT_MAX;
        }
        int Max=-1;
        
        while(minHeap.size() > 0){
            auto node=getMin(minHeap);
            deleteMin(minHeap);
            Max=max(Max,node.first);
            
            for(int i=0;i<adj[node.second].size();i++){
                //Relax
                int node_no=(adj[node.second][i]).first;
                int val_edge_weight=(adj[node.second][i]).second;
                auto itr=find_key(minHeap,{dist[node_no],node_no});
                //cout<<(*itr).first<<" "<<(*node).first<<" "<<val_edge_weight<<endl;
            if(itr!=-1 && node.first!=INT_MAX){
                if(minHeap[itr].first > (val_edge_weight+node.first)){
                    auto pare=minHeap[itr];
                    decreaseKey(minHeap,{val_edge_weight+node.first,pare.second},itr);
                    dist[pare.second]=val_edge_weight+node.first;
                    path[pare.second]=to_string(pare.second)+' '+path[node.second];
                 }
                else if(minHeap[itr].first == (val_edge_weight+node.first)){
                    string temp=to_string(minHeap[itr].second)+' '+path[node.second];
                    //cout<<temp<<" "<<path[(*itr).second]<<endl;
                    if(temp < path[minHeap[itr].second]) path[minHeap[itr].second]=temp;
                }
               }
            }
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
