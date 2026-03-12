#include <bits/stdc++.h>
#define debug2(x) cout<<#x<<" = "<<x<<"\n"
#define debug(x)
#define s second
#define f first
using namespace std;
long long tab[10005][4];
vector<pair<pair<int,int>,pair<int,int>>> newbie;
long long xp,yp,xk,yk;
void przeskaluj(int n, int k)
{
    for (int i=0; i<n; i++){
        int xa=max(tab[i][0]-k,xp);
        int ya=max(tab[i][1]-k,yp);
        int xb=min(tab[i][2]+k,xk);
        int yb=min(tab[i][3]+k,yk);
        if (xb<xp || xa>xk || ya>yk || yb<yp){
            continue;
        }
        else {
            newbie.push_back({{xa,1},{ya,yb}});
            newbie.push_back({{xb,-1},{ya,yb}});
        }
    }
}
const int B=(1<<17);
int tree[2*B+5][2];
int lazy[2*B+5];
void wyp()
{

    for (int i=B; i<2*B; i++){
        tree[i][0]=0;
        lazy[i]=0;
        tree[i][1]=1;
    }
    for (int i=B-1; i>0; i--){
        tree[i][0]=0;
        lazy[i]=0;
        tree[i][1]=tree[i*2][1]+tree[i*2+1][1];
    }
    newbie.clear();
}
void propagate(int v)
{
    if (v>=B){

        return;
    }
    int l=2*v,r=l+1;
    lazy[l]+=lazy[v];
    lazy[r]+=lazy[v];
    tree[l][0]+=lazy[v];
    tree[r][0]+=lazy[v];
    lazy[v]=0;
}
void add(int v, int be, int en, int a, int b, int Val)
{
    debug(v);
    debug(be);
    debug(en);
    propagate(v);

    if (a==be && b==en){

        lazy[v]+=Val;
        tree[v][0]+=Val;
        return ;
    }
    int l=2*v, r=l+1;
    int mid=(be+en)/2;
    if (a<=mid){
        add(l,be,mid,a,min(mid,b),Val);
    }
    if (b>mid){
        add(r,mid+1,en,max(a,mid+1),b,Val);
    }
    tree[v][0]=min(tree[l][0],tree[r][0]);
    tree[v][1]=0;
    if (tree[l][0]==tree[v][0]) tree[v][1]+=tree[l][1];
    if (tree[r][0]==tree[v][0]) tree[v][1]+=tree[r][1];
}
int sum(int v, int be, int en, int a, int b)
{
    propagate(v);
    if (a==be && b==en){
        if (tree[v][0]==0)
        	return tree[v][1];
        return 0;
    }
    int l=2*v, r=l+1, ile=0;
    int mid=(be+en)/2;
    if (a<=mid){
        ile+=sum(l,be, mid, a, min(b,mid));
    }
    if (b>mid){
        ile+=sum(r, mid+1, en, max(a, mid+1), b);
    }
    return ile;
}
long long licz(long long k, int n)
{
    long long suma=0;
    wyp();
    przeskaluj(n,k);
    if (newbie.size()==0){
        return 0;
    }
    sort(newbie.begin(), newbie.end());
// debug2("-----------------------------------------------------------");
 	long long last = newbie[0].f.s;
    add(1,0,B-1,newbie[0].s.f, newbie[0].s.s,newbie[0].f.s);
    for (int i=1; i<newbie.size(); i++){
        int qwerty=sum(1,0,B-1,yp,yk);
        // debug2(qwerty);
       	suma+=((yk-yp)-qwerty)*(newbie[i].f.f-newbie[i-1].f.f);    
        add(1,0,B-1,newbie[i].s.f, newbie[i].s.s,newbie[i].f.s);
    }
    return suma;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>tab[i][0]>>tab[i][1]>>tab[i][2]>>tab[i][3];
        if (tab[i][0]>tab[i][2]){
            swap(tab[i][0],tab[i][2]);
        }
        if (tab[i][1]>tab[i][3]){
            swap(tab[i][1],tab[i][3]);
        }
    }
    long long p,op;
    cin>>p;
    op=p;
    cin>>xp>>yp>>xk>>yk;
    if (xp>xk){
        swap(xp,xk);
    }
    if (yp>yk){
        swap(yp,yk);
    }
    long long pole=(abs(xk-xp)*abs(yk-yp));
    long long m_pole=(pole*op-1)/100+1;
    long long l=-1, r=100005;
    while (l<r-1){
        
        int mid=(l+r)/2;
        debug2(mid);
        debug2(licz(mid,n));
        if (licz(mid, n)*100>=pole*p){
            r=mid;
        }
        else {
            l=mid;
        }
    }
    cout<<r<<"\n";
    return 0;
}
/*
1
833 113 839 113
99
627 641 715 883
1
800 100 850 100
100
600 600 700 900
*/
