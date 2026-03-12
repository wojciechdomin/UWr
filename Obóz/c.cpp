#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100005;
int nex[MAX_N];
bool vis[MAX_N];



int main(){
  int N,K;
  cin>>N>>K;
  vector<int> dlugosci;
  for(int i = 1; i<= N; i++){
  	cin>>nex[i];
  }
  for(int i = 1; i <= N; i++){
    if(!vis[i]){
       int dlug = 1;
       vis[i] = true;
  	   int j = nex[i];
  	   while(!vis[j]){
  	    dlug++;
  	   	vis[j] = true;
  	   	j = nex[j];
  	   }
  	   dlugosci.push_back(dlug);
    } 
  }
  int odp = 0;
  sort(dlugosci.begin(),dlugosci.end(),greater<int>());
  for(int i = 0; i < min(K+1, (int)dlugosci.size()); i++){
  	odp += dlugosci[i];
  }
  cout<<odp<<"\n";










}