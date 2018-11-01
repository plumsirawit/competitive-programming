/*
Used Order Statistic Tree.
I tried for the case of only two courses meal first.
Sort the people according to time of appetizer.
Brute-force check if in the subset of size k from the first i people,
what will be the minimum time achieved from eating the main dish.
Now extends the solution up to 3 courses meal.
Sort the people according to time of appetizer and also the main dish.
(In my implementation I split into two vectors: a and b.)
Now brute-force i and j and track the minimum of maximum of subset of size k in the 'dessert' field.
It would be O(N^3).
I optimized to O(N^2*log(N)) using order statistic tree.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
int z[2048];
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	int x,y;
	vector<pair<int,int> > a,b,c;
	for(int i = 0; i < n; i++){
		scanf("%d%d%d",&x,&y,z+i);
		a.emplace_back(x,i);
		b.emplace_back(y,i);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	long long mn = 1e18;
	for(int i = 0; i < n; i++){
		set<int> used;
		for(int j = 0; j <= i; j++){
			used.insert(a[j].second);
		}
		tree<int,nullptr_t,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> t;
		for(int j = 0; j < n; j++){
			if(used.find(b[j].second) != used.end()){
				t.insert(make_pair(z[b[j].second],nullptr));
			}
			if(t.size() >= k){
				mn = min(mn,(long long)t.find_by_order(k-1)->first + (long long)b[j].first + (long long)a[i].first);
			}
		}
	}
	printf("%lld\n",mn);
	return 0;
}
