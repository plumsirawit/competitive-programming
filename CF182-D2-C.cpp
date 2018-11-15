/*
In this problem, I will define a 'block' as a continuous subarray of the array 'a' with 'len' elements.
To solve the problem, query every block and find the maximum of the outcomes.
Observe that instead of pre-selecting k operations at the start, it is possible to select k operations at each query.
To maximize the modular sum of a given block, the sum should be either as negative as possible (min) or either as positive as possible (max).
So 
1. I select a subset of k elements that is maximum (from max to k-th max) from the set of positive number in the block
and negate all of them.
2. I select a subset of k elements that is minimum from the set of negative number in the block and negate (to positive) all of them.
I simulated both options and tracked maximum modular sum using maintainance of a self-balancing binary search tree (Treap in this case).
Expected Time: O(N log N)
*/
#include <bits/stdc++.h>
using namespace std;
uniform_int_distribution<int> uid(-1000000000,1000000000);
default_random_engine dre;
class tnode{
public:
	int value;
	long long sum;
	int sz;
	int prior;
	tnode* l;
	tnode* r;
	tnode(int x = 0){
		value = x;
		sum = value;
		prior = uid(dre);
		sz = 1;
		l = r = NULL;
	}
};
int gsz(tnode* t){
	return t ? t->sz : 0;
}
long long gsum(tnode* t){
	return t ? t->sum : 0ll;
}
void upd(tnode* t){
	if(!t) return;
	t->sum = gsum(t->l) + gsum(t->r) + (long long)t->value;
	t->sz = gsz(t->l) + gsz(t->r) + 1;
}
void split(tnode* t,int k,tnode*& l,tnode*& r){
	upd(t);
	if(t == NULL) l = r = NULL;
	else if(gsz(t->l) >= k) split(t->l,k,l,t->l), r = t;
	else split(t->r,k-gsz(t->l)-1,t->r,r), l = t;
	upd(l);
	upd(r);
}
void merge(tnode*& t,tnode* l,tnode* r){
	upd(l);
	upd(r);
	if(!l || !r) t = l ? l : r;
	else if(l->prior < r->prior) merge(r->l,l,r->l), t = r;
	else merge(l->r,l->r,r), t = l;
	upd(t);
}
void insert(tnode*& t,int x){
	if(!t) t = new tnode(x);
	else if(t->value < x) insert(t->r,x);
	else if(t->value == x && uid(dre) % 2 == 0) insert(t->r,x);
	else insert(t->l,x);
	upd(t);
}
void remove(tnode*& t,int x){
	if(!t) throw 0;
	else if(t->value < x) remove(t->r,x);
	else if(t->value == x) merge(t,t->l,t->r);
	else remove(t->l,x);
	upd(t);
}
long long extract(tnode*& t1, tnode*& t2, int k){
	long long v1 = 0ll;
	long long v2 = 0ll;
	if(k == 0) return abs(gsum(t1) - gsum(t2));
	if(gsz(t1) <= k){
		v1 = gsum(t1);
	}else{
		int n = gsz(t1);
		tnode* tb1;
		tnode* tb2;
		split(t1,n-k,tb1,tb2);
		v1 = gsum(tb2);
		merge(t1,tb1,tb2);
	}
	if(gsz(t2) <= k){
		v2 = gsum(t2);
	}else{
		int n = gsz(t2);
		tnode* tb1;
		tnode* tb2;
		split(t2,n-k,tb1,tb2);
		v2 = gsum(tb2);
		merge(t2,tb1,tb2);
	}
	return max(llabs(gsum(t1) - gsum(t2) - 2ll * v1),
		llabs(gsum(t1) - gsum(t2) + 2ll * v2));
}
int a[100005];
int main(){
	int n,len;
	scanf("%d%d",&n,&len);
	for(int i = 1; i <= n; i++){
		scanf("%d",a+i);
	}
	int k;
	scanf("%d",&k);
	tnode* rpos = NULL;
	tnode* rneg = NULL;
	long long mx = 0ll;
	int ps = 0;
	int pn = 0;
	for(int i = 1; i <= len; i++){
		if(a[i] >= 0) insert(rpos,a[i]), ps++;
		else insert(rneg,-a[i]), pn++;
		tnode* tb1;
		tnode* tb2;
		split(rpos,ps/2,tb1,tb2);
		merge(rpos,tb1,tb2);
		split(rneg,pn/2,tb1,tb2);
		merge(rneg,tb1,tb2);
	}
	mx = extract(rpos,rneg,k);
	for(int i = len+1; i <= n; i++){
		if(a[i-len] >= 0) remove(rpos,a[i-len]);
		else remove(rneg,-a[i-len]);
		if(a[i] >= 0) insert(rpos,a[i]);
		else insert(rneg,-a[i]);
		mx = max(mx,extract(rpos,rneg,k));
	}
	printf("%lld\n",mx);
	return 0;
}
