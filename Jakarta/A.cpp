// 23 - 12 - 23 

#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right Now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)2000 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;

int n,m;
vector<int> adj[MAX];
int deg[MAX];
vector<int> s1,s2;
int del[MAX];
vector<int> g[MAX];
vector<int> ans_q;
vector<int> colc[MAX];

void solve(){
    
    vector<int> col(n + 5);
    for(int i = 1;i <= n;i++)col[i] = -1;

    for(int i = 1;i <= n;i++){
        if(col[i] == -1){
            deque<int> h;
            h.push_back(i);
            col[i] = 0;
            colc[0].push_back(i);
            while(!h.empty()){
                int u = h.front();
                h.pop_front();
                vector<int> c;
                //cout << u << ' ' << col[u] << "\n";
                if(col[u] == -2){
                    for(auto v : adj[u]){
                        if(col[v] != -1 && col[v] != -2)c.push_back(col[v]);
                    }
                    sort(c.begin(),c.end());
                    c.erase(unique(c.begin(),c.end()),c.end());
                    int now_col = 0;
                    for(int i = 0;i < (int)c.size();i++){
                        if(c[i] == now_col){
                            now_col++;
                            continue;
                        }else break;
                    }
                    //cout << c.size() << "-- " << now_col << "\n";
                    col[u] = now_col;
                    colc[now_col].push_back(u);
                }
                for(auto v : adj[u]){
                    if(col[v] != -1)continue;
                    h.push_back(v);
                    col[v] = -2;
                }
            }
        }
    }

    int best_col = -1;
    int id_best = 0;
    for(int i = 0;i <= n;i++){
        // cout << "Color " << i << " Has " << (int)colc[i].size() << " Nodes\n";
        // for(auto v : colc[i]){
        //     cout << v << " ";
        // }cout << "\n";
        if((int)colc[i].size() > best_col){
            best_col = (int)colc[i].size();
            id_best = i;
        }
    }

    ans_q = colc[id_best];

}
signed main(){
    
    read();
    
    //cerr << "Hello Jakarta\n";
    if(ifstream("jakarta.inp")){
        freopen("jakarta.inp","r",stdin);
        //freopen("jakarta.out","w",stdout);
    }

    ans_q.clear();

    cin >> n >> m;
    for(int i = 1,u,v;i <= m;i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[v]++;
        deg[u]++;
    }
    set<ii> st;
    for(int i = 1;i <= n;i++){
        del[i] = 0;
        st.insert({deg[i],i});
    }
    
    solve();
    int xxx = (int)ans_q.size();
    int cur_best = st.begin() -> X;
    int cur_sol = xxx;

    if((cur_sol + 1) * (cur_best + 1) > n){
        //cerr << "Initial Solution Works\n";
        vector<int> ans_p;
        for(int i = 1;i <= n;i++){
            if(!del[i])ans_p.push_back(i);
        }
        cout << cur_best << " " << cur_sol << "\n";
        cout << ans_p.size() << " ";
        for(auto v : ans_p)cout << v << " ";cout << "\n";
        cout << ans_q.size() << " ";
        for(auto v : ans_q)cout << v << " ";cout << "\n";
        return 0;
    }
    while(!st.empty()){
        //cerr << "Current Best : " << cur_best << " " << st.size() << "\n";
        while(st.begin() -> X <= cur_best && !st.empty()){
            ii p = *st.begin();
            st.erase(st.begin());
            //cerr << "Removing Node " << p.Y << " With Degree " << p.X << "\n";
            del[p.Y] = 1;
            for(auto v : adj[p.Y]){
                if(del[v]){
                    g[p.Y].push_back(v);
                    g[v].push_back(p.Y);
                    continue;
                }
                st.erase({deg[v],v});
                deg[v]--;
                st.insert({deg[v],v});
            }

            ///cout << p.X << " " << p.Y << "--\n";
            int cur_f = xxx;
            if((cur_f + 1) * (cur_best + 1) > n){
                
                vector<int> ans_p;
                for(int i = 1;i <= n;i++){
                    if(!del[i]){
                        ans_p.push_back(i);
                        //cerr << ans_p.back() << " ";
                    }
                }
               // for(auto v : ans_p)cerr << v << " ";cerr << "\n";
                cout << cur_best << " " << cur_f << "\n";
                cout << ans_p.size() << " ";
                for(auto v : ans_p)cout << v << " ";
                cout << "\n";
                cout << ans_q.size() << " ";
                for(auto v : ans_q)cout << v << " ";cout << "\n";
                return 0;
            }
        }
        cur_best = st.begin() -> X;
    }
}