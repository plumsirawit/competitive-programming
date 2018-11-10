#include <bits/stdc++.h>
using namespace std;
bool found[1 << 22];
bool used[1 << 22];
int n;
int fmsk;
void dfs(int u){
	if(found[u]) return;
	found[u] = true;
	for(int i = 0; i < n; i++){
		if(u & (1 << i)) continue;
		dfs(u | (1 << i));
	}
	if(used[u ^ fmsk]) dfs(u ^ fmsk);
}
int main(){
	int m;
	scanf("%d%d",&n,&m);
	vector<int> v;
	for(int i = 0; i < m; i++){
		int x;
		scanf("%d",&x);
		v.push_back(x);
		used[x] = true;
	}
	fmsk = 1 << n;
	fmsk--;
	int c = 0;
	sort(v.begin(),v.end());
	for(auto x : v){
		if(!found[fmsk ^ x]){
			dfs(x);
			c++;
		}
	}
	printf("%d\n",c);
}
