#include "ricehub.h"
#include <deque>
using namespace std;
 
int besthub(int R, int L, int X[], long long B)
{
	int lo = 0;
	int hi = R;
	int mid;
	long long QS[R];
	QS[0] = X[0];
	for(int i = 1; i < R; i++){
		QS[i] = QS[i-1] + (long long)X[i];
	}
	while(lo < hi){
		mid = (lo + hi + 1)/2;
		int md = mid/2;
		int first = 0;
		long long s = QS[mid-1] - QS[mid/2] - (long long)(mid-mid/2-1)*X[mid/2] +
			(long long)(mid/2)*X[mid/2] - QS[mid/2-1];
		for(int i = mid; i < R; i++){
			md = (2*i - mid)/2;
			first = i-mid+1;
			s = min(s,QS[i] - QS[md] - (long long)(i-md)*X[md] + (long long)(md-first)*X[md] - QS[md-1] + QS[first-1]);
			//if(s == 1ll) printf("DBG %lld %d %d\n",s,mid,i);
		}
		if(s <= B){
			lo = mid;
		}else{
			hi = mid-1;
		}
	}
	return lo;
}
