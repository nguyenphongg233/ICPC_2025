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

int n;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    if(ifstream("file.inp")){
    	freopen("file.inp", "r", stdin);
    	freopen("file.out", "w", stdout);
    }
    
    cin >> n;
    if(n == 1) {
    	cout << "1 1 1";
    	return 0;
    }
    if(n % 3 == 2) {
    	for(int i = 1; i <= 3; i++) {
    		for(int j = 1; j <= n; j++) {
    			cout << j << ' ';
    		}
    	}
    }
    else {
    	for(int i = 1; i <= 3; i++) {
    		cout << "1 ";
    		if(i == 2) cout << n << ' ';
    		if(i == 3) cout << n - 1 << ' ' << n << ' ';
    		for(int j = 2; j <= n - i + 1; j++) cout << j << ' ';
    	}
    }
    
    return 0;
}

// tuntun
