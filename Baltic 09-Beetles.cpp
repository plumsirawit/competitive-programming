#include <bits/stdc++.h>
using namespace std;
int dp[305][305][2];
class state{
public:
	int l;
	int r;
	int t;
	int dp;
	int side;
	state(){
		l = r = t = dp = side = 0;
	}
	state(int a,int b,int c,int d,int e){
		l = a;
		r = b;
		t = c;
		dp = d;
		side = e;
	}
	friend bool operator<(state x,state y){
		return x.t < y.t;
	}
};
int main(){
	int n,m;
	scanf("%d%d", &n, &m);
	int x;
	vector<int> neg,pos;
	int mod = 0;
	for(int i = 1; i <= n; i++){
		scanf("%d",&x);
		if(x == 0){
			mod += m;
			continue;
		}
		if(x < 0) neg.push_back(-x);
		else pos.push_back(x);
	}
	memset(dp,-1,sizeof(dp));
	neg.push_back(0);
	pos.push_back(0);
	sort(neg.begin(),neg.end());
	sort(pos.begin(),pos.end());
	priority_queue<state> pq;
	pq.emplace(0,0,m,0,0);
	pq.emplace(0,0,m,0,1);
	while(!pq.empty()){
		state cur = pq.top();
		pq.pop();
		if(dp[cur.l][cur.r][cur.side] >= cur.dp) continue;
		dp[cur.l][cur.r][cur.side] = cur.dp;
		//printf("USE (%d,%d,%d,%d,%d)\n",cur.l,cur.r,cur.t,cur.dp,cur.side);
		int nxtt,nxtv;
		int l = cur.l+1;
		if(l < neg.size()){
			if(cur.side == 0){
				nxtt = cur.t - neg[l] + neg[cur.l];
				if(nxtt > 0){
					nxtv = cur.dp + nxtt;
					pq.emplace(l,cur.r,nxtt,nxtv,0);
				}
			}else{
				nxtt = cur.t - pos[cur.r] - neg[l];
				if(nxtt > 0){	
					nxtv = cur.dp + nxtt;
					pq.emplace(l,cur.r,nxtt,nxtv,0);
				}
			}
		}
		int r = cur.r+1;
		if(r < pos.size()){
			if(cur.side == 0){
				nxtt = cur.t - neg[cur.l] - pos[r];
				if(nxtt > 0){
					nxtv = cur.dp + nxtt;
					pq.emplace(cur.l,r,nxtt,nxtv,1);	
				}
			}else{
				nxtt = cur.t - pos[r] + pos[cur.r];
				if(nxtt > 0){
					nxtv = cur.dp + nxtt;
					pq.emplace(cur.l,r,nxtt,nxtv,1);
				}
			}
		}
	}
	int mx = 0;
	for(int i = 0; i < neg.size(); i++){
		for(int j = 0; j < pos.size(); j++){
			mx = max(mx,max(dp[i][j][0],dp[i][j][1]));
		}
	}
	printf("%d\n",mx+mod);
}
