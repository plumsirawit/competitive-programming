#include <bits/stdc++.h>
using namespace std;
vector<int> g[300005];
multiset<long long> sack[300005];
int info[300005];
int c[300005];
long long slope[300005];
long long yint[300005];
int sz[300005];
void dfs(int u,int p = -1){
	sz[u] = 1;
	int mindex = -1;
	int mx = 0;
	for(int v : g[u]){
		if(v == p) continue;
		dfs(v,u);
		sz[u] += sz[v];
		if(sz[v] > mx){
			mx = sz[v];
			mindex = v;
		}
	}
	if(mindex == -1){
		info[u] = u;
		sack[u].insert(c[u]);
		sack[u].insert(c[u]);
		yint[u] = (long long)c[u];
		slope[u] = -1ll;
	}else{
		info[u] = info[mindex];
		for(int v : g[u]){
			if(v == p) continue;
			if(v == mindex) continue;
			for(long long x : sack[info[v]]){
				sack[info[u]].insert(x);
			}
			yint[info[u]] += yint[info[v]];
			slope[info[u]] += slope[info[v]];
		}
		long long opt = *sack[info[u]].rbegin();
		while(!sack[info[u]].empty() && slope[info[u]] + (long long)sack[info[u]].size() > 0ll){
			opt = *sack[info[u]].rbegin();
			sack[info[u]].erase(sack[info[u]].find(opt));
		}
		long long opt2 = *sack[info[u]].rbegin();
		sack[info[u]].erase(sack[info[u]].find(opt2));
		sack[info[u]].insert(opt + (long long)c[u]);
		sack[info[u]].insert(opt2 + (long long)c[u]);
		yint[info[u]] += (long long)c[u];
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 2; i <= n+m; i++){
		int p;
		scanf("%d%d",&p,c+i);
		g[i].push_back(p);
		g[p].push_back(i);
	}
	dfs(1);
	long long ly = yint[info[1]];
	long long ls = slope[info[1]];
	long long lp = 0ll;
	long long mn = ly;
	for(auto x : sack[info[1]]){
		ly += ls * (x - lp);
		ls++;
		lp = x;
		mn = min(mn,ly);
	}
	printf("%lld\n",mn);
}
