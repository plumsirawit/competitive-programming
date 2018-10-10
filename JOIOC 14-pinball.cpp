#include <bits/stdc++.h>
using namespace std;
const int MXN = 1 << 17;
long long dp1[MXN];
long long dp2[MXN];
long long dp1h[3*MXN];
long long dp2h[3*MXN];
long long segT1[12*MXN];
long long segT2[12*MXN];
int lb[12*MXN];
int rb[12*MXN];
void build(int c,int l,int r){
	lb[c] = l;
	rb[c] = r;
	if(l == r){
		segT1[c] = dp1h[l];
		segT2[c] = dp2h[l];
		return;
	}
	int k = (l+r)/2;
	build(2*c,l,k);
	build(2*c+1,k+1,r);
	segT1[c] = min(segT1[2*c],segT1[2*c+1]);
	segT2[c] = min(segT2[2*c],segT2[2*c+1]);
}
void update1(int c,int idx){
	if(lb[c] == rb[c]){
		segT1[c] = dp1h[idx];
		return;
	}
	int k = (lb[c] + rb[c])/2;
	if(idx <= k){
		update1(2*c,idx);
	}else{
		update1(2*c+1,idx);
	}
	segT1[c] = min(segT1[2*c],segT1[2*c+1]);
}
void update2(int c,int idx){
	if(lb[c] == rb[c]){
		segT2[c] = dp2h[idx];
		return;
	}
	int k = (lb[c] + rb[c])/2;
	if(idx <= k){
		update2(2*c,idx);
	}else{
		update2(2*c+1,idx);
	}
	segT2[c] = min(segT2[2*c],segT2[2*c+1]);
}
long long query1(int c,int l,int r){
	if(lb[c] == l && rb[c] == r) return segT1[c];
	int k = (lb[c] + rb[c])/2;
	if(l <= k && k < r){
		return min(query1(2*c,l,k),query1(2*c+1,k+1,r));
	}else if(r <= k){
		return query1(2*c,l,r);
	}else{
		return query1(2*c+1,l,r);
	}
}
long long query2(int c,int l,int r){
	if(lb[c] == l && rb[c] == r) return segT2[c];
	int k = (lb[c] + rb[c])/2;
	if(l <= k && k < r){
		return min(query2(2*c,l,k),query2(2*c+1,k+1,r));
	}else if(r <= k){
		return query2(2*c,l,r);
	}else{
		return query2(2*c+1,l,r);
	}
}
int main(){
	int m,n;
	scanf("%d%d",&m,&n);
	vector<tuple<int,int,int,int> > data;
	vector<int> cprs;
	for(int i = 0; i < m; i++){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		data.emplace_back(a,b,c,d);
		cprs.push_back(a);
		cprs.push_back(b);
		cprs.push_back(c);
		dp1[i] = dp2[i] = 1e18;
	}
	sort(cprs.begin(),cprs.end());
	cprs.resize(unique(cprs.begin(),cprs.end()) - cprs.begin());
	for(int i = 0; i < cprs.size(); i++){
		dp1h[i] = dp2h[i] = 1e18;
	}
	build(1,0,cprs.size()-1);
	for(int i = 0; i < m; i++){
		int idx = lower_bound(cprs.begin(),cprs.end(),get<2>(data[i])) - cprs.begin();
		if(get<0>(data[i]) == 1){
			dp1[i] = get<3>(data[i]);
			dp1h[idx] = min(dp1h[idx],dp1[i]);
			update1(1,idx);
		}
		if(get<1>(data[i]) == n){
			dp2[i] = get<3>(data[i]);
			dp2h[idx] = min(dp2h[idx],dp2[i]);
			update2(1,idx);
		}
		dp1[i] = min(dp1[i],(long long)get<3>(data[i]) + query1(1,
			lower_bound(cprs.begin(),cprs.end(),
				get<0>(data[i])) - cprs.begin(),
			lower_bound(cprs.begin(),cprs.end(),
				get<1>(data[i])) - cprs.begin())
		);
		dp1h[idx] = min(dp1h[idx],dp1[i]);
		update1(1,idx);

		dp2[i] = min(dp2[i],(long long)get<3>(data[i]) + query2(1,
			lower_bound(cprs.begin(),cprs.end(),
				get<0>(data[i])) - cprs.begin(),
			lower_bound(cprs.begin(),cprs.end(),
				get<1>(data[i])) - cprs.begin())
		);
		dp2h[idx] = min(dp2h[idx],dp2[i]);
		update2(1,idx);
		
	}
	long long mn = 1e18;
	for(int i = 0; i < m; i++){
		mn = min(mn,dp1[i] + dp2[i] - get<3>(data[i]));
	}
	if(mn == 1e18){
		printf("-1\n");
	}else{
		printf("%lld\n",mn);
	}
	return 0;
}
