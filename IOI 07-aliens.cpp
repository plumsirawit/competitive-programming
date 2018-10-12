#include <bits/stdc++.h>
using namespace std;
enum dir{
	up, down, lleft, rright
};
long long n;
const pair<long long,long long> NOPE = make_pair(-1,-1);
map<pair<long long,long long>,bool> mp;
bool query(long long x,long long y){
	if(x <= 0 || y <= 0 || x > n || y > n) return false;
	if(mp.find(make_pair(x,y)) != mp.end()) return mp[make_pair(x,y)];
	printf("examine %lld %lld\n",x,y);
	fflush(stdout);
	char in[8];
	scanf("%s",in);
	mp[make_pair(x,y)] = in[0] == 't';
	return in[0] == 't';
}
long long topbound;
long long bottombound;
pair<long long,long long> search(long long x,long long y,dir d){
	int sstate = 0;
	long long yy = y;
	long long xx = x;
	if(d == up){
		for(long long i = 1; yy+i <= n; i *= 2ll){
			if(query(x,yy+i)){
				if(sstate == 1){
					return make_pair(x,yy+i);
				}
			}else{
				if(sstate == 0){
					yy += i;
					topbound = yy;
					sstate = 1;
					i /= 4ll;
					if(i < 1ll) i = 1ll;
				}
			}
		}
		return NOPE;
	}else if(d == down){
		for(long long i = 1; yy-i > 0ll; i *= 2ll){
			if(query(x,yy-i)){
				if(sstate == 1){
					return make_pair(x,yy-i);
				}
			}else{
				if(sstate == 0){
					yy -= i;
					bottombound = yy;
					sstate = 1;
					i /= 4ll;
					if(i < 1ll) i = 1ll;
				}
			}
		}
		return NOPE;
	}else if(d == lleft){
		for(long long i = 1; xx-i > 0ll; i *= 2ll){
			if(query(xx-i,y)){
				if(sstate == 1){
					return make_pair(xx-i,y);
				}
			}else{
				if(sstate == 0){
					xx -= i;
					sstate = 1;
					i /= 4ll;
					if(i < 1ll) i = 1ll;
				}
			}
		}
		return NOPE;
	}else{
		for(long long i = 1; xx+i <= n; i *= 2ll){
			if(query(xx+i,y)){
				if(sstate == 1){
					return make_pair(xx+i,y);
				}
			}else{
				if(sstate == 0){
					xx += i;
					sstate = 1;
					i /= 4ll;
					if(i < 1ll) i = 1ll;
				}
			}
		}
		return NOPE;
	}
}
long long getsidelength(long long x,long long y){
	long long byu = -1ll;
	long long byd = -1ll;
	long long hi = topbound-y;
	long long lo = 0ll;
	long long mid;
	while(lo < hi){
		mid = (lo + hi)/2ll;
		if(query(x,y+mid)){
			lo = mid+1ll;
		}else{
			hi = mid;
		}
	}
	byu = y+lo;
 
	hi = y-bottombound;
	lo = 0ll;
	while(lo < hi){
		mid = (lo + hi)/2ll;
		if(query(x,y-mid)){
			lo = mid+1ll;
		}else{
			hi = mid;
		}
	}
	byd = y-lo;
	return byu - byd - 1ll;
}
int main(){
	scanf("%lld",&n);
	long long x0,y0;
	scanf("%lld%lld",&x0,&y0);
	topbound = n+1;
	bottombound = 0;
	auto v0 = search(x0,y0,up);
	auto v1 = search(x0,y0,down);
	if(topbound > n+1) topbound = n+1;
	if(bottombound < 0) bottombound = 0;
	long long m = getsidelength(x0,y0);
	//printf("%lld\n",m);
	auto v2 = search(x0,y0,lleft);
	auto v3 = search(x0,y0,rright);
	int mask = 0;
	if(v0 != NOPE) mask++;
	mask *= 2;
	if(v1 != NOPE) mask++;
	mask *= 2;
	if(v2 != NOPE) mask++;
	mask *= 2;
	if(v3 != NOPE) mask++;
	pair<long long,long long> nxt;
	//printf("DBG %d\n",mask);
	switch(mask){
		case 5:
		nxt = search(v1.first,v1.second,down);
		if(nxt == NOPE){
			nxt.first = x0 + m;
			nxt.second = y0 - m;
		}else{
			nxt.first = v1.first + 2ll*m;
			nxt.second = v1.second;
		}
		break;
 
		case 6:
		nxt = search(v1.first,v1.second,down);
		if(nxt == NOPE){
			nxt.first = x0 - m;
			nxt.second = y0 - m;
		}else{
			nxt.first = v1.first - 2ll*m;
			nxt.second = v1.second;
		}
		break;
 
		case 7:
		nxt = v1;
		break;
 
		case 9:
		nxt = search(v0.first,v0.second,up);
		if(nxt == NOPE){
			nxt.first = x0 + m;
			nxt.second = y0 + m;
		}else{
			nxt.first = v0.first + 2ll*m;
			nxt.second = v0.second;
		}
		break;
 
		case 10:
		nxt = search(v0.first,v0.second,up);
		if(nxt == NOPE){
			nxt.first = x0 - m;
			nxt.second = y0 + m;
		}else{
			nxt.first = v0.first - 2ll*m;
			nxt.second = v0.second;
		}
		break;
 
		case 11:
		nxt = v0;
		break;
 
		case 13:
		nxt = v3;
		break;
 
		case 14:
		nxt = v2;
		break;
 
		case 15:
		nxt = make_pair(x0,y0);
		break;
	}
	long long x = nxt.first;
	long long y = nxt.second;
	//printf("DBGDBG %d %d\n",x,y);
	long long lo = 0ll;
	long long hi = m;
	long long mid;
	long long byd = 0ll;
	long long bxl = 0ll;
 
	lo = 0ll;
	hi = m;
	while(lo < hi){
		mid = (lo + hi)/2ll;
		if(query(x,y-mid)){
			lo = mid+1ll;
		}else{
			hi = mid;
		}
	}
	byd = y-lo;
 
	lo = 0ll;
	hi = m;
	while(lo < hi){
		mid = (lo + hi)/2ll;
		if(query(x-mid,y)){
			lo = mid+1ll;
		}else{
			hi = mid;
		}
	}
	bxl = x-lo;
	
	printf("solution %lld %lld\n",bxl + m/2ll + 1ll,byd + m/2ll + 1ll);
	return 0;
}
