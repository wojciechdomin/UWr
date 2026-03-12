#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50005;
const int LOG_N = 20;
vector<int> graf[MAX_N];
int depth[MAX_N];
int paren[LOG_N][MAX_N];
int kontr[MAX_N];
int suma[MAX_N];

int ans = 0;

void dfs(int v, int p){
	depth[v] = depth[p] + 1;
	paren[0][v] = p;
	for(auto x : graf[v]){
		if(x!=p) dfs(x,v);
	}
}

void dfs2(int v, int p){
	depth[v] = depth[p] + 1;
	suma[v] = kontr[v];
	for(auto x : graf[v]){
		if(x!=p){
			dfs2(x,v);
			suma[v] += suma[x];
		}
	}
	ans = max(ans, suma[v]);
}

int lca(int u, int v){
	int cnt = LOG_N-1;
	if(depth[v] < depth[u]) swap(u,v);
	while(cnt >= 0){
		if(depth[paren[cnt][v]] >= depth[u])
			v = paren[cnt][v];
		cnt--;
	}
	cnt = LOG_N - 1;
	while(cnt >= 0){
		if(paren[cnt][v] != paren[cnt][u]){
			v = paren[cnt][v];
			u = paren[cnt][u];
		}
		cnt--;
	}
	if(v != u){
		v = paren[0][v];
		u = paren[0][u];
	}
	return v;
}



int main(){
	int N,K;
	cin>>N>>K;
	for(int i = 0; i < N-1; i++){
		int u,v;
		cin>>u>>v;
		graf[u].push_back(v);
		graf[v].push_back(u);
	}
	depth[0] = -1;
	dfs(1,0);
	for(int i = 1; i < LOG_N; i++){
		for(int j = 0; j <= N; j++){
			paren[i][j] = paren[i-1][paren[i-1][j]];
		}
	}
	for(int i = 1; i <= K; i++){
		int u,v;
		cin>>u>>v;
		int l = lca(u,v);
		kontr[u]++;
		kontr[v]++;
		kontr[l]--;
		kontr[paren[0][l]]--;
	}
	dfs2(1,0);
	cout<<ans<<"\n";
	


}