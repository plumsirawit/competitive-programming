#include <bits/stdc++.h>
using namespace std;
int p[2048];
int s[2048];
int mp[2048];
int main(){
	int n;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++){
		scanf("%d",p+i);
	}
	for(int i = 1; i <= n; i++){
		scanf("%d",s+i);
		mp[s[i]] = i;
	}
	for(int i = 1; i <= n; i++){
		p[i] = mp[p[i]];
	}
	long long s = 0ll;
	vector<pair<int,int> > ans;
	for(int cn = n; cn > 0; cn--){
		int idx = -1;
		for(int i = 1; i <= cn; i++){
			if(p[i] == cn){
				idx = i;
				break;
			}
		}
		for(int i = idx+1; i <= cn; i++){
			if(p[i] <= idx){
				ans.emplace_back(idx,i);
				swap(p[i],p[idx]);
				s += (long long)(i - idx);
				idx = i;
			}
		}
	}
	printf("%lld\n",s);
	printf("%d\n",ans.size());
	for(auto x : ans){
		printf("%d %d\n",x.first,x.second);
	}
	return 0;
}
