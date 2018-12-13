/*
The problem is: Given a tree of n vertices, what is the minimum number of edge deletion such that the forest
formed by group of have at least one tree that consists of exactly k vertices.

I checked for every vertices, if it is the root of the k-vertices newly created tree, what will be the minimum number of
edge deletion in the subtree of the current vertex such that the subtree rooted with k, with the deletion of vertices,
becomes k-vertices tree.

Formally, for each vertex u in the tree, let sz[u] be the size of subtree rooted with u.
Find the set S with minimum size possible such that sz[u] - sum(sz[S_i]) = k, where S_i are elements of S.

To do that, I implemented a dynamic programming.
Let dp[i][j] be the least number of non-intersecting subtree that sums the size of the subtrees to j.
Observe that sum(sz[S_i]) = sz[u]-k. Therefore, the answer at vertex i is dp[i][sz[u]-k].
But we have to go around all vertices.
So, I wrote a recurrence relation: dp[u][old+i] = min(dp[u][old+i],dp[u][old] + dp[v][i]).
And the base case is dp[u][0] = 0 (don't select anything), dp[u][sz[u]] = 1 (select itself).
This runs in O(N^3).

But furthermore, we have to print the edge deleted, so I tracked more using sets with dp.
Time Complexity: O(N^4).
*/
#include <bits/stdc++.h>
using namespace std;
int dp[405][405];
int sz[405];
int n,k;
int ans;
vector<int> g[405];
set<int> s[405][405];
set<int> ansset;
int p[405];
void dfs(int u,int p = -1){
	::p[u] = p;
	sz[u] = 1;
	for(int i = 0; i <= n; i++){
		dp[u][i] = 1e9;
	}
	dp[u][0] = 0;
	for(int v : g[u]){
		if(v == p) continue;
		dfs(v,u);
		sz[u] += sz[v];
		for(int i = n; i >= 0; i--){
			for(int j = n-i; j >= 0; j--){
				if(dp[u][i+j] > dp[u][i] + dp[v][j]){
					dp[u][i+j] = dp[u][i] + dp[v][j];
					s[u][i+j] = s[u][i];
					s[u][i+j].insert(s[v][j].begin(),s[v][j].end());
				}
			}
		}
	}
	if(dp[u][sz[u]] > 1){
		dp[u][sz[u]] = 1;
		s[u][sz[u]].clear();
		s[u][sz[u]].insert(u);
	}
	if(p == -1){
		dp[u][sz[u]] = 0;
		s[u][sz[u]].clear();
	}
	if(sz[u] >= k){
		if(ans > dp[u][sz[u] - k] + (p == -1 ? 0 : 1)){
			ans = dp[u][sz[u] - k] + (p == -1 ? 0 : 1);
			ansset = s[u][sz[u] - k];
			if(p != -1) ansset.insert(u);
		}
	}
}
int bck[405][405];
int main(){
	scanf("%d%d",&n,&k);
	for(int i = 1; i < n; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
		bck[x][y] = bck[y][x] = i;
	}
	ans = 1e9;
	dfs(1);
	printf("%d\n",ans);
	for(auto x : ansset){
		printf("%d ",bck[x][p[x]]);
	}
	printf("\n");
	return 0;
}
