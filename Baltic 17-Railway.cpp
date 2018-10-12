/* 
	Observed the problem in brute-force solution.
	For each deputy minister, it is necessary to pair the neighbourhoods.

	The brute-force solution is, therefore, inefficient.

	Another idea is to check whether each edge should be selected or not.
	The sufficient condition is that the edge is selected by at least k deputy minister.
	The deputy minister numbered i would take edge(u,v) (WLOG assume v is parent of u in the DFS tree)
	if and only if we cut edge(u,v) then the tree would be divided into two parts such that there is at least
	one neighbourhood selected by the deputy minister in each part.

	The further idea is to check whether there exist that such pair in a more efficient way.
	The sufficient condition is that if we count the number of neighbourhoods selected by deputy minister i
	in the subtree of u and the rest, both of them should not be zero.

	i.e. cnt[u][i] != 0 && s[i] - cnt[u][i] != 0
	We split the invalid ones it to two parts:
		- cnt[u][i] == 0
		- cnt[u][i] == s
	
	If the valid ones counted at node u is more than or equal to k, then the edge between u and its parent should be selected.

	To maintain the counting, I used sack (DSU on tree) (to count each items) and another auxiliary array (to count the items such that cnt[items] == s[items]).
*/
#include <bits/stdc++.h>
using namespace std;
vector<pair<int,int> > g[100005];
vector<int> add[100005];
map<int,int> res[100005];
int info[100005];
int sz[100005];
int cnt[100005];
int c[100005];
int k;
vector<int> ans;
void dfs(int u,int p = -1,int pe = 0){
	sz[u] = 1;
	int mx = 0;
	int mindex = -1;
	for(auto v : g[u]){
		if(v.first == p) continue;
		dfs(v.first,u,v.second);
		sz[u] += sz[v.first];
		if(sz[v.first] > mx){
			mx = sz[v.first];
			mindex = v.first;
		}
	}
	info[u] = u;
	if(mindex != -1){
		info[u] = info[mindex];
		for(auto v : g[u]){
			if(v.first == p || v.first == mindex) continue;
			for(auto x : res[info[v.first]]){
				res[info[u]][x.first] += x.second;
				if(res[info[u]][x.first] == c[x.first]) cnt[info[u]]++;
			}
			res[info[v.first]].clear();
		}
	}
	for(int x : add[u]){
		res[info[u]][x]++;
		if(res[info[u]][x] == c[x]) cnt[info[u]]++;
	}
	if(res[info[u]].size() - cnt[info[u]] >= k){
		ans.push_back(pe);
	}
}
int main(){
	int n,m;
	scanf("%d%d%d",&n,&m,&k);
	int a,b;
	for(int i = 1; i < n; i++){
		scanf("%d%d",&a,&b);
		g[a].emplace_back(b,i);
		g[b].emplace_back(a,i);
	}
	for(int i = 1; i <= m; i++){
		int s;
		scanf("%d",&s);
		for(int j = 0; j < s; j++){
			scanf("%d",&a);
			add[a].push_back(i);
		}
		c[i] = s;
	}
	dfs(1);
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	for(auto x : ans){
		printf("%d ",x);
	}
	printf("\n");
	return 0;
}
