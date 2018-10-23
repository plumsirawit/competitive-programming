#include <bits/stdc++.h>
using namespace std;
int a[5005];
int dist[50005];
class state{
public:
	int cur;
	int cw;
	state(int a,int b){
		cur = a;
		cw = b;
	}
	friend bool operator<(state x,state y){
		return x.cw > y.cw;
	}
};
int main(){
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++){
		scanf("%d",a+i);
	}
	memset(dist,0x3F,sizeof(dist));
	dist[0] = 0;
	priority_queue<state> pq;
	pq.emplace(0,0);
	while(!pq.empty()){
		state cur = pq.top();
		pq.pop();
		if(cur.cw > dist[cur.cur]) continue;
		for(int i = 1; i < n; i++){
			if(dist[(cur.cur + a[i]) % a[0]] > cur.cw + a[i]){
				dist[(cur.cur + a[i]) % a[0]] = cur.cw + a[i];
				pq.emplace((cur.cur + a[i]) % a[0],cur.cw + a[i]);
			}
		}
	}
	int k;
	scanf("%d",&k);
	int x;
	for(int i = 0; i < k; i++){
		scanf("%d",&x);
		if(dist[x % a[0]] <= x){
			printf("TAK\n");
		}else{
			printf("NIE\n");
		}
	}
	return 0;
}
