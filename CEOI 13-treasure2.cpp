#include <bits/stdc++.h>
#include "treasure.h"
using namespace std;
int dp[128][128];
int query(int a,int b,int c,int d,int N){
	if(a > c || b > d || a == 0 || b == 0 || c == 0 || d == 0 || a == N+1 || b == N+1 || c == N+1 || d == N+1) return 0;
	return countTreasure(a,b,c,d);
}
void findTreasure(int N){
	for(int i = N; i > 0; i--){
		for(int j = N; j > 0; j--){
			if(i > N/2 && j > N/2){
				dp[i][j] = query(1,1,i,j,N);
			}else if(i > N/2 && j <= N/2){
				dp[i][j] = dp[i][N] - query(1,j+1,i,N,N);
			}else if(i <= N/2 && j > N/2){
				dp[i][j] = dp[N][j] - query(i+1,1,N,j,N);
			}else{
				dp[i][j] = query(i+1,j+1,N,N,N) + dp[N][j] + dp[i][N] - dp[N][N];
			}
		}
	}
	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			if(dp[i][j] - dp[i-1][j] - dp[i][j-1] + dp[i-1][j-1] == 1){
				Report(i,j);
			}
		}
	}
}
