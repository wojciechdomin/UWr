#include <bits/stdc++.h>
#define int long long
#define mp make_pair
#define pb push_back
#define ld long double
#define pii pair<int,int>
#define sz(x) (int)x.size()
#define piii pair<pii,pii>
#define precise cout<<fixed<<setprecision(10)
#define st first
#define nd second
#define ins insert
#define vi vector<int>
#define BOOST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int MAX=2e5+5;
int x[MAX],y[MAX],col[MAX];
int xmaxi[MAX],ymaxi[MAX];

vector<int>best_col[MAX];
vector<int>dp[MAX];
set<int>cands[MAX];
int dist(int i,int j){
  int dist = abs(x[i]-x[j])+abs(y[i]-y[j]);
  assert(dist == max(abs(xmaxi[i]-xmaxi[j]),abs(ymaxi[i]-ymaxi[j])));
  return dist;
}

int n;
int color[MAX];
void solve(){
  int m;
  cin>>m;
  for (int i=1;i<=m;i++)cin>>color[i];
  int ans=0;
  for (int i=1;i<=m;i++){
    dp[i].resize(best_col[color[i]].size());
  }
  for (int i=1;i<=m;i++){
    if (i>=2){
      for (int j=0;j<best_col[color[i]].size();j++)dp[i][j]=0;
      for (int j=0;j<best_col[color[i]].size();j++){
        for (int k=0;k<best_col[color[i-1]].size();k++){
          dp[i][j]=max(dp[i][j],dp[i-1][k]+dist(best_col[color[i]][j],best_col[color[i-1]][k]));
          ans=max(ans,dp[i][j]);
        }
      }
    }
  }
  cout<<ans<<"\n";
}

