#include <bits/stdc++.h>
using namespace std;
string str;
typedef long long ll;
int main(){
	while(!cin.eof()){
		vector<tuple<ll,ll,ll> > v;
		ll x,y,z;
		bool ok = true;
		getline(cin,str);
		while(str[0] != '\r' && str[0] != ' ' && str[0] != '\0'){
			sscanf(str.c_str(),"%lld%lld%lld",&x,&y,&z);
			v.emplace_back(x,y,z);
			if(cin.eof()) break;
			getline(cin,str);
		}
		if(v.empty()) continue;
		long long lo = 0;
		long long hi = 1ll << 32ll;
		long long mid;
		while(lo < hi){
			mid = (lo + hi)/2ll;
			long long s = 0ll;
			for(auto p : v){
				long long x,y,z;
				tie(x,y,z) = p;
				if(x > mid) continue;
				y = min(y,mid);
				s += (y-x)/z+1ll;
			}
			if(s % 2ll == 0ll){
				lo = mid+1ll;
			}else{
				hi = mid;
			}
		}
		long long c = 0ll;
		for(auto p : v){
			long long x,y,z;
			tie(x,y,z) = p;
			if(lo > y) continue;
			if(lo < x) continue;
			if((lo-x) % z == 0ll){
				c++;
			}
		}
		if(c == 0ll){
			printf("no corruption\n");
		}else{
			printf("%lld %lld\n",lo,c);
		}
	}
}
