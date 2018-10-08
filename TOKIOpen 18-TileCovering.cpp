#include "tile.h"
#include <bits/stdc++.h>
using namespace std;

bool found[300005];
vector<int> g[300005];
int idg[300005];
void dfs(vector<int>::iterator x,int K,vector<int>& A){
	if(found[x-A.begin()+1]) return;
	found[x-A.begin()+1] = true;
	auto nxt = lower_bound(A.begin(),A.end(),*x+K);
	if(nxt == A.end()) return;
	g[nxt-A.begin()+1].push_back(x-A.begin()+1);
	idg[x-A.begin()+1]++;
	dfs(nxt,K,A);
}
int p[300005][32];
int d[300005];
vector<int> gA;
void init(int N, int K, int Q, int M, vector<int> A) {
	for(vector<int>::iterator it = A.begin(); it != A.end(); ++it){
		dfs(it,K,A);
	}
	queue<int> q;
	for(int i = 1; i <= M; i++){
		if(idg[i] == 0){
			q.push(i);
		}
	}
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		for(int v : g[cur]){
			idg[v]--;
			if(idg[v] == 0){
				d[v] = d[cur]+1;
				p[v][0] = cur;
				for(int i = 1; i < 19; i++){
					p[v][i] = p[p[v][i-1]][i-1];
				}
				q.push(v);
			}
		}
	}
	gA = A;
}

int getNumberOfSpecialTiles(int L, int R) {
	int start = lower_bound(gA.begin(),gA.end(),L) - gA.begin();
	if(start == gA.size() || gA[start] > R){
		return 0;
	}
	start++;
	int cd = d[start];
	int endp = upper_bound(gA.begin(),gA.end(),R) - gA.begin();
	for(int i = 18; i >= 0; i--){
		if(p[start][i] != 0 && p[start][i] <= endp) start = p[start][i];
	}
	return cd - d[start] + 1;
}
