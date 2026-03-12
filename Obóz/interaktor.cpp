#include <bits/stdc++.h>
#include "solve_dlazaw.hpp"

using namespace std;
using namespace Solve;

const int MAXN = 145, MAXQ = 2000;

int N, A, B;
int Q, C;
int par[MAXN];

bool P;
bool vis[MAXN];
bool adj[MAXN][MAXN];

int find(int now) {
  if (par[now] == now) {
    return now;
  }
  return par[now] = find(par[now]);
}

void dfs(int now) {
  vis[now] = true;
  for (int i = 1; i <= N; i++) {
    if (adj[now][i] && !vis[i]) {
      dfs(i);
    }
  }
}

void init() {
  for (int i = 1; i <= N; i++) {
    par[i] = i;
    if (!vis[i]) {
      C++;
      dfs(i);
    }
  }
}

int main(int argc, char** argv) {
	auto& I = Interactor::create(argc, argv);
	auto& input = I.test_reader();
	
	auto end = [&] (int score, const std::string& msg) {
		I.end(score, msg);
	};
    input >> N >> A >> B >> P;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
        input >> adj[i][j];
        }
    }
    
    init();
    I.writer(0) << N << endl;
    
    while (true) {
        char co;
        I.reader(0) >> co; 
        if(co == '?') {
            if (++Q > MAXQ) {
                end(0, "Wykonano ponad 2000 zapytań!");
            }
            
            vector <int> S, T;
            for (int i = 1; i <= N; i++) {
                int W;
                I.reader(0) >> W;
                if (W < 0 || W > 2) {
                    end(0, "Wczytano wartość inną niż: 0, 1, 2");
                }
                if (W == 1) {
                    S.push_back(i);
                }
                if (W == 2) {
                    T.push_back(i);
                }
            }

            int cnt[2] = {0,0};
            for (int i : S) {
                for (int j : T) {
                    cnt[adj[i][j]]++;
                }
            }
            
            I.writer(0) << A*cnt[1] + B*cnt[0] << endl;
        }
        else if (co == '!') {
            int M;
            I.reader(0) >> M;
            if (M != N-1) {
                end(0, "WA");
            }
            
            int cnt = 0;
            for (int i = 1; i < N; i++) {
                int U, V;
                I.reader(0) >> U >> V;
                if (U < 1 || U > N || V < 1 || V > N || U == V) {
                    end(0, "WA");
                }
                if (find(U) == find(V)) {
                    end(0, "WA");
                }
                par[find(U)] = find(V);
                if (!adj[U][V]) {
                    cnt++;
                }
            }
            
            if (cnt != C-1) {
                end(0, "WA");
            }

            if (P && Q > 1000) {
                if (Q > 1170) {
                    end((long double)100 * floor(5 + 2000.0 / (Q - 1000)) / (long double)35, "AC: " + to_string(Q) + " zapytań");
                }
                else {
                    end((long double)100 * floor(36 - pow(2, (Q - 1000) / 40.0)) / (long double)35, "AC: " + to_string(Q) + " zapytań");
                }
            }
            else {
                end(100, "AC: " + to_string(Q) + " zapytań");
            }
            end(0, "WA");
        }
        else {
            end(0, "zapytanie powinno być typu ? lub !");
        }
    }
    return 0;
}
