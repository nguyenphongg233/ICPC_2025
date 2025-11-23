// 23 - 12 - 23 

#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right Now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)2e5 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;

int n;
char c[3][MAX];
int a[MAX];
int maxl[MAX],maxr[MAX];
int nextr[MAX];

int st[MAX << 2];
void update(int u,int val,int id = 1,int l = 1,int r = n){
    if(u > r || u < l)return;
    if(l == r){
        st[id] = val;
        return;
    }
    int mid = l + r >> 1;
    update(u,val,id << 1,l,mid);
    update(u,val,id << 1 | 1,mid + 1,r);
    st[id] = max(st[id << 1],st[id << 1 | 1]);
}
int get(int u,int v,int id = 1,int l = 1,int r = n){
    if(u > r || v < l)return -INF;
    if(u <= l && r <= v)return st[id];
    int mid = l + r >> 1;
    return max(get(u,v,id << 1,l,mid),get(u,v,id << 1 | 1,mid + 1,r));
}
signed main(){
    
    read();
    
    if(ifstream("jakarta.inp")){
        freopen("jakarta.inp","r",stdin);
        //freopen("jakarta.out","w",stdout);
    }
    cin >> n;
    for(int i = 0;i < 3;i++){
        for(int j = 1;j <= n;j++){
            cin >> c[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        if(c[0][i] == '#' || c[2][i] == '#')a[i] = 2;
        else if(c[1][i] == '#') a[i] = 1;
        else a[i] = 0;
    }

    int pref = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] == 0)pref++;
        else pref = 0;
        maxl[i] = max(maxl[i - 1],pref);    
    }
    pref = 0;

    nextr[n + 1] = n + 1;
    for(int i = n;i >= 1;i--){
        if(a[i] == 0){
            pref++;
            if(nextr[i + 1] == n + 1)nextr[i] = i;
            else nextr[i] = nextr[i + 1];
        }else if(a[i] == 2){
            nextr[i] = n + 1;
            pref = 0;
        }else {
            nextr[i] = nextr[i + 1];
            pref = 0;
        }
        maxr[i] = max(maxr[i + 1],pref);
        if(maxr[i + 2] > 0){
            update(i,maxr[i + 2] * 3 + 2 * i);
        }else update(i,-INF);
    }

    int best_sum = -1;
    for(int i = 1;i <= n;i++){
        int cur_sum = maxl[i - 2];
        if(cur_sum == 0)continue;
        if(a[i] != 0)continue;
        
        int l = i;
        int r = nextr[i];

        if(l == r)continue;

        //cout << l << " " << r << '\n';
        int cur_r = maxr[r + 2];

        if(cur_r > 0 && cur_r + cur_sum >= (r - l + 1)){
            best_sum = max(best_sum,(r - l + 1) * 3 + (r - l + 1) * 2 + 2);
          //  cerr << cur_sum << "-- " << l << " " << r << " " << cur_r << "\n";
            continue;
        }

        for(int j = r;j >= l + 2;j--){
            if(a[j] != 0)continue;
            cur_r = maxr[j + 2];
            if(cur_r == 0)continue;
            if(cur_r + cur_sum >= (j - l + 1)){
            //    cerr << cur_sum << " " << l << " " << j << " " << cur_r << "\n";
                best_sum = max(best_sum,(j - l + 1) * 3 + (j - l + 1) * 2 + 2);
                break;
            }else{
              //  cerr << cur_sum << " " << l << " " << j << " " << cur_r << "\n";
                best_sum = max(best_sum,cur_sum * 3 + cur_r * 3 + 2 * (j - l + 1) + 2);
            }
        }
        //cout << best_sum << "\n";
    }

    cout << best_sum << "\n";

}