#include <bits/stdc++.h>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	multiset<int> options;
	multiset<int> used;
	options.insert(10000000);
	used.insert(10000000);
	int x;
	long long s = 0ll;
	for(int i = 0; i < n; i++){
		scanf("%d",&x);
		if(*options.begin() < *used.begin() && *options.begin() < x){
			used.insert(x);
			s += (long long)(x - *options.begin());
			options.erase(options.begin());
		}else if(*options.begin() >= *used.begin() && *used.begin() < x){
			options.insert(*used.begin());
			s += (long long)(x - *used.begin());
			used.erase(used.begin());
			used.insert(x);
		}else{
			options.insert(x);
		}
	}
	printf("%lld\n",s);
}
