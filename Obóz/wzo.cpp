#include <bits/stdc++.h>
#define debug(x) cout<<#x<<" = "<<x<<"\n"
using namespace std;
const long long INF=1000000000;
const int P=1048576/2;
class areaTree{
	int s[P*2+10];
	int m[P*2+10];
	int t[P*2+10];
	int a, b, val;
	inline void lazy(int u){
		s[u]+=t[u];
		if (u<P)
			{
			t[u*2]+=t[u];
			t[u*2+1]+=t[u];
			calculate(u);
			}
		t[u]=0;
	}
	inline void calculate(int u){
		if (s[u*2]+t[u*2]<s[u*2+1]+t[u*2+1])
			{
			s[u]=s[u*2]+t[u*2];
			m[u]=m[u*2];
			}
		if (s[u*2]+t[u*2]==s[u*2+1]+t[u*2+1])
			{
			s[u]=s[u*2]+t[u*2];
			m[u]=m[u*2]+m[u*2+1];
			}
		if (s[u*2]+t[u*2]>s[u*2+1]+t[u*2+1])
			{
			s[u]=s[u*2+1]+t[u*2+1];
			m[u]=m[u*2+1];
			}
	}
	inline int mid(int low, int high){
		return (low+high)/2;
	}
	inline void add(int u=1, int low=0, int high=P-1){
		lazy(u);
		//cout<<u<<" "<<low<<" "<<high<<endl;
		if (a>high || low>b)
			return;
		if (a<=low && high<=b)
			{
			t[u]+=val;
			lazy(u);
			return;
			}
		add(u*2, low, mid(low, high));
		add(u*2+1, mid(low, high)+1, high);
		lazy(u);
	}
	public:
	void update(int x, int y, int v){
		a=x, b=y, val=v;
		add();
	}
	void clear(){
		for (int i=P; i<P*2; i++)
			m[i]=1;
		for (int i=P-1; i>0; i--)
			m[i]=m[i*2]+m[i*2+1];
		for (int i=0; i<=P*2+5; i++)
			s[i]=t[i]=0;
	}
	long long ask(){
		return P-m[1];
	}
};
areaTree tree;
vector <pair <pair <int, int>, pair <int, int> > > rivers;
vector <pair <pair <int, int>, pair <int, int> > > events;
vector <pair <pair <int, int>, pair <int, int> > > rect;
long long n, p, xx1, yy1, xx2, yy2;
long long area(){
	tree.clear(), events.clear();
	for (auto i: rect)
		{
		//cout<<"R: "<<i.first.first<<" "<<i.first.second<<" "<<i.second.first<<" "<<i.second.second<<endl;
		events.push_back({{i.first.first, 1}, {i.first.second, i.second.second}});
		events.push_back({{i.second.first+1, -1}, {i.first.second, i.second.second}});
		}
	sort(events.begin(), events.end());
	long long w=0, last=0;
	for (auto e: events)
		{
		//cout<<e.first.first<<" "<<e.first.second<<" "<<e.second.first<<" "<<e.second.second<<endl;
		w+=(long long)tree.ask()*(e.first.first-last);
		tree.update(e.second.first, e.second.second, e.first.second);
		//cout<<"XD"<<endl;
		last=e.first.first;
		}

	return w;
}
bool check(long long r){
	rect.clear();
	for (auto i: rivers)
		{
		long long ix1=i.first.first-r;
		long long ix2=i.second.first+r;
		long long iy1=i.first.second-r;
		long long iy2=i.second.second+r;
		ix2--, iy2--;
        
        // ZMIANA: Prawdziwe ucinanie przedziałów
		ix1=max(ix1, xx1);
		ix2=min(ix2, xx2);
		iy1=max(iy1, yy1);
		iy2=min(iy2, yy2);
        
        // ZMIANA: Filtr sprawdzający, czy rzeka fizycznie przecina się ze skanem
        if (ix1 <= ix2 && iy1 <= iy2) {
		    rect.push_back({{ix1, iy1}, {ix2, iy2}});
        }
		}
	long long ar=area();
	debug(ar);

	return ((ar*100))>=((xx2-xx1+1)*(yy2-yy1+1))*p;
}
int main()
	{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	while (n--)
		{
		int a, b, c, d;
		cin>>a>>b>>c>>d;
        // ZMIANA: Zabezpieczenie na współrzędne (układamy od lewej-do-prawej, dół-góra)
		rivers.push_back({{min(a, c), min(b, d)}, {max(a, c), max(b, d)}});
		}
	cin>>p>>xx1>>yy1>>xx2>>yy2;
	xx2--, yy2--;

    // ZMIANA: Górna granica na sztywno za największą możliwą odległością na planszy
	int low=-1, high=100005; 
	while (high-low>1)
		{
		int s=(low+high)/2;
		debug(s);
		if (check(s))
			high=s;
		else
			low=s;
		}
	cout<<high<<"\n";
	return 0;
	}