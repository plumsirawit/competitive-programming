/*
I put every qudruple (i,j,k,l) such that i != j != k != l (distinct value) and 0 <= i,j,k,l < 16 into a set Q.
Then, I hashed (let's say masked) each quadruple (i,j,k,l) with i+2*j+3*k+4*l.
And bucketed all of them with the same masked value into the same group.
For each with the same mask, they can be in the balance.

For the same mask, they can be in the two side of the balance if and only if (i1,j1,k1,l1) and (i2,j2,k2,l2)
has {i1,j1,k1,l1,i2,j2,k2,l2} as distinct numbers.
Let `use` be a counting array that can count the number of ways for {i1,j1,k1,l1,i2,j2,k2,l2} such that they can be balanced.
So the total number of ways is the use[{i1,j1,k1,l1,i2,j2,k2,l2}] * use[the other 8 values].
But there is two balance, so I divided by two.
*/
#include <bits/stdc++.h>
using namespace std;
int a[16];
vector<int> c[32768];
int use[65536];
int main(){
	int tc = 1;
	while(true){
		memset(use,0,sizeof(use));
		for(int i = 0; i < 32768; i++){
			c[i].clear();
		}
		for(int i = 0; i < 16; i++){
			scanf("%d",a+i);
			if(a[i] == 0){
				return 0;
			}
		}
		for(int i = 0; i < 16; i++){
			for(int j = 0; j < 16; j++){
				for(int k = 0; k < 16; k++){
					for(int l = 0; l < 16; l++){
						if(i == j || j == k || k == l || i == k || i == l || j == l) continue;
						c[a[i]+2*a[j]+3*a[k]+4*a[l]].push_back((1 << i) | (1 << j) | (1 << k) | (1 << l));
					}
				}
			}
		}
		for(int i = 0; i < 32768; i++){
			for(int j = 0; j < c[i].size(); j++){
				for(int k = j+1; k < c[i].size(); k++){
					if((c[i][j] & c[i][k]) == 0){
						use[c[i][j] | c[i][k]]++;
					}
				}
			}
		}
		long long d = 0ll;
		for(int i = 0; i < 65536; i++){
			d += (long long)use[i] * (long long)use[65535 ^ i];
		}
		printf("Case %d: %lld\n",tc,d/2ll);
		tc++;
	}
}
