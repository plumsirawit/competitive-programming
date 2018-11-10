/*
Observed that the result is a non-increasing sequence.
Count the elements into buckets A and B.
(A[i] denotes how many i is there in the first input, similarly, B[i] : how many i in second input)
Then looped the result from m-1 to 0 and count how many pair of buckets sums to current result:
Loop i from m-1 to 0 then
Loop j from 0 to m-1, j must be matched with something (ex) such that ex + j == i or m+i.
So if i >= j, ex = i-j, else, ex = m+i-j.
I greedily erased the possible pair (j,ex).
The number of pair erased is min(A[j],B[ex]).
Delete those pairs from possible set.
Observed that one of them (A[j] or B[ex]) must be zero after erased.
Observed that when completed loop, the remaining non-zero number will be decreased by half.
This makes |A|+|B| decrased by half in every step.

The bug I encountered (which makes me TLE at test 65) is that counting how many pairs sums to current result efficiently.
I thought every time the loop continues, the elements of set A and B would be decreased by half.
It really decreased. But it's not exact half, and cannot greedily select the smaller one.
So I changed the implementation, instead of picking using set A and B, observe that the total element (|A| + |B|) will
decrease by half every time the loop runs. So I used two pointers, to locate index of current element in A (j),
and to locate index of limiting zeroes in B (rp).
Now the loop can be guaranteed to run in O(log M) due to the erasion of elements by half every time the loop runs.

*/
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int b[100005];
int ans[100005];
set<int> nza; // Non-zeroed A
set<int> nzb; // Non-zeroed B
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		a[x]++;
		nza.insert(x);
	}
	for(int i = 1; i <= n; i++){
		int x;
		scanf("%d",&x);
		b[x]++;
		nzb.insert(x);
	}
	vector<int> q;
	int d;
	for(int i = m-1; i >= 0; i--){
		int j = 0;
		int rp = i;
		for(auto it = nza.begin(); it != nza.end();){
			if(*it > i) break;
			j = *it;
			if(rp < i-j){
				it = nza.lower_bound(i-rp);
				continue;
			}
			if(rp >= i-j){
				if(nzb.find(i-j) != nzb.end()){
					d = min(a[j],b[i-j]);
					a[j] -= d;
					b[i-j] -= d;
					ans[i] += d;
					if(a[j] == 0){
						it = nza.erase(nza.find(j));
					}else{
						it++;
					}
					if(b[i-j] == 0){
						nzb.erase(i-j);
					}
				}else{
					auto itt = nzb.lower_bound(i-j);
					if(itt == nzb.begin()) break;
					itt--;
					rp = *itt;
				}
			}
		}
		rp = m-1;
		for(auto it = nza.upper_bound(i); it != nza.end();){
			j = *it;
			if(rp < m+i-j){
				it = nza.lower_bound(m+i-rp);
				continue;
			}
			if(rp >= m+i-j){
				if(nzb.find(m+i-j) != nzb.end()){
					d = min(a[j],b[m+i-j]);
					a[j] -= d;
					b[m+i-j] -= d;
					ans[i] += d;
					if(a[j] == 0){
						it = nza.erase(nza.find(j));
					}else{
						it++;
					}
					if(b[m+i-j] == 0){
						nzb.erase(m+i-j);
					}
				}else{
					auto itt = nzb.lower_bound(m+i-j);
					if(itt == nzb.begin()) break;
					itt--;
					rp = *itt;
				}
			}
		}
		// if(nzb.size() * nzb.size() < m){
		// 	for(int j : nzb){
		// 		int ex = i >= j ? i - j : m + i - j;
		// 		if(a[ex]){
		// 			d = min(a[ex],b[j]);
		// 			a[ex] -= d;
		// 			b[j] -= d;
		// 			ans[i] += d;
		// 			if(a[ex] == 0){
		// 				nza.erase(ex);
		// 			}
		// 			if(b[j] == 0){
		// 				q.push_back(j);
		// 			}
		// 		}
		// 	}
		// 	while(!q.empty()){
		// 		nzb.erase(q.back());
		// 		q.pop_back();
		// 	}
		// }else{
		// 	for(int j : nza){
		// 		int ex = i >= j ? i - j : m + i - j;
		// 		if(b[ex]){
		// 			d = min(a[j],b[ex]);
		// 			a[j] -= d;
		// 			b[ex] -= d;
		// 			ans[i] += d;
		// 			if(a[j] == 0){
		// 				q.push_back(j);
		// 			}
		// 			if(b[ex] == 0){
		// 				nzb.erase(ex);
		// 			}
		// 		}
		// 	}
		// 	while(!q.empty()){
		// 		nza.erase(q.back());
		// 		q.pop_back();
		// 	}
		// }
	}
	for(int i = m-1; i >= 0; i--){
		for(int j = 0; j < ans[i]; j++){
			printf("%d ",i);
		}
	}
	printf("\n");
	return 0;
}
