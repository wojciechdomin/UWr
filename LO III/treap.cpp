#include <bits/stdc++.h>
#include <experimental/chrono>
using namespace std;

#define debug(x) cout<<#x<<" = "<<x<<"\n"

class Treap{
		Treap* left;
		Treap* right;
		int priority;
		int key;
		public:
		Treap(){

		}
		Treap(Treap* _left, Treap* _right, int _priority, int _key){
				left = _left; right = _right; priority	= _priority; key = _key;
		}
		pair<Treap*,Treap*> split(int x){
				if(this->key > x){
						if(!left) return {nullptr, this};
						pair<Treap*,Treap*> costam = left->split(x);
						this->left = costam.second;
						return {costam.first ,  this}; 
				}else{
					if(!right) return {this, nullptr};
					pair<Treap*,Treap*> costam = right->split(x);
					this->right = costam.first;
					return	{this, costam.second};
				}
		}

		static Treap* merge(Treap* T1, Treap* T2){
			if(!T1) return T2;
			if(!T2) return T1;
			if(T1->priority	> T2->priority){
				T1->right = merge(T1->right, T2);
				return T1;
			}else {
				T2->left = merge(T1, T2->left);
				return T2;
			}
		}

	    Treap* insert(int x){
	    	Treap* wsk = new Treap(nullptr, nullptr , rand(), x);
	    	pair<Treap*,Treap*> T = this->split(x);
	    	T.second = merge(wsk, T.second);
	    	return merge(T.first, T.second);
	    }

	    Treap* delet(int x){
	    	pair<Treap*,Treap*> T = this->split(x);
	    	pair<Treap*,Treap*> S;
	    	if(T.first) S = T.first->split(x-1);
	    	else S = {nullptr,nullptr};
	    	return merge(S.first, T.second);
	    }

	    void print(){
	    	if(!!left) left->print();
	    	cout<<key<<" ";
	    	if(!!right) right->print();
	    }

	    void print_h(int x){
	    	if(!!left) left->print_h(x + 1);
	    	cout<<x<<" ";
	    	if(!!right) right->print_h(x+1);
	    }

};
vector<int> odp;

class ITreap{
		ITreap* left;
		ITreap* right;
		int priority;
		int value;
		int cnt;
		bool rev;
		public:
		ITreap(){

		}
		ITreap(ITreap* _left, ITreap* _right, int _priority, int _value){
				left = _left; right = _right; priority	= _priority; value = _value; rev = false;
				cnt = give_cnt(left) + give_cnt(right) + 1;
		}
		static int give_cnt(ITreap* wsk){
			return wsk ? wsk->cnt : 0;
		}

		ITreap* reverse(int l, int r){
			pushdown();
			pair<ITreap*, ITreap*> spl = split(r,0);
			if(!spl.first) return spl.second;
			pair<ITreap*, ITreap*> spl2 = spl.first->split(l,0);
			if(spl2.second	){
				spl2.second	->rev ^= 1;	
				swap(spl2.second->left,spl2.second->right);
			}
			return merge(spl2.first,merge(spl2.second,spl.second));
		}

		void pushdown(){
			if(!rev) return;
			if(left){
				left->rev^=1;
				swap(left->left, left->right);
			}
			if(right){
				right->rev^=1;
				swap(right->left,right->right);
			}
			rev = false;
		}


		static void update_cnt(ITreap* wsk){
			if(!wsk) return;
			int _cnt = 1;
			if(wsk->left) _cnt += wsk->left->cnt;
			if(wsk->right) _cnt += wsk->right->cnt;
			wsk->cnt = _cnt;
		}

		pair<ITreap*,ITreap*> split(int x, int add){
				pushdown();
				int key = give_cnt(this->left) + add;
				if(key > x){
						if(!left) return {nullptr, this};
						pair<ITreap*,ITreap*> costam = left->split(x,add);
						left = costam.second;
						ITreap* prawy = this;
						update_cnt(this);
						return {costam.first, prawy}; 
				}else{
					if(!right) return {this, nullptr};
					pair<ITreap*,ITreap*> costam = right->split(x,give_cnt(left)+1+add);
					ITreap* lewy = this;
					right = costam.first;
					update_cnt(this);
					return	{lewy, costam.second};
				}
		}		

		static ITreap* merge(ITreap* T1, ITreap* T2){
			if(T1) T1->pushdown();
			if(T2) T2->pushdown();
			if(!T1) return T2;
			if(!T2) return T1;
			if(T1->priority	> T2->priority){
				T1->right = merge(T1->right, T2);
				ITreap* wsk = T1;
				update_cnt(wsk);
				return wsk;
			}else {
				T2->left = merge(T1, T2->left);
				ITreap* wsk = T2;
				update_cnt(wsk);
				return wsk;
			}
		}

		ITreap* insert(int x,int v){
			pushdown();
	    	ITreap* wsk = new ITreap(nullptr, nullptr , rand(), v);
	    	update_cnt(wsk);
	    	pair<ITreap*,ITreap*> T = this->split(x,0);
	    	T.first	= merge(T.first, wsk);
	    	return merge(T.first, T.second);
	    }

	   	pair<ITreap*,int> delet(int x){
	   		pushdown();
	    	pair<ITreap*,ITreap*> T = this->split(x,0);
	    	if(!T.first) return {T.second,-1};
	    	pair<ITreap*,ITreap*> S = T.first->split(x-1,0);
	    	return {merge(S.first, T.second),S.second->value};
	    }

	    void print(){
	    	pushdown();
	    	if(!!left) left->print();
	    	odp.push_back(value);
	    	if(!!right) right->print();
	    }

};


int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	auto start = chrono::high_resolution_clock::now();
	srand(time(NULL));
	int n,q,m;
	cin>>n>>q>>m;
	ITreap* wsk = new ITreap(nullptr, nullptr, rand() , -1);
	for(int i = 1; i <= n; i++){
		int x; cin>>x;
		wsk = wsk->insert( i-1	, x);
	}
	wsk = (wsk->delet(0)).first;
	
	for(int i = 0; i < q; i++){
		int t,l,r;
		cin>>t>>l>>r;
		if(l==r) continue;
		if(t == 1){

				pair<ITreap*,int> p = wsk->delet(r-1);
				wsk = p.first->insert(l-2,p.second);	
		}else{
				wsk = wsk->reverse(l-2,r-1);
		}
		

	}
	wsk->print();
	

	
	for(int i = 0; i < m; i++){
		int x; cin>>x;
		cout<<odp[x-1]<<" ";
	}
	cout<<"\n";
	return 0;







}
