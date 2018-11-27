/*
Maintain a set of available segments sorted by priority given in the problem statement.
Every time there is insertion, select the appropriate segment and split the segment into left and right.
Every time there is erasion, erase the point and merge two segments.
Separately maintain corner cases (i.e. there is only zero or one point).
*/
#include <bits/stdc++.h>
using namespace std;
int where[1000005];
int idAt[200005];
class Compare{
public:
	bool operator()(pair<int,int> x,pair<int,int> y){
		return (x.second - x.first)/2 > (y.second - y.first)/2 ? true : (x.second - x.first)/2 == (y.second - y.first)/2 ? x.first < y.first : false;
	}
};
set<pair<int,int>,Compare> segments;
set<int> parked;
int main(){
	memset(where,-1,sizeof(where));
	memset(idAt,-1,sizeof(idAt));
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < m; i++){
		int t,id;
		scanf("%d%d",&t,&id);
		if(t == 1){
			if(parked.empty()){
				idAt[1] = id;
				where[id] = 1;
				printf("1\n");
				parked.insert(1);
			}else if(parked.size() == 1){
				if(idAt[1] != -1){
					idAt[n] = id;
					where[id] = n;
					segments.emplace(1,n);
					printf("%d\n",n);
					parked.insert(n);
				}else if(idAt[n] != -1){
					idAt[1] = id;
					where[id] = 1;
					printf("1\n");
					segments.emplace(1,n);
					parked.insert(1);
				}else{
					int ix = *parked.begin();
					int iu;
					int dif;
					if(ix - 1 < n - ix){
						iu = n;
						dif = n-ix;
					}else{
						iu = 1;
						dif = ix-1;
					}
					idAt[iu] = id;
					where[id] = iu;
					printf("%d\n",iu);
					if(iu < ix){
						segments.emplace(iu,ix);
					}else if(iu > ix){
						segments.emplace(ix,iu);
					}else{
						throw 0;
					}
					parked.insert(iu);
				}
			}else{
				int i1 = *parked.begin();
				int i2 = *parked.rbegin();
				int iu;
				int dif;
				if(i1 - 1 < n - i2){
					iu = n;
					dif = n-i2;
				}else{
					iu = 1;
					dif = i1-1;
				}
				pair<int,int> place = *segments.begin();
				int use = (place.first + place.second)/2;
				int dx = min(use - place.first, place.second - use);
				if(dif > dx || dif == dx && iu < use){
					idAt[iu] = id;
					where[id] = iu;
					if(iu < *parked.begin()){
						segments.emplace(iu,*parked.begin());
					}else if(iu > *parked.rbegin()){
						segments.emplace(*parked.rbegin(),iu);
					}else{
						throw 0;
					}
					printf("%d\n",iu);
					parked.insert(iu);
				}else{
					segments.erase(segments.begin());
					idAt[use] = id;
					where[id] = use;
					segments.emplace(place.first,use);
					segments.emplace(use,place.second);
					printf("%d\n",use);
					parked.insert(use);
				}
			}
		}else{
			parked.erase(where[id]);
			if(parked.empty()){
				idAt[where[id]] = -1;
				where[id] = -1;
			}else{
				auto it = parked.lower_bound(where[id]);
				if(it == parked.begin()){
					segments.erase(make_pair(where[id],*it));
				}else if(it == parked.end()){
					it--;
					segments.erase(make_pair(*it,where[id]));
				}else{
					int y = *it;
					segments.erase(make_pair(where[id],*it));
					it--;
					int x = *it;
					segments.erase(make_pair(*it,where[id]));
					segments.emplace(x,y);
				}
				idAt[where[id]] = -1;
				where[id] = -1;
			}
		}
	}
}
