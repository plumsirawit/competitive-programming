#include "wiring.h"
#include <vector>
#include <algorithm>

using namespace std;
long long min_total_length(vector<int> r, vector<int> b) {
	vector<pair<int,bool> > combined;
	vector<long long> qs;
	for(int x : r){
		combined.emplace_back(x,false);
	}
	for(int x : b){
		combined.emplace_back(x,true);
	}
	sort(combined.begin(),combined.end());
	bool cur = !combined.front().second;
	int clen = -1e9;
	int llen = 0;
	int begin = 0;
	vector<int> lpos;
	lpos.resize(combined.size());
	vector<int> laxis;
	laxis.resize(combined.size());
	for(int i = 0; i < combined.size(); i++){
		if(combined[i].second == cur){
			clen++;
		}else{
			begin = i;
			llen = clen;
			clen = 1;
			cur = !cur;
		}
		lpos[i] = 2*begin-i-1;
		laxis[i] = begin;
		if(lpos[i] < begin-llen){
			lpos[i] = -1;
		}
	}
	qs.push_back((long long)combined.front().first);
	for(int i = 1; i < combined.size(); i++){
		qs.push_back(qs.back() + (long long)combined[i].first);
	}
	vector<long long> dp;
	dp.resize(combined.size());
	dp[0] = 1e18;
	if(combined[0].second){
		auto it = lower_bound(r.begin(),r.end(),combined[0].first);
		if(it != r.begin()) dp[0] = min(dp[0],(long long)combined[0].first - (long long)*(it-1));
		if(it != r.end()) dp[0] = min(dp[0], (long long)*it - (long long)combined[0].first);
	}else{
		auto it = lower_bound(b.begin(),b.end(),combined[0].first);
		if(it != b.begin()) dp[0] = min(dp[0], (long long)combined[0].first - (long long)*(it-1));
		if(it != b.end()) dp[0] = min(dp[0], (long long)*it - (long long)combined[0].first);
	}
	for(int i = 1; i < combined.size(); i++){
		// Case 1: dp[i] = dp[i-1] + abs(pos[i] - pos[j])
		dp[i] = 1e18;
		if(combined[i].second){
			auto it = lower_bound(r.begin(),r.end(),combined[i].first);
			if(it != r.begin())
				dp[i] = min(dp[i],dp[i-1] + (long long)combined[i].first - (long long)*(it-1));
			if(it != r.end())
				dp[i] = min(dp[i],dp[i-1] + (long long)*it - (long long)combined[i].first);
		}else{
			auto it = lower_bound(b.begin(),b.end(),combined[i].first);
			if(it != b.begin())
				dp[i] = min(dp[i],dp[i-1] + (long long)combined[i].first - (long long)*(it-1));
			if(it != b.end())
				dp[i] = min(dp[i],dp[i-1] - (long long)combined[i].first + (long long)*it);
		}
		// Case 2: dp[i] = dp[j] + Distance Differences
		if(lpos[i] == 0){
			dp[i] = min(dp[i],qs[i] - qs[laxis[i]-1] - qs[laxis[i]-1]);
		}else if(lpos[i] != -1){
			dp[i] = min(dp[i],qs[i] - qs[laxis[i]-1] - qs[laxis[i]-1] + qs[lpos[i]-1] + dp[lpos[i]-1]);
		}
	}
	return dp.back();
}
