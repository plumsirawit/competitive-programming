/*
Initial idea: For every 5 points there will be at least 3 points collinear.
Loop and check all the C(5,3) ways and check what triple is collinear.
Suppose (u,v,w) is collinear, fix w and then checking every (i,i+1) whether it belongs in the same line as (u,v,w) or not.
If it does not belong in the same line, i or i+1 must be in the different line.
If i is in the different line, i is saved to 'used'.
Else, i+1 is saved to 'used'.
Buf if 'used' is defined, there is already a point that is not in the line of (u,v,w), then the currently used and the 'used'
belongs to the same line which is not the same line as (u,v,w).
Repeat the process as it can be proved that if there exists at least 3 points in another line, then this algorithm will produce the correct answer.
But if there is just one point left after the process, that point must not be in the the same line as (u,v,w) for sure.
(If it is, then there is less than 3 points in another line, which contradicts the statement.)
*/
#include <bits/stdc++.h>
#include "office.h"
using namespace std;
int main(){
	int n = GetN();
	int use = -1;
	if(isOnLine(1,2,3)){
		for(int i = 4; i+1 <= n; i += 2){
			if(!isOnLine(1,i,i+1)){
				int b1 = isOnLine(1,2,i);
				if(!b1){
					if(use == -1){
						use = i;
					}else{
						Answer(1,2,use,i);
						return 0;
					}
				}else{
					if(use == -1){
						use = i+1;
					}else{
						Answer(1,2,use,i+1);
						return 0;
					}
				}
			}
		}
		Answer(1,2,use,n);
	}else if(isOnLine(1,4,5)){
		if(isOnLine(1,3,4)) use = 3;
		else use = 2;
		for(int i = 6; i+1 <= n; i += 2){
			if(!isOnLine(1,i,i+1)){
				int b1 = isOnLine(1,4,i);
				if(!b1){
					Answer(1,4,use,i);
					return 0;
				}else{
					Answer(1,4,use,i+1);
					return 0;
				}
			}
		}
		Answer(1,4,use,n);
	}else if(isOnLine(2,3,4)){
		for(int i = 6; i+1 <= n; i += 2){
			if(!isOnLine(2,i,i+1)){
				int b1 = isOnLine(2,3,i);
				if(!b1){
					Answer(2,3,1,i);
					return 0;
				}else{
					Answer(2,3,1,i+1);
					return 0;
				}
			}
		}
		Answer(2,3,1,n);
	}else if(isOnLine(1,3,4)){
		Answer(1,3,2,5);
	}else{
		if(isOnLine(2,3,5)){
			Answer(1,4,2,3);
		}else if(isOnLine(2,4,5)){
			Answer(1,3,2,4);
		}else if(isOnLine(3,4,5)){
			Answer(1,2,3,4);
		}else if(isOnLine(1,2,4)){
			Answer(1,2,3,5);
		}else if(isOnLine(1,2,5)){
			Answer(1,2,3,4);
		}else if(isOnLine(1,3,5)){
			Answer(1,3,2,4);
		}else{
			throw 0;
		}
	}
}