vi points[MAX];
int32_t main()
{
  BOOST;  
  
  cin>>n;
  for (int i=1;i<=n;i++){
    cin>>x[i]>>y[i]>>col[i];
    xmaxi[i]=(x[i]+y[i]);
    ymaxi[i]=(x[i]-y[i]);
    points[col[i]].pb(i);
    
    /*
    0 - minimalizujemy po x w razie remisu chcemy trzymac najmniejszy y
    1 - minimalizujemy po x w razie remisu chcemy trzymac najwiekszy y
    2 - maksymalizujemy po x w razie remisu chcemy trzymac najmniejszy y
    3 - maksymalizujemy po x w razie remisu chcemy trzymac najwiekszy y

    -------------------------------
    4 - minimalizujemy po y w razie remisu chcemy trzymac najmniejszy x
    5 - minimalizujemy po y w razie remisu chcemy trzymac najwiekszy x
    6 - maksymalizujemy po y w razie remisu chcemy trzymac najmniejszy x
    7 - maksymalizujemy po y w razie remisu chcemy trzymac najwiekszy x


    */

    // 0
    /*
    if (best_col[col[i]][0]==-1){
      best_col[col[i]][0]=i;
    }
    else{
      int id=best_col[col[i]][0];
      if (xmaxi[i]<xmaxi[id] || (xmaxi[i]==xmaxi[id] && ymaxi[i]<ymaxi[id])){
        best_col[col[i]][0] = i;
      }
    }

    // 1
    if (best_col[col[i]][1]==-1){
      best_col[col[i]][1]=i;
    }
    else{
      int id=best_col[col[i]][1];
      if (xmaxi[i]<xmaxi[id] || (xmaxi[i]==xmaxi[id] && ymaxi[i]>ymaxi[id])){
        best_col[col[i]][1] = i;
      }
    }


    // 2
    if (best_col[col[i]][2]==-1){
      best_col[col[i]][2]=i;
    }
    else{
      int id=best_col[col[i]][2];
      if (xmaxi[i]>xmaxi[id] || (xmaxi[i]==xmaxi[id] && ymaxi[i]<ymaxi[id])){
        best_col[col[i]][2] = i;
      }
    }

    // 3

    if (best_col[col[i]][3]==-1){
      best_col[col[i]][3]=i;
    }
    else{
      int id=best_col[col[i]][3];
      if (xmaxi[i]>xmaxi[id] || (xmaxi[i]==xmaxi[id] && ymaxi[i]>ymaxi[id])){
        best_col[col[i]][3] = i;
      }
    }

    // 4
    if (best_col[col[i]][4]==-1){
      best_col[col[i]][4]=i;
    }
    else{
      int id=best_col[col[i]][4];
      if (ymaxi[i]<ymaxi[id] || (ymaxi[i]==ymaxi[id] && xmaxi[i]<xmaxi[id])){
        best_col[col[i]][4] = i;
      }
    }


    // 5
    if (best_col[col[i]][5]==-1){
      best_col[col[i]][5]=i;
    }
    else{
      int id=best_col[col[i]][5];
      if (ymaxi[i]<ymaxi[id] || (ymaxi[i]==ymaxi[id] && xmaxi[i]>xmaxi[id])){
        best_col[col[i]][5] = i;
      }
    }


    // 6
    if (best_col[col[i]][6]==-1){
      best_col[col[i]][6]=i;
    }
    else{
      int id=best_col[col[i]][6];
      if (ymaxi[i]>ymaxi[id] || (ymaxi[i]==ymaxi[id] && xmaxi[i]<xmaxi[id])){
        best_col[col[i]][6] = i;
      }
    }


    // 7
    if (best_col[col[i]][7]==-1){
      best_col[col[i]][7]=i;
    }
    else{
      int id=best_col[col[i]][7];
      if (ymaxi[i]>ymaxi[id] || (ymaxi[i]==ymaxi[id] && xmaxi[i]>xmaxi[id])){
        best_col[col[i]][7] = i;
      }
    }*/

   
  }


  for (int col=1;col<=(int)2e5;col++){
    vector<pair<pii,int>> pom;
    set<int>diffxmin,diffxmax,diffymin,diffymax;
    for (auto it:points[col]){
      pom.pb(mp(mp(xmaxi[it],ymaxi[it]),it));
    }
    sort(pom.begin(),pom.end(),[](pair<pii,int>a,pair<pii,int>b){
      if (a.st.st!=b.st.st)return a.st.st<b.st.st;
      return a.st.nd<b.st.nd;
    });
    for (auto it:pom){
      diffxmin.ins(it.st.st);
      if (sz(diffxmin)>=300)break;
    }


    sort(pom.begin(),pom.end(),[](pair<pii,int>a,pair<pii,int>b){
      if (a.st.st!=b.st.st)return a.st.st>b.st.st;
      return a.st.nd<b.st.nd;
    });
    for (auto it:pom){
      diffxmax.ins(it.st.st);
      if (sz(diffxmax)>=300)break;
    }


    sort(pom.begin(),pom.end(),[](pair<pii,int>a,pair<pii,int>b){
      return a.st.nd<b.st.nd;
    });
    for (auto it:pom){
      diffymin.ins(it.st.nd);
      if (sz(diffymin)>=300)break;
    }


    sort(pom.begin(),pom.end(),[](pair<pii,int>a,pair<pii,int>b){
      return a.st.nd>b.st.nd;
    });
    for (auto it:pom){
      diffymax.ins(it.st.nd);
      if (sz(diffymax)>=300)break;
    }
    const int inf=(int)1e18+9;

    for (auto wsp:diffxmin){
      int maxi=-inf,wsk=-1;
      for (auto it:points[col]){
        if (xmaxi[it]==wsp && ymaxi[it]>maxi){
          wsk=it;
          maxi=ymaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);

      wsk=-1;
      int mini=inf;


      for (auto it:points[col]){
        if (xmaxi[it]==wsp && ymaxi[it]<mini){
          wsk=it;
          mini=ymaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);
    }


    /*
    for (auto wsp:diffxmax){
      int maxi=-inf,wsk=-1;
      for (auto it:points[col]){
        if (xmaxi[it]==wsp && ymaxi[it]>maxi){
          wsk=it;
          maxi=ymaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);

      wsk=-1;
      int mini=inf;


      for (auto it:points[col]){
        if (xmaxi[it]==wsp && ymaxi[it]<mini){
          wsk=it;
          mini=ymaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);
    }



    for (auto wsp:diffymin){
      int maxi=-inf,wsk=-1;
      for (auto it:points[col]){
        if (ymaxi[it]==wsp && xmaxi[it]>maxi){
          wsk=it;
          maxi=xmaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);

      wsk=-1;
      int mini=inf;


      for (auto it:points[col]){
        if (ymaxi[it]==wsp && xmaxi[it]<mini){
          wsk=it;
          mini=xmaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);
    }


     for (auto wsp:diffymax){
      int maxi=-inf,wsk=-1;
      for (auto it:points[col]){
        if (ymaxi[it]==wsp && xmaxi[it]>maxi){
          wsk=it;
          maxi=xmaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);

      wsk=-1;
      int mini=inf;


      for (auto it:points[col]){
        if (ymaxi[it]==wsp && xmaxi[it]<mini){
          wsk=it;
          mini=xmaxi[it];
        }
      }
      assert(wsk!=-1);
      cands[col].ins(wsk);
    }
      */

  }


  for (int i=1;i<=MAX-1;i++){
    for (auto it:cands[i])best_col[i].pb(it);
  }


  int t;
  cin>>t;
  while (t--){
    solve();
  }
  return 0;
}