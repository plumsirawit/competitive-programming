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
