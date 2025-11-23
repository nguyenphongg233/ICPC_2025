// 23 - 12 - 23 

#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)2000 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;

using namespace std;

int n,m;
signed main() {
    read();
    
    if(ifstream("jakarta.inp")){
        freopen("jakarta.inp","r",stdin);
        //freopen("jakarta.out","w",stdout);
    }
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> slots[2];
    for (int j = 0; j < m; ++j) {
        if (j % 2 == 0) slots[0].push_back(j);
        else slots[1].push_back(j);
    }

    int cap[2];
    cap[0] = slots[0].size();
    cap[1] = slots[1].size();

    vector<vector<bool>> dp(n, vector<bool>(2, false));
    vector<vector<int>> trace(n, vector<int>(2, -1));

    if (a[0] <= cap[0]) dp[0][0] = true;
    if (a[0] <= cap[1]) dp[0][1] = true;

    for (int i = 1; i < n; ++i) {
        for (int cur = 0; cur < 2; ++cur) {
            if (a[i] > cap[cur]) continue;
            for (int prev = 0; prev < 2; ++prev) {
                if (dp[i - 1][prev]) {
                    bool ok = false;
                    if (cur != prev) {
                        ok = true;
                    } else {
                        if (a[i] + a[i - 1] <= cap[cur]) {
                            ok = true;
                        }
                    }

                    if (ok) {
                        dp[i][cur] = true;
                        trace[i][cur] = prev;
                        break;
                    }
                }
            }
        }
    }

    int last_type = -1;
    if (dp[n - 1][0]) last_type = 0;
    else if (dp[n - 1][1]) last_type = 1;

    if (last_type == -1) {
        cout << -1 << "\n";
    } else {
        vector<int> types(n);
        types[n - 1] = last_type;
        for (int i = n - 1; i > 0; --i) {
            types[i - 1] = trace[i][types[i]];
        }

        vector<string> grid(n, string(m, '0'));
        bool from_start = true;

        for (int i = 0; i < n; ++i) {
            int t = types[i];
            if (i > 0 && types[i] != types[i - 1]) {
                from_start = true;
            }

            if (from_start) {
                for (int k = 0; k < a[i]; ++k) {
                    grid[i][slots[t][k]] = '1';
                }
                from_start = false;
            } else {
                int sz = slots[t].size();
                for (int k = 0; k < a[i]; ++k) {
                    grid[i][slots[t][sz - 1 - k]] = '1';
                }
                from_start = true;
            }
        }

        for (int i = 0; i < n; ++i) {
            cout << grid[i] << "\n";
        }
    }

    return 0;
}