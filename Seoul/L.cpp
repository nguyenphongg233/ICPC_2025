#include <bits/stdc++.h>

#define int long long
#define fi first
#define se second

const int N = 2e5 + 5;
const int K = 1e2 + 5;
const int mod = 1e9 + 7;
const int inf = 1e18 + 7;

#define all(v) (v).begin(), (v).end()
#define pii pair<int, int> 

using namespace std;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());

int n, q, a, b;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    if(ifstream("file.inp")){
    	freopen("file.inp", "r", stdin);
    	freopen("file.out", "w", stdout);
    }
    
    a = 1e9, b = 0;
    cin >> n >> q;
    while(n--) {
    	int l, r, p;
    	cin >> l >> r >> p;
    	a = min(a, r);
    	b = max(b, l);
    }
    while(q--) {
    	int p;
    	cin >> p;
    	int ans = 0;
    	if(a < p) ans = max(ans, p - a);
    	if(p < b) ans = max(ans, b - p);
    	cout << ans << '\n';
    }
    
    return 0;
}

// tuntun
