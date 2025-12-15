#include <bits/stdc++.h>
#define int long long
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

#define se second
#define fi first

const int MAX_Q = 20000;


//funckje do rotowania wektora kierunku
pair<int,int> rotateR(pair<int,int> p){
	return {-p.se, p.fi};
}

pair<int,int> rotateL(pair<int,int> p){
	return {p.se, -p.fi};
}

string Q;
int tura = 0;
int v = 1;
pair<int,int> c = {0,0}; //aktualna pozycja
pair<int,int> d = {1,0}; //kierunek
vector<int> old_dist;

int move(){
	char instr = Q[tura];
	tura++;
	if(instr == 'R'){
		d = rotateR(d);
	}
	if(instr == 'L'){
		d = rotateL(d);
	}
//	cout<<"? "<<instr<<endl;
	int dist;
//	cin>>dist;
	if(dist == 0) exit(0);
	c.fi+=d.fi*v;
	c.se+=d.se*v;
	v++;
	old_dist.push_back(dist);
	return dist;
}

int move_seq(string &s){
	Q+=s;
	int dist;
	while(tura < Q.size()){
		dist = move();
	//	debug(c);
	}
	return dist;
}

void solve()
{
	Q = "";

	int minx,maxx;
	bool okx = false;

	
	
	string gora1 = "FRRFRRLLLLFLLL";

	int d1 = move_seq(gora1);
	debug(c);
	int d2 = move_seq(gora1);
	debug(c);
	int d3 = move_seq(gora1);
	debug(c);
	int d4 = move_seq(gora1);
	debug(c);
	// debug(old_dist);
	if(d1 < d2){

	}
	if(d2 < d3){

	}

	


	





}


int32_t main(){
	BOOST;
	int t = 1;
//	cin>>t;
	while(t--){
		solve();
	}
}
