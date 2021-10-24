#include<iostream>
#include<string.h>
#include <algorithm>
#include<vector>
using namespace std;

/*Trie Implementation starts------------------------------------------------------------------*/
struct TrieNode{
        char c;
        struct TrieNode *arr[256];
        int count=0;
        string word;
    };
    
    struct TrieNode* createNode(struct TrieNode* node){
        node=new TrieNode();
        memset(node->arr, NULL, 256);
        node->c='\0';
        node->word="";
        return node;
    }
    
    struct TrieNode *root;

     void insertIfNull(TrieNode* cur_root,string word,string org_word){
        TrieNode *temp=cur_root;
        for(int i=0;i<word.size();i++){
                struct TrieNode *node;
                temp->arr[word[i]]=node=createNode(node);
                node->c=word[i];
                temp=node;
            }
            temp->count=1;
            temp->word=org_word;
    }
    
    void insert(string word) {
        TrieNode *temp=root;
        
        int i=0;
        while(temp->arr[word[i]]!=NULL && i<word.size()){
                temp=temp->arr[word[i]];
                i++;
        }
        if(i==word.size()){
            temp->count=1;
            temp->word=word;
        }
        else insertIfNull(temp,word.substr(i,word.size()-i),word);
    }
    
    bool search(string word) {
            TrieNode* temp=root;
            for(int i=0;i<word.size();i++){
                if(temp->arr[word[i]]!=NULL) temp=temp->arr[word[i]];
                else return false;
            }
        if(temp->count==0) return false;
        return true;
    }
    
    bool startsWith(string prefix) {
            TrieNode* temp=root;
            for(int i=0;i<prefix.size();i++){
                if(temp->arr[prefix[i]]!=NULL) temp=temp->arr[prefix[i]];
                else return false;
            }
        return true;
    }
/*Trie Implementation ends------------------------------------------------------------------*/
class Solution {
public:
    vector<vector<int>> tab;
int c(string s,string t){
        if(s.size()==0 || t.size()==0){
            if(s.size()==0 && t.size()==0) return 0;
            if(s.size()==0 && t.size()==1) return 1;
            if(s.size() > 0) return s.size();
            if(t.size() > 0) return t.size();
        }
        else if(s[0]==t[0]){
            if(tab[s.size()-1][t.size()-1]!=-1) return tab[s.size()-1][t.size()-1];
            else {
                tab[s.size()-1][t.size()-1]=c(s.substr(1),t.substr(1));
                return  tab[s.size()-1][t.size()-1];
                }
        } 
        else{
            int x,y,z;
            if(tab[s.size()-1][t.size()-1]!=-1) x=1+tab[s.size()-1][t.size()-1];
            else {
                tab[s.size()-1][t.size()-1]=c(s.substr(1),t.substr(1));
                x=1+tab[s.size()-1][t.size()-1];    
            }  //Replace
            
            if(tab[s.size()-1][t.size()]!=-1) y=1+tab[s.size()-1][t.size()];
            else{
                tab[s.size()-1][t.size()]=c(s.substr(1),t);
                y=1+tab[s.size()-1][t.size()];
            }
             //Delete
             if(tab[s.size()][t.size()-1]!=-1) z=1+tab[s.size()][t.size()-1];
             else{
                 tab[s.size()][t.size()-1]=c(s,t.substr(1));
                 z=1+tab[s.size()][t.size()-1];
             } //Insert
            return min(min(x,y),z);
        }
    return 0;
    }
    int minDistance(string s, string t) {
        tab.resize(s.size()+1,vector<int>(t.size()+1,-1));
        tab[0][0]=0;
        
        //cout<<tab[0].size();
        return c(s,t);
    }
};


int spell_check(string str){
    return search(str);
}

void find_words(TrieNode* root,vector<string> &word_list,string str,string prefix){
    str+=root->c;
    for(int i=0;i<256;i++){
        if(root->arr[i]!=NULL) find_words(root->arr[i],word_list,str,prefix);
    }
    if(root->count==1){
        // string temp="able";
        // cout<<(root->word).compare(temp)<<" "<<root->word<<" "<<temp<<endl;
        word_list.push_back(prefix+str);
        //cout<<root->word<<" ";
    }
}

vector<string> auto_complete(string prefix){
    TrieNode* temp=root;
    vector<string> word_list;
    for(int i=0;i<prefix.size();i++){
        if(temp->arr[prefix[i]]!=NULL){
            temp=temp->arr[prefix[i]];
        }
    }
    find_words(temp,word_list,"",prefix.substr(0,prefix.size()-1));
    sort(word_list.begin(),word_list.end());
    return word_list;
}

void calc_auto_correct(TrieNode* root,vector<string> &word_list,string input,string str){
    str+=root->c;
    for(int i=0;i<256;i++){
        if(root->arr[i]!=NULL) calc_auto_correct(root->arr[i],word_list,input,str);
    }
    if(root->count==1){
        Solution *obj=new Solution();
        //if(str=="early"){
            //cout<<"hello";
        int x=obj->minDistance(root->word,input);
        //cout<<x<<" "<<str<<" ";
        
        if(x <= 3) word_list.push_back(root->word);
       // }
    }
}

vector<string> auto_correct(string input){
    vector<string> word_list;
    calc_auto_correct(root,word_list,input,"");
    sort(word_list.begin(),word_list.end());
    return word_list;
}

int main(){
    int n;
    cin>>n;

    root=createNode(root);

    FILE *fromFile_f;
    string path="./file1.3.txt";
    fromFile_f = fopen(path.c_str(), "r");
    char ch;int i=0,j=0;
    string str="";
    while ((ch = getc(fromFile_f)) != EOF && i<n) {
        if(ch=='\n'){
            j=0;
            i++;
            insert(str);
            str="";
            continue;
        }
        //int e=ch-'0';
        str+=ch;
        j++;
    }

    // for(int i=0;i<n;i++){
    //     string input;
    //     cin>>input;
    //     insert(input);
    // }
    int ai;string ti;
    cin>>ai>>ti;
    if(ai==1){
        cout<<spell_check(ti)<<endl;
    }else if(ai==2){
        vector<string> lis;
        lis=auto_complete(ti);
        cout<<lis.size()<<endl;
        for(auto itr:lis) cout<<itr<<endl;
    }
    else if(ai==3){
        vector<string> lis;
        lis=auto_correct(ti);
        cout<<lis.size()<<endl;
        for(auto itr:lis) cout<<itr<<endl;
    }else{
        //Solution obj;
        // int x=minDistance("early","halla");
        // cout<<x<<endl;
        //cout<<"yes";
        //   vector<string> lis;  
        //   find_words(root,lis,"","");
        //   cout<<lis.size()<<endl;
        //for(auto itr:lis) cout<<itr<<" ";
    }
}
