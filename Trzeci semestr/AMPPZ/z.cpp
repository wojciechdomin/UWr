#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define debug(x) cout<<#x<<" = "<<x<<"\n"
#define int long long

int N,M,L,D;
string pociag[105];
string pociag2[105];
int cnt[105][30];
vector<pair<int,int> > odp;
void move(int i,int j){
	// debug("!!!");
	assert(pociag[i].size() >= 1);
	char last = pociag[i][(int)pociag[i].size()-1];

	pociag[i].pop_back();
	pociag[j].pb(last);
	cnt[i][last - 'a']--;
	cnt[j][last-'a']++;
	odp.pb({i,j});
	// debug("???");
}

void naszczyt(int i, int j){
	int inna = 1;
	int ile = 0;
	vector<int> v;
	for(int k = L-1; k >= j; k--){
		if(ile == M-L){
			inna++;
			ile = 0;
		}
		if(inna == i){
			inna++;
			ile = 0;
		}
		v.pb(inna);
		move(i,inna);
		ile++;
		// debug(ile);

	}
	int el;
	for(el = 1; el <= N; el++){
		if(el != i && el != inna) break;
	}
	for(auto x : v){
		if(x != inna){
			move(x,i);
		}
	}
	move(inna, el);
	for(int k = 0; k + 1 < v.size(); k++){
		if(v[k] == inna) move(inna, i);
	}

	move(el, i);
}

void swip(int i, int j){ //swaps j and j+1 in i-th one
	// debug("swapbegin");
	// debug(pociag[i]);
	int inna = 1;
	vector<int> v;
	for(int k = L-1; k >= j; k--){
		while(inna == i) inna = (inna%N)+1;
		v.pb(inna);
		move(i,inna);
		inna=(inna%N)+1;
	}
	// debug(pociag[i]);
	assert(v[v.size()-2] != v[v.size()-1]);
	move(v[(int)(v.size())-2], i);
	move(v[(int)(v.size())-1], i);
	for(int j = (int)(v.size())-3; j >= 0; j--){
		move(v[j], i);
	}
	// debug(pociag[i]);
	// debug("swipend");
}


int32_t main(){
	cin>>N>>M>>L;
	D = (N-1)*(M-L);
	for(int i = 1; i <= N; i++){
		cin>>pociag[i];
		for(int j = max(0ll,L-D); j < L; j++){
			cnt[i][pociag[i][j]-'a']++;
		}
	}
	for(int i = 1; i <= N; i++){
		cin>>pociag2[i];
		for(int j = max(0ll,L-D); j < L; j++){
			cnt[i][pociag2[i][j]-'a']--;
		}
	}

	bool ok = true;
	for(int i = 1; i <= N; i++){
		for(int j = 0; j < L-D; j++){
			if(pociag[i][j] != pociag2[i][j]) ok = 0;
		}
		if(N <= 2 && pociag[i] != pociag2[i]) ok = 0;
	}
	if(!ok){
		cout<<"NO\n";
	}
	if(N <= 2){
		cout<<"YES\n0\n";
	}
	// debug("!");
	for(int i = 1; i <= N; i++){
		for(char z = 'a'; z <= 'z'; z++){
			while(cnt[i][z-'a'] > 0){
				// debug(i);
				char y;
				for(y = 'a'; y <= 'z'; y++) if(cnt[i][y-'a'] < 0) break;
				int i2;
				for(i2 = i+1; i2 <= N; i2++) if(cnt[i2][y-'a'] > 0) break;

				int p1,p2;
				for(p1= L; p1 >= max(0ll,L-D); p1--) if(pociag[i][p1] == z) break;
				for(p2= L; p2 >= max(0ll,L-D); p2--) if(pociag[i2][p2] == y) break;
					// debug(i);
				assert(pociag[i].size() == L);
				assert(pociag[i2].size() == L);
				assert(p1>=0);
				assert(p2>=0);
				naszczyt(i,p1);
				// debug("ok");
				naszczyt(i2,p2);
				int el;
				for(el = 1; el <= N; el++) if(el != i && el != i2) break;
				move(i,el);
				move(i2,i);
				move(el,i2);
				// debug(i);
				// debug(i2);



			}
		}
	}
for(int i = 1; i <= N; i++){
	int a = max(0ll,L-D);
	while(a < L){
		// debug(a);
		if(pociag[i][a] == pociag2[i][a]){
			a++;
			continue;
		}
		char cel = pociag2[i][a];
		int p = a;
		for(p = a; p < L; p++) if(pociag[i][p] == cel) break;
		for(int k = p-1; k >= a; k--){
			// debug("swap");
			// debug(k);
			// debug(pociag[i]);
			swip(i,k);
			// debug(pociag[i]);
		}

	}
	
}

// for(int i = 1; i <= N; i++){
	// cout<<pociag[i]<<"\n";
// }
cout<<"YES\n";
cout<<odp.size()<<"\n";
for(auto x : odp){
	cout<<x.first<<" "<<x.second<<"\n";
}



	return 0;
}