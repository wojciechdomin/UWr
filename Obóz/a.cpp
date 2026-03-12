#include <bits/stdc++.h>
    using namespace std;
    #define ll long long
    #define st first
    #define nd second
    #define pii pair<int,int>
    #define ba back
    #define si size
    #define pb push_back
    #define pp pop_back
    #define int ll
    #define debug(x) cout<<#x<<" = "<<x<<"\n"
;


const int base=1<<17;
pii tree[2*base];
int tree2[2*base];


 int n,a,b,c,d,p;


void push(int v){
    tree[2*v].st+=tree2[v];
    tree[2*v+1].st+=tree2[v];
    tree2[2*v]+=tree2[v];
    tree2[2*v+1]+=tree2[v];
    tree2[v]=0;
}
void add(int v,int a,int b,int l,int r,int k){
    if(l<=a&&b<=r){
        tree2[v]+=k;
        tree[v].st+=k;
        return;
    }
    if(a>r||b<l)return;
    int mid=(a+b)/2;
    push(v);
    add(2*v,a,mid,l,r,k);
    add(2*v+1,mid+1,b,l,r,k);
    pii p=tree[2*v],q=tree[2*v+1];
    if(p.st!=q.st)tree[v]=min(p,q);
    else tree[v]={p.st,p.nd+q.nd};
}
void rek(int v,int a,int b){
    if(v>=2*base)return;
    tree[v].nd=b-a+1;
    tree[v].st=0;
    int mid=(a+b)/2;
    rek(2*v,a,mid);
    rek(2*v+1,mid+1,b);
}

void reset(){
	for(int i = 2*base; i >= base; i--){
		tree[i].st = 0;
		tree[i].nd = 1;
	}
	for(int i = base-1; i >= 1; i--){
		tree[i].st = min(tree[i*2].st, tree[i*2+1].st);
		tree[i].nd = tree[i*2].nd + tree[i*2+1].nd;
	}


}
pii query(int v,int a,int b,int l,int r){
    if(l<=a&&b<=r){
        return tree[v];
    }
    if(b<l||r<a)return {1e9,1e9};
    push(v);
    int mid=(a+b)/2;
    pii p=query(2*v,a,mid,l,r),q;
    q=query(2*v+1,mid+1,b,l,r);
    if(p.st!=q.nd)return min(p,q);
    return {p.st,p.nd+q.nd};
}

bool cmp(const pair<pii,pii> a,const pair<pii,pii> b){
    if(a.st.st!=b.st.st)return a.st.st>b.st.st;
    if(!a.st.nd)return 1;
    if(!b.st.nd)return 0;
    return a.st.nd<b.st.nd;
}

ll policz_pole(ll R, vector<pair<pii, pii> > &v){
	    int sum=0;
        vector<pair<pii,pii>> acc;
        for(int i=0;i<n;i++){
            acc.pb({{min(c,v[i].nd.st+R),1},{max(b,v[i].st.nd-R),min(d,v[i].nd.nd+R)}});
            acc.pb({{max(a,v[i].st.st-R-1),-1},{max(b,v[i].st.nd-R-1),min(d,v[i].nd.nd+R)}});
        }
        acc.pb({{c,0},{b,d}});
        sort(acc.begin(),acc.end(),cmp);
          for(int i=1;i<acc.si();i++){
            pii pa=query(1,0,base-1,b,d-1);
            int dod;
            if(pa.st)dod=d-b;
            else dod=pa.nd;
            sum+=(acc[i-1].st.st-acc[i].st.st)*dod;
            add(1,0,base-1,acc[i].nd.st,acc[i].nd.nd,acc[i].st.nd);
    
        }
        return sum;
}


signed main(){
   
    cin>>n;
    vector<pair<pii,pii>>v(n);
    for(int i=0;i<n;i++){
        cin>>v[i].st.st>>v[i].st.nd>>v[i].nd.st>>v[i].nd.nd;
    }
    cin>>p>>a>>b>>c>>d;
    int l=-1,r=1e5,mid;
    ll sum = policz_pole (0, v);
    	debug(0);
    	debug(sum);
    while(r-l>1){
        reset();
        mid=(l+r)/2;
    	ll sum = policz_pole (mid, v);
    	debug(mid);
    	debug(sum);
        if(sum*100>p*(c-a)*(d-b))r=mid;
        else l=mid;
    }
    cout<<r<<'\n';
}