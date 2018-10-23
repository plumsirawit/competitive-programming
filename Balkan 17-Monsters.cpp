#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
char t[1024][1024];
int v[1024][1024];
int ax[1024*1024];
long long tg[1024*1024];
long long nm[1024][1024];
long long rs[1024][1024];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("%s",t[i]+1);
	}
	long long ans = 0ll;
	int u,mn,k;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(t[i][j] == '0') continue;
			v[j][i] = v[j-1][i] + 1;
			mn = v[j][i];
			u = (j+1) << 10;
			for(k = i; k > 0; k--){
				mn = min(mn,v[j][k]);
				if(mn == 0) break;
				ans += mn;
            	ax[u + k]--;
            	ax[u + i+1]++;
            	tg[u + k] -= mn;
            	tg[u + i+1] += mn;
				ax[1024*(j-mn+1) + k]++;
            	ax[1024*(j-mn+1) + i+1]--;
			}
		}
	}
	long long mx = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			nm[j][i] = nm[j-1][i] + (long long)ax[j*1024 + i];
		}
		for(int j = 1; j <= m; j++){
			nm[j][i] += tg[j*1024 + i];
			rs[j][i] = rs[j-1][i] + rs[j][i-1] - rs[j-1][i-1] + nm[j][i];
			if(rs[j][i] > mx){
				mx = rs[j][i];
			}
		}
	}
	printf("%lld\n",ans-mx);
}
