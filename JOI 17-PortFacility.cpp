#include <bits/stdc++.h>
using namespace std;
vector<int> g[1000005];
int segTmin[4*1000005];
int segTmax[4*1000005];
int lb[4*1000005];
int rb[4*1000005];
vector<tuple<int,int,int> > pts;
int p[1000005];
int bck[2*1000005];
int fn(int x){
	if(p[x] == -1) return x;
	else return p[x] = fn(p[x]);
}
void un(int x,int y){
	x = fn(x);
	y = fn(y);
	if(x != y) p[x] = y;
}
void build(int c,int l,int r){
	lb[c] = l;
	rb[c] = r;
	if(l == r){
		segTmin[c] = get<1>(pts[l]);
		segTmax[c] = get<2>(pts[l]);
		return;
	}
	int k = (l + r)/2;
	build(2*c,l,k);
	build(2*c+1,k+1,r);
	segTmin[c] = min(segTmin[2*c],segTmin[2*c+1]);
	segTmax[c] = max(segTmax[2*c],segTmax[2*c+1]);
}
int querymin(int c,int l,int r){
	if(lb[c] == l && rb[c] == r) return segTmin[c];
	int k = (lb[c] + rb[c])/2;
	if(l <= k && k < r) return min(querymin(2*c,l,k),querymin(2*c+1,k+1,r));
	else if(r <= k) return querymin(2*c,l,r);
	else return querymin(2*c+1,l,r);
}
int querymax(int c,int l,int r){
	if(lb[c] == l && rb[c] == r) return segTmax[c]; 
	int k = (lb[c] + rb[c])/2;
	if(l <= k && k < r) return max(querymax(2*c,l,k),querymax(2*c+1,k+1,r));
	else if(r <= k) return querymax(2*c,l,r);
	else return querymax(2*c+1,l,r);
}
int col[1000005];
bool dfs(int u,int p = -1,int c = 1){
	col[u] = c;
	c = c % 2 + 1;
	for(int v : g[u]){
		if(v == p) continue;
		if(col[v] && col[v] != c) return false;
		if(col[v]) continue;
		if(!dfs(v,u,c)) return false;
	}
	return true;
}
int main(){
	memset(p,-1,sizeof(p));
	int n;
	scanf("%d",&n);
	int a,b;
	for(int i = 0; i < n; i++){
		scanf("%d%d",&a,&b);
		pts.emplace_back(i,a,b);
	}
	sort(pts.begin(),pts.end(),[](tuple<int,int,int> x,tuple<int,int,int> y){
		return get<2>(x) < get<2>(y);
	});
	for(int i = 0; i < n; i++){
		bck[get<1>(pts[i])] = get<0>(pts[i]);
	}
	int c = 0;
	build(1,0,pts.size()-1);
	for(int i = 0; i < n; i++){
		int idx = upper_bound(pts.begin(),pts.end(),make_tuple(0,0,get<1>(pts[i])),[](tuple<int,int,int> x,tuple<int,int,int> y){
			return get<2>(x) < get<2>(y);
		}) - pts.begin();
		if(idx <= i-1 && querymin(1,idx,i-1) < get<1>(pts[i])){
			int l = querymin(1,idx,i-1);
			un(bck[l],get<0>(pts[i]));
			g[bck[l]].push_back(get<0>(pts[i]));
			g[get<0>(pts[i])].push_back(bck[l]);
		}
	}
	sort(pts.begin(),pts.end(),[](tuple<int,int,int> x,tuple<int,int,int> y){
		return get<1>(x) < get<1>(y);
	});
	for(int i = 0; i < n; i++){
		bck[get<2>(pts[i])] = get<0>(pts[i]);
	}
	build(1,0,pts.size()-1);
	for(int i = n-1; i >= 0; i--){
		int idx = lower_bound(pts.begin(),pts.end(),make_tuple(0,get<2>(pts[i]),0),[](tuple<int,int,int> x,tuple<int,int,int> y){
			return get<1>(x) < get<1>(y);
		}) - pts.begin() - 1;
		if(idx >= i+1 && querymax(1,i+1,idx) > get<2>(pts[i])){
			int r = querymax(1,i+1,idx);
			un(bck[r],get<0>(pts[i]));
			g[bck[r]].push_back(get<0>(pts[i]));
			g[get<0>(pts[i])].push_back(bck[r]);
		}
	}
	for(int i = 0; i < pts.size(); i++){
		if(col[i]) continue;
		if(!dfs(i)){
			printf("0\n");
			return 0;
		}
	}
	set<int> s;
	for(int i = 0; i < n; i++){
		s.insert(fn(i));
	}
	c = s.size();
	int ans = 1;
	for(int i = 0; i < c; i++){
		ans *= 2;
		ans %= 1000000007;
	}
	printf("%d\n",ans);
	return 0;
}
