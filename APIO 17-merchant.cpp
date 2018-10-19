#include <bits/stdc++.h>
using namespace std;
int b[128][1024];
int s[128][1024];
int profit[128][128];
long long d1[128][128];
long long d2[128][128];
int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= k; j++){
			scanf("%d%d",&b[i][j],&s[i][j]);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			for(int l = 1; l <= k; l++){
				if(b[i][l] != -1 && s[j][l] != -1){
					profit[i][j] = max(profit[i][j],s[j][l] - b[i][l]);
				}
			}
			d1[i][j] = 1e18;
		}
	}
	for(int i = 1; i <= m; i++){
		int v,w,t;
		scanf("%d%d%d",&v,&w,&t);
		d1[v][w] = t;
	}
	for(int l = 1; l <= n; l++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				d1[i][j] = min(d1[i][j],d1[i][l] + d1[l][j]);
			}
		}
	}
	long long lo = 0ll;
	long long hi = 1e12;
	long long mid;
	while(lo < hi){
		mid = (lo + hi + 1ll)/2ll;
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				d2[i][j] = profit[i][j] - mid*min((long long)1e18/mid,d1[i][j]);
			}
		}
		for(int l = 1; l <= n; l++){
			for(int i = 1; i <= n; i++){
				for(int j = 1; j <= n; j++){
					d2[i][j] = max(d2[i][j],d2[i][l] + d2[l][j]);
				}
			}
		}
		bool ok = false;
		for(int i = 1; i <= n; i++){
			if(d2[i][i] >= 0){
				ok = true;
			}
		}
		if(ok){
			lo = mid;
		}else{
			hi = mid-1ll;
		}
	}
	printf("%lld\n",lo);
}
