#include <bits/stdc++.h>
#define int unsigned long long
#define mp make_pair
#define pb push_back
#define pii pair<int,int>
#define sz(x) (int)x.size()
#define piii pair<pii,pii>
#define precise cout<<fixed<<setprecision(10)
#define st first
#define nd second
#define ins insert
#define vi vector<int>
#define BOOST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define debug(x) cout<<#x<<" = "<<x<<"\n"
using namespace std;

#define fi first
#define se second

template <typename H, typename T> 
ostream& operator<<(ostream& os, pair<H, T> m){
	return os <<"("<< m.fi<<", "<<m.se<<")";
}
 
template <typename H> 
ostream& operator<<(ostream& os, vector<H> V){
	os<<"{";
	for(int i=0; i<V.size(); i++){
		if(i)os<<" ";
		os<<V[i];
	}
	os<<"}";
	return os;
}
 

 int modd(int x){
	return x & ((unsigned long long)(1ll<<32)-1ll);
}

int modd(int x,int n){
	return x & ((unsigned long long)(1ll<<n)-1ll);
}

void solve()
{
	int a;
	cin>>a;
	vector<pair<int,int> > v[2];
	int t = 0;
	//v[0].pb({0,1});
	//v[0].pb({1,a});
	int u = 1;
	for(int i = 0; i < 2048; i++){
		v[0].pb({i,u});
		u = modd(u*a);
	}
	int c = a;
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	c = modd(c*c);
	for(int w = 11; w <= 31; w++){
		// debug(w);
		// debug(v[t]);
		// debug(v[t^1]);
		c = modd(c*c);
		for(auto x : v[t]){
		//	debug(x);
		//	debug(modd(x.se,w));
		//	debug( modd(a^(x.fi),w));
			if(modd(x.se,w) == modd(a^(x.fi),w+1)){
				v[t^1].pb({x.fi, modd(x.se)});
				// debug("ok");
			}
			if(modd(x.se*c,w+1) == modd(a^(x.fi+(1ll<<w)),w+1)){
				v[t^1].pb({x.fi+(1ll<<w), modd(x.se*c)});
			}
			
		}
		
		v[t].clear();
			t^=1;
	}

			u = 1;
			for(int i = 0; i < 2048; i++){
				if(modd(i^a) == u){
					v[t].pb({i,u});
				}
				u = modd(u*a);

			}
			int aa = a;
			int cnt = 31;
			u = 1;
			int ww = a;
			for(int i = 0; i < 32; i++){
				if(a & (1<<i)){
					u = modd(u * ww);
				}
				ww = modd(ww * ww);
			}
			if((ww ^ a) == 0)
			v[t].pb({a,modd(u)});

	set<int> s;
	for(auto x : v[t]){
		s.insert(x.fi);
	}
	cout<<s.size()<<" ";
	for(auto x : s){
		//assert(modd(x.se) == modd(x.fi ^ a));
		cout<<x<<" ";
	}
	cout<<"\n";





}


int32_t main(){
	BOOST;

	int t;
	cin>>t;
	while(t--){
		solve();
	}
}
