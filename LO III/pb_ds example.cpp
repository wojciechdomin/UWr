#include <bits/stdc++.h>
#define print(x) cout<<#x<<" = "<<x<<"\n"
#define jprint(x) cout<<x<<"\n"

//nagłówki:
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>  
#include <ext/pb_ds/priority_queue.hpp> //kolejka priorytetowa


using namespace __gnu_pbds;

using namespace std;

typedef tree<int,
             null_type,
             less<int>,
             rb_tree_tag,
             tree_order_statistics_node_update>
ordered_set;

typedef
tree<int, char, less<int>,
     splay_tree_tag,
     tree_order_statistics_node_update>
tree_map_t;



struct my_less_int{
    bool operator()(const int& a, const int& b) const {
        return a < b; 
    }
};

typedef tree<int,
             null_type,
             my_less_int,
             rb_tree_tag,
             tree_order_statistics_node_update>
ordered_set_with_custom_comparator;

typedef null_type		mapped_type;
typedef trie_string_access_traits<> 	cmp_fn;
typedef pat_trie_tag 			tag_type;

typedef trie<string, mapped_type, cmp_fn, tag_type, 
	     trie_prefix_search_node_update> trie_type;


void
print_prefix_match(const trie_type& t, const string& key)
{
  typedef trie_type::const_iterator 		const_iterator;

  cout << "All keys whose prefix matches \"" << key << "\":" << endl;

  const pair<const_iterator,const_iterator> match_range = t.prefix_range(key);
  for (const_iterator it = match_range.first; it != match_range.second; ++it)
    cout << *it << ' ';
  cout << endl;
}

struct CustomHash {
    int operator()(const std::string& key) const {
        int hash = 0;
        for (char c : key) {
            hash = hash * 31 + c; // Simple polynomial hash
        }
        return hash;
    }
};

int main(){
	ordered_set moj_zbior;
	moj_zbior.insert(5);
	moj_zbior.insert(2);
	moj_zbior.insert(3);
	jprint("wrzucamy elementy: {2,3,5}");
	jprint("moj_zbior.find_by_order(1) zwraca iterator it");
	auto it = moj_zbior.find_by_order(1); 
	print(*(it));
	print(moj_zbior.order_of_key(6));
	print(moj_zbior.order_of_key(5));
	print(moj_zbior.order_of_key(4));

	ordered_set zbior1, zbior2;
	jprint("zbior1 = {1,3,...,1999}. zbior2 = {2500,2502,...,4500}");

	for(int i = 1; i <= 1000; i++){
		zbior1.insert(2*i-1);
		zbior2.insert(i*2 + 2500); // zbior2.insert(i*2 + 1500) da błąd
		//klucze w jednym muszą być większe od kluczy w drugim
	}
	jprint("zbior1.join(zbior2)");
	 try {   
        zbior1.join(zbior2);
    } catch (const __gnu_pbds::join_error& e) {
        cerr << "Błąd: " << e.what() << "\n";
    }
	print(*zbior1.find_by_order(999));
	print(*zbior1.find_by_order(1000));
	jprint("zbior1.split(678)");
	zbior1.split(678,zbior2);
	print(zbior1.size());
	print(zbior2.size());


////////////////////////////////////////
	jprint("tree_map example:\n");
    tree_map_t s0;
    s0.insert({12, 'a'});
    s0.insert({505, 'b'});
    s0.insert({30, 'c'});
    print(s0.find_by_order(2)->first);
////////////////////////////////////
    jprint("cc_hash_table example:\n");
    //chained collisions
    //(w przypadku kolizji nawijamy kolejne elementy na listę wiązaną)
    cc_hash_table<int,char> hash_table1;
    hash_table1[5] = 'c';
    hash_table1[7] = 'd';
    print(hash_table1[7]);


    jprint("gp_hash_table example:\n");
    //general probing
    //(w przypadku kolizji wybieramy inną komórkę według pewnego wzoru matematycznego aż do trafienia na wolną)
    gp_hash_table<std::string, int, CustomHash> my_table;

    my_table["one"] = 1;
    my_table["two"] = 2;

    for (const auto& pair : my_table) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }



    //////////////////////////
    jprint("patricia trie\n");

	


     trie_type t;

  // Insert some entries.
	  assert(t.insert("I").second == true);
	  assert(t.insert("wish").second == true);
	  assert(t.insert("that").second == true);
	  assert(t.insert("I").second == false);
	  assert(t.insert("could").second == true);
	  assert(t.insert("ever").second == true);
	  assert(t.insert("see").second == true);
	  assert(t.insert("a").second == true);
	  assert(t.insert("poem").second == true);
	  assert(t.insert("lovely").second == true);
	  assert(t.insert("as").second == true);
	  assert(t.insert("a").second == false);
	  assert(t.insert("trie").second == true);


 print_prefix_match(t, "");
  print_prefix_match(t, "a");
  print_prefix_match(t, "as");
  print_prefix_match(t, "ad");
  print_prefix_match(t, "t");
  print_prefix_match(t, "tr");
  print_prefix_match(t, "trie");
  print_prefix_match(t, "zzz");

  //
  jprint("kolejny przyklad\n");
  typedef trie<string, string, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> 
  trie_map;
  trie_map t2; t2["apple"]="jabulko"; t2["app"] ="tiktok"; t2["banana"] = "banan"; t2["bat"] = "nietoper";
if (t2.find("app") != t2.end()) cout << "Found: app\n";
auto range = t2.prefix_range("ba");
for (auto it = range.first; it != range.second; ++it) cout << "Prefix match: " << it->first << "="<< it->second<<"\n";

jprint("kolejki priorytetowe:");
  typedef  __gnu_pbds::priority_queue<int, less<int>, thin_heap_tag> myPQ;
  myPQ pq;
  myPQ pq2;
  pq2.push(3);
  auto it1 = pq.push(1);
  pq.push(5);
  auto it2 = pq.push(10);
  print(pq.top());
  pq.modify(it2, -7);
  pq.join(pq2);
  print(pq.top());
  pq.erase(it1);
  jprint("------------");
  while(!pq.empty()){
  	print(pq.top());
  	pq.pop();
  }







}
