#include <bits/stdc++.h>
using namespace std;

int c[20005];
int e[20005];
int a[10005];
int evp[10005][128];
int ans[128][10005];
int bans[128][10005];
int main() {
    int n,l;
    scanf("%d%d",&n,&l);
    for(int i = 1; i <= n; i++){
        scanf("%d",a+i);
    }
    int q;
    scanf("%d",&q);
    vector<pair<int,int> > qrs;
    for(int i = 1; i <= q; i++){
        int x;
        scanf("%d",&x);
        qrs.emplace_back(x,i);
    }
    sort(qrs.begin(),qrs.end());
    for(int d = 1; d <= n; d++){
        memset(c,0,sizeof(c));
        for(int i = 1; i+d <= n; i++){
            if(a[i] != a[i+d]){
                int k = max(i-l+1,1);
                c[d+2*k]++;
                k = min(d+n-l+1,i)+1;
                c[d+2*k]--;
            }
        }
        for(int i = d+2; i+d <= 2*n; i++){
            if((i + d) % 2 == 1) continue;
            e[i] = e[i-2] + c[i];
        }
        for(int i = d+2; i+d <= 2*n; i++){
            if((i + d) % 2 == 1) continue;
            int x = (i-d)/2;
            int y = (i+d)/2;
            if(y > n-l+1) continue;
            int sl = lower_bound(qrs.begin(),qrs.end(),make_pair(e[i],(int)-1e9)) - qrs.begin();
            evp[x][sl]++;
            evp[y][sl]++;
        }
        for(int i = d+2; i+d <= 2*n; i++){
            if((i + d) % 2 == 1) continue;
            e[i] = 0;
        }
    }
    for(int i = 1; i <= n-l+1; i++){
        bans[0][i] = evp[i][0];
        for(int j = 1; j <= q; j++){
            bans[j][i] = bans[j-1][i] + evp[i][j];
        }
    }
    for(int i = 0; i < qrs.size(); i++){
        for(int j = 1; j <= n-l+1; j++){
            ans[qrs[i].second][j] = bans[i][j];
        }
    }
    for(int i = 1; i <= q; i++){
        for(int j = 1; j <= n-l+1; j++){
            printf("%d ",ans[i][j]);
        }
        printf("\n");
    }
    return 0;
}
