/*
    Main idea started by observing the LIS.
    The modifying interval should be used as either a prefix or suffix of the array.
    Because if used randomly in the middle of the LIS, the LIS won't be better.
    
    Now track the length of LIS ending with element i as ends[i].
    Then go back from the end and check if we should modify the interval [i+1, n] by +x (observed that other values is worse than this).
    
    In the same fashion, track the length of LDS ending with element i from backward as ends[i].
    Then go back from the beginning end check if we should modify the interval [1,i-1] by -x.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int t[200005];
int ends[200005];
vector<int> lis;
int main() {
    int n,x;
    scanf("%d%d",&n,&x);
    for(int i = 1; i <= n; i++){
        scanf("%d",t+i);
        auto it = lower_bound(lis.begin(),lis.end(),t[i]);
        if(it == lis.end()){
            lis.push_back(t[i]);
        }else{
            *it = t[i];
        }
        ends[i] = lower_bound(lis.begin(),lis.end(),t[i]) - lis.begin() + 1;
    }
    int ans = lis.size();
    lis.clear();
    for(int i = n; i > 0; i--){
        ans = max(ans,(int)(lower_bound(lis.begin(),lis.end(),t[i],greater<int>()) - lis.begin()) + ends[i]);
        t[i] += x;
        auto it = lower_bound(lis.begin(),lis.end(),t[i],greater<int>());
        if(it == lis.end()){
            lis.push_back(t[i]);
        }else{
            *it = t[i];
        }
        t[i] -= x;
    }
    lis.clear();
    for(int i = n; i > 0; i--){
        auto it = lower_bound(lis.begin(),lis.end(),t[i],greater<int>());
        if(it == lis.end()){
            lis.push_back(t[i]);
        }else{
            *it = t[i];
        }
        ends[i] = lower_bound(lis.begin(),lis.end(),t[i],greater<int>()) - lis.begin() + 1;
    }
    lis.clear();
    for(int i = 1; i <= n; i++){
        ans = max(ans,(int)(lower_bound(lis.begin(),lis.end(),t[i]) - lis.begin()) + ends[i]);
        t[i] -= x;
        auto it = lower_bound(lis.begin(),lis.end(),t[i]);
        if(it == lis.end()){
            lis.push_back(t[i]);
        }else{
            *it = t[i];
        }
        t[i] += x;
    }
    printf("%d\n",ans);
}
