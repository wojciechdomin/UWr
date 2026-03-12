#include <bits/stdc++.h>

using namespace std;

int main () {
  int N; 
  cin >> N; 
  int x, y;
  cout << "? 1 ";
  for(int i = 2; i <= N; i++) {
    cout << "2 ";
  }
  cout << endl;
  cin >> x;
  cout << "? ";
  for(int i = 1; i <= N - 1; i++) {
    cout << "1 ";
  }
  cout << "2 " << endl;
  cin >> y;
  if(x < y) {
    cout << "! " << N - 1 << endl;
    for(int i = 2; i <= N; i++) {
      cout << "1 " << i << endl;
    }
  }
  else {
    cout << "! " << N - 1 << endl;
    for(int i = 1; i <= N - 1; i++) {
      cout << N << ' ' << i << endl;
    }
  }
  return 0; 
}