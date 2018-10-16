/*
 * My initial idea came from the problem 76F in codeforces.
 * Link: http://codeforces.com/contest/76/problem/F
 * 
 * I used longest increasing subsequence to help, but in this problem,
 * the main thing changed a bit. Instead of asking the length of longest
 * increasing subsequence, the problem asks for the minimum number of
 * increasing subsequences used to cover the entire sequence.
 * 
 * In this case, I used a (bit-like dp style) idea. At the position i,
 * I check if I can append the value at position i into a subsequence ending at
 * j for some j < i. Using multiset, greedily, I can easily check the statement.
 * And if it does not exist, I create a new subsequence of that element alone,
 * and the answer is incremented by one.
 */
#include <bits/stdc++.h>
using namespace std;
int used[100005];
int main(){
	int n;
	scanf("%d",&n);
	int s,t;
	vector<pair<int,int> > v;
	for(int i = 1; i <= n; i++){
		scanf("%d%d",&s,&t);
		v.emplace_back(t+s,t-s);
	}
	vector<pair<int,int> > w;
	sort(v.begin(),v.end());
	multimap<int,int> ok;
	int cc = 1;
	used[0] = cc;
	ok.insert(make_pair(v[0].second,cc));
	for(int i = 1; i < v.size(); i++){
		auto it = ok.upper_bound(v[i].second);
		if(it == ok.begin()){
			used[i] = ++cc;
			ok.insert(make_pair(v[i].second,used[i]));
			continue;
		}
		it--;
		used[i] = it->second;
		ok.erase(it);
		ok.insert(make_pair(v[i].second,used[i]));
	}
	printf("%d\n",cc);
	for(int i = 0; i < n; i++){
		printf("%d %d %d\n",(v[i].first - v[i].second)/2,(v[i].first + v[i].second)/2, used[i]);
	}
}
