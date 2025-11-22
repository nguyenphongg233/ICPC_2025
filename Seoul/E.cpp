#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define all(a) a.begin(), a.end()
#define sz(a) ((int)a.size())
#ifdef TUDIV
template <typename T>
ostream& operator << (ostream &o, vector <T> vec) {
    o << "{"; int f = 0;
    for (T i : vec) o << (f++ ? " " : "") << i;
    return o << "}"; }
void bug__(int c, auto ...a) {
    cerr << "\e[1;" << c << "m";
    (..., (cerr << a << " "));
    cerr << "\e[0m" << endl; }
#define bug_(c, x...) bug__(c, __LINE__, "[" + string(#x) + "]", x)
#define bug(x...) bug_(32, x)
#define bugv(x...) bug_(36, vector(x))
#define safe bug_(33, "safe")
#else
#define bug(x...) void(0)
#define bugv(x...) void(0)
#define safe void(0)
#endif
const int mod = 998244353, N = 5e3 + 5;
const int inf = 1e9 + 7;

int n;
vector<int> adj[N];
int dp[N][N];
int sub[N];
int f[N];
int bestL[N], bestR[N];
// node u, left


void minimize(int &res, int val) {
    res = min(res, val);
}


int dfs(int u, int par) {
    dp[u][0] = 0;
    sub[u] = 0;
    for(int v : adj[u]) {
        if(v == par) continue;
        dfs(v, u);
    }

    sort(adj[u].begin(), adj[u].end(), [&](int x, int y){
        return sub[x] < sub[y];
    });

    for(int v : adj[u]) {
        if(v == par) continue;
        for(int w = sub[u] + sub[v]; w >= 0; --w) {
            f[w] = inf;
            if(w >= sub[v]) {
                minimize(f[w], dp[u][w - sub[v]] + bestL[v] + w);
            }
            if(w <= sub[u]) minimize(f[w], dp[u][w] + (sub[u] - w) + sub[v] + bestR[v]);
        }

        for(int w = sub[u] + sub[v]; w >= 0; --w) {
            dp[u][w] = f[w];
        }

        sub[u] += sub[v];
    }

    bestL[u] = bestR[u] = inf;
    int res = inf;
    for(int w = 0; w <= sub[u]; ++w) {
        minimize(res, dp[u][w]);
        minimize(bestL[u], dp[u][w] - w);
        minimize(bestR[u], dp[u][w] - sub[u] + w);
    }
    bug(res);
    bug(u);
    bug(bestL[u]);
    bug(bestR[u]);
    sub[u] += 1;
    return res;
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    
    
    cin >> n;
    memset(dp, 0x3f, sizeof dp);

    for(int i = 0; i < n - 1; ++i) {
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    cout << dfs(1, -1);
}