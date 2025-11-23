// 23 - 12 - 23 

#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right now Is : "<<x<<"\n"

#define int long long
#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)2000 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)998244353;

using namespace std;

int n,a[MAX];
int bit[MAX];

void update(int id,int val){
    for(;id <= n;id += id & -id)bit[id] += val;
}
int get(int id){
    int res = 0;
    for(;id > 0;id -= id & -id)res += bit[id];
    return res;
}
signed main(){

    read();

    if(ifstream("jakarta.inp")){
        freopen("jakarta.inp","r",stdin);
        //freopen("jakarta.out","w",stdout);
    }

    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    update(1,1);
    int res = 1;
    for(int i = 2;i <= n;i++){
        int cur = get(a[i] - 1);
        int overa = i - 1 - cur;
        if(overa > 0)continue;
        cout << i << " " << cur << '\n';
        res = (res * cur) % MOD;
        update(a[i],1);
    }
    cout << res;

}