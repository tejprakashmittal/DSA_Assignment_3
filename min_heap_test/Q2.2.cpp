#include<iostream>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<vector>
using namespace std;

vector<pair<int,string>> global_path;
vector<int> done;

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
                    if(done[pare.second]==0 && minHeap[itr].first!=INT_MAX)
                    {
                        string temp=path[node_no]+' '+to_string(node.second);
                        global_path.push_back({minHeap[itr].first + val_edge_weight, temp});
                    }

                    decreaseKey(minHeap,{val_edge_weight+node.first,pare.second},itr);
                    dist[pare.second]=val_edge_weight+node.first;
                    path[pare.second]=path[node.second]+' '+to_string(pare.second);
                    if(done[pare.second]==0)
                    global_path.push_back({dist[pare.second],path[pare.second]});
                 }
                 else if(minHeap[itr].first < (val_edge_weight+node.first) && done[(minHeap[itr]).second]==0){
                    string temp=path[node.second]+' '+to_string(minHeap[itr].second);
                    global_path.push_back({val_edge_weight+node.first,temp}); 
                 }
                else if(minHeap[itr].first == (val_edge_weight+node.first)){
                    string temp=path[node.second]+' '+to_string(minHeap[itr].second);
                    //cout<<temp<<" "<<path[(*itr).second]<<endl;
                    if(temp < path[minHeap[itr].second]){
                        path[minHeap[itr].second]=temp;
                    }
                    if(done[minHeap[itr].second]==0)
                        global_path.push_back({dist[minHeap[itr].second],temp});
                 }
               }
            }
        }
        
        for(int h=0;h<path.size();h++){
            if(h==k) continue;
        }
        
        if(Max==INT_MAX) Max=-1;
        return Max;
    }
};

void all_pairs( vector<vector<int>> &times,int n, int k){
    Solution obj;

    for(int i=0;i<n;i++){
        done[i]=1;
        obj.networkDelayTime(times,n,i);
    }
    sort(global_path.begin(),global_path.end());
    for(int i=0;i<k;i++){
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
    int k;
    cin>>k;
    all_pairs(grid,n,k);
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<3;j++){
    //         cout<<grid[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}