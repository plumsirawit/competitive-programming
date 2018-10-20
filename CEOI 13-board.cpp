#include <bits/stdc++.h>
using namespace std;
char a[100005];
char b[100005];
class holder{
public:
  vector<int> masker;
  bool updt = false;
  holder& operator=(const holder& y){
    masker = y.masker;
    updt = y.updt;
    return *this;
  }
  int length(){
    return masker.size();
  }
  int gint(){
    int ret = 0;
    for(int i = max((int)masker.size()-19,0); i < (int)masker.size(); i++){
      ret *= 2;
      ret += (int)masker[i];
    }
    return ret;
  }
  void update(){
    updt = false;
    for(int i = masker.size()-1; i > 0 && i > (int)masker.size()-20; i--){
      if(masker[i] > 1){
        masker[i-1] += masker[i]/2;
        masker[i] &= 1;
      }
      if(masker[i] < 0){
        masker[i-1] += (masker[i]-1)/2;
        masker[i] &= 1;
      }
    }
  }
  void move(char x){
    switch(x){
    case '1':
      if(updt) update();
      masker.push_back(0);
      break;
    case '2':
      if(updt) update();
      masker.push_back(1);
      break;
    case 'U':
      if(updt) update();
      masker.pop_back();
      break;
    case 'L':
      masker.back()--;
      updt = true;
      break;
    case 'R':
      masker.back()++;
      updt = true;
      break;
    }
  }
};
int hsh[100005];
int mem[100005];
int main(){
  scanf("%s",a);
  scanf("%s",b);
  holder ma,mb;
  for(int i = 0; a[i]; i++){
    ma.move(a[i]);
  }
  ma.update();
  for(int i = 0; b[i]; i++){
    mb.move(b[i]);
  }
  mb.update();
  if(ma.length() < mb.length()){
    swap(ma,mb);
  }
  int lla = ma.length();
  int llb = mb.length();
  while(ma.length() > mb.length()){
    ma.move('U');
  }
  int d = lla + llb;
  int cur = 0;
  int rig = 0;
  for(int i = 0; i < mb.length(); i++){
    if(!rig && ma.masker[i] != mb.masker[i]){
      if(ma.masker[i] < mb.masker[i]) rig = 2;
      else rig = 1;
    }
    cur *= 2;
    if(rig == 1) cur += ma.masker[i] - mb.masker[i];
    else cur += mb.masker[i] - ma.masker[i];
    d = min(d,cur + lla - 2*i + llb - 2);
    if(cur > d) break;
  }
  printf("%d\n",d);
  return 0;
}
