#include<iostream>
#include<queue>
#include<vector>
using namespace std;

class Solution {
public:
    
    bool safe(vector<vector<int>>& grid,vector<vector<int>>& visited,int i,int j){
        return (i>0) && (j>0) && (i<grid.size()-1) && (j<grid[0].size()-1) && (grid[i][j]==0) && (visited[i][j]==0);
    }
    
    bool safe_visited(vector<vector<int>>& grid,vector<vector<int>>& visited,int i,int j){
        return (i>0) && (j>0) && (i<grid.size()-1) && (j<grid[0].size()-1) && (grid[i][j]==0) && (visited[i][j]==1);
    }
    
    void shortestPathBinaryMatrix(vector<vector<char>>& grid) {
        // if(grid[0][0] || grid[grid.size()-1][grid[0].size()-1]) return -1;
        // if(grid.size()==1 && grid[0].size()==1) return 1;
        queue<pair<int,int>> qu;
        vector<vector<int>> visited(grid.size(),vector<int>(grid[0].size(),0));
        vector<vector<int>> grid_new(grid.size(),vector<int>(grid[0].size(),0));
        vector<pair<int,int>> riders;
        vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),__INT_MAX__));
        
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]=='#') grid_new[i][j]=__INT_MAX__;
                else if(grid[i][j]=='R'){
                    riders.push_back({i,j});
                }
                else  grid_new[i][j]=0;
            }
        }
        
        int row[]={-1,0,0,1};
        int col[]={0,-1,1,0};
        
        visited[0][0]=1;
        dp[1][1]=1;
        qu.push({1,1});
        
        while(qu.empty()==false){
            auto pos=qu.front();
            qu.pop();
            
            int Min=__INT_MAX__;
            for(int k=0;k<4;k++){
                if(safe_visited(grid_new,visited,pos.first+row[k],pos.second+col[k])){
                    Min=min(Min,dp[pos.first+row[k]][pos.second+col[k]]);
                }
            }
            if(Min!=__INT_MAX__)
                dp[pos.first][pos.second]=Min+1;
            
            for(int k=0;k<8;k++){
                if(safe(grid_new,visited,pos.first+row[k],pos.second+col[k])){
                    qu.push({pos.first+row[k],pos.second+col[k]});
                    visited[pos.first+row[k]][pos.second+col[k]]=1;
                }
            }
            
        }
        for(int i=0;i<dp.size();i++){
            for(int j=0;j<dp[0].size();j++){
                if(dp[i][j]==__INT_MAX__) cout<<"-1"<<" ";
                else cout<<dp[i][j]<<" ";
            }
            cout<<endl;
        }

        int Min=__INT_MAX__;
        for(int i=0;i<riders.size();i++){
            Min=min(Min,dp[riders[i].first][riders[i].second]);
        }

        if(Min!=__INT_MAX__){
            if(Min < dp[dp.size()-2][dp[0].size()-2]) cout<<"NO"<<endl;
            else cout<<"Yes"<<endl<<dp[dp.size()-2][dp[0].size()-2];
        }
        else {
            if(dp[dp.size()-2][dp[0].size()-2] != __INT_MAX__) cout<<"Yes"<<endl<<dp[dp.size()-2][dp[0].size()-2];
            else cout<<"INVALID"<<endl;
        }
        // if(dp[dp.size()-2][dp[0].size()-2]==__INT_MAX__) return -1;
        // return dp[dp.size()-2][dp[0].size()-2];
    }
};

int main(){
    int m,n;
    cin>>m>>n;
    FILE *fromFile_f;
    vector<vector<char>> grid(m,vector<char>(n));
    string path="./file.txt";
    fromFile_f = fopen(path.c_str(), "r");
    char ch;int i=0,j=0;
    while ((ch = getc(fromFile_f)) != EOF && i<m) {
        if(ch=='\n'){
            j=0;
            i++;
            continue;
        }
        //int e=ch-'0';
        grid[i][j]=ch;
        j++;
    }

    Solution obj;
    obj.shortestPathBinaryMatrix(grid);

    // for(int i=0;i<m;i++){
    //     for(int j=0;j<n;j++){
    //         cout<<grid[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
}