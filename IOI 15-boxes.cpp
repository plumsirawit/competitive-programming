/*
  The idea is about divide the strategy into three parts.
  1. Run clockwise from position 0 to position p[i] and back to position 0.
  2. Run counterclockwise from position 0 to position p[i] and back to position 0.
  3. Run around the circle from position 0 to position 0, giving K souvenirs to K teams.
  
  The main observation is that the strategy 3 should be on a middle interval (giving K souvenirs to K teams in the interval [L,R])
  and the strategy 1 and 2 should be used on prefix and suffix of the position array.
  
  Now, I define dp1[i] as the result of strategy 1 in the prefix of the position array, ending with i.
  Next, I define dp2[i] as the result of strategy 2 in the suffix of the position array, ending backwardly with i (interval [i,N-1]).
  
  Then the possible outcomes would be the minimum of dp1[i] + dp2[j] + ceil((N - (N-j) + (i-1)) / K) * L
  and the cases where only strategy (1 or 2) and 3 is applied (dp1[i] + ceil((N - (i-1)) / K) * L) and (dp2[i] + ceil((N - (N-i)) / K) * L).
  
  ceil((N - (N-j) + (i+1))/K) is the number of runs that uses strategy 3.
  
  As a brute-force solution, loop i and j where 0 <= i < j < N and track the minimum of the formula.
  To optimize, observe that when (N - (N-j) + (i+1)) cannot be divided by K, it is never optimal.
  So for each i, I consider only track j such that N - (N-j) + (i-1) can be divided by K.
  I derived the formula into: dp1[i] + dp2[i+1+j*K] + j * L.
  (Now, the formula (i,j) is for the interval [i,i+1+j*K].)
  
  So I made a table suf[i][j] such that suf[i][j] = min(suf[i][j+1], dp2[i+K*j] + j*L).
  suf[i][j] will be the suffix minimum starting from dp2[i+j*K] + j*L, dp2[i+(j+1)*K] + (j+1)*L, dp2[i+(j+2)*K] + (j+2)*L, ...
  Then the loop is optimized. For each i, mn = min(mn, dp1[i] + suf[(i+1) % K][(i+1) / K] - (i+1)/K*L.
  
  Now the memory exceeds the limit. It can be optimized by using only suf[j] instead of suf[i][j], but changed the order of operations.
  Instead of going i from 1 to N, fix i as a residue class modulo K, then compute possible suf[j] and compute the derived formula.
  
  The answer is the minimum of the formula.
*/
#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;
 
long long delivery(int N, int K, int L, int p[]) {
	vector<long long> dp1,dp2;
	vector<long long> suf;
	dp1.resize(N);
	dp2.resize(N);
	dp1[0] = 2ll*p[0];
	for(int i = 1; i < N; i++){
		dp1[i] = i >= K ? dp1[i-K] : 0ll;
		dp1[i] += 2ll*(long long)p[i];
	}
	dp2[N-1] = 2ll*(long long)(L-p[N-1]);
	for(int i = N-2; i >= 0; i--){
		dp2[i] = i+K >= N ? 0ll : dp2[i+K];
		dp2[i] += 2ll*(long long)(L-p[i]);
	}
	long long mn = (long long)(N+K-1)/(long long)K*(long long)L;
	for(int i = 0; i < N; i++){
		mn = min(mn,dp1[i] + (long long)(N-i+K-2)/(long long)K*(long long)L);
		mn = min(mn,dp2[i] + (long long)(i+K-1)/(long long)K*(long long)L);
	}
	for(int i = 0; i < K; i++){
		suf.clear();
		for(int j = (N-i-1)/K; j >= 0; j--) suf.push_back(0);
		for(int j = (N-i-1)/K; j >= 0; j--){
			suf[j] = min((K*(j+1)+i >= N ? (long long)1e18 : suf[j+1]),dp2[K*j+i] + (long long)j*(long long)L);
		}
		for(int j = (N-i-1)/K; j >= 0; j--){
			mn = min(mn,dp1[i+j*K-1] + suf[j] - (long long)(i+j*K)/(long long)K*(long long)L);
		}
	}
	return mn;
}
