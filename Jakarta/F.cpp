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

int n, m;
vector<int> adj[MAX];
int deg[MAX];           
int original_deg[MAX];  
bool deleted[MAX];      
int core_val[MAX];      
vector<int> elim_order; 

int color[MAX];
bool used_color[MAX];

signed main(){
    read();
    
    if(ifstream("jakarta.inp")){
        freopen("jakarta.inp","r",stdin);
        //freopen("jakarta.out","w",stdout);
    }

    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    set<pair<int,int>> st;
    for(int i = 1; i <= n; i++){
        st.insert({deg[i], i});
        original_deg[i] = deg[i];
    }

    int max_core = 0; 
    
    while(!st.empty()){
        pair<int,int> top = *st.begin();
        st.erase(st.begin());
        
        int u = top.second;
        int d = top.first;
        
        deleted[u] = true;
        elim_order.push_back(u);
        max_core = max(max_core, d);
        core_val[u] = max_core; 

        for(int v : adj[u]){
            if(!deleted[v]){
                st.erase({deg[v], v});
                deg[v]--;
                st.insert({deg[v], v});
            }
        }
    }
    vector<int> S1;

    fill(deg + 1, deg + n + 1, 0);
    int k = 0;
    for(int i=1; i<=n; i++) {
        deg[i] = original_deg[i];
        deleted[i] = false;
    }
    vector<int> q_remove;
    for(int i=1; i<=n; i++){
        if(deg[i] < max_core) {
            deleted[i] = true;
            q_remove.push_back(i);
        }
    }
    int head = 0;
    while(head < q_remove.size()){
        int u = q_remove[head++];
        for(int v : adj[u]){
            if(!deleted[v]){
                deg[v]--;
                if(deg[v] < max_core){
                    deleted[v] = true;
                    q_remove.push_back(v);
                }
            }
        }
    }
    for(int i=1; i<=n; i++){
        if(!deleted[i]) S1.push_back(i);
    }
    vector<int> nodes_by_color[MAX];
    int max_color_used = 0;

    for(int i = n - 1; i >= 0; i--){
        int u = elim_order[i];
        vector<int> neighbor_colors;
        for(int v : adj[u]){
            if(color[v] != 0){ 
                used_color[color[v]] = true;
            }
        }
        
        int c = 1;
        while(used_color[c]) c++;
        
        color[u] = c;
        nodes_by_color[c].push_back(u);
        max_color_used = max(max_color_used, c);
        
        for(int v : adj[u]){
            if(color[v] != 0) used_color[color[v]] = false;
        }
    }

    int best_color = 1;
    for(int c = 1; c <= max_color_used; c++){
        if(nodes_by_color[c].size() > nodes_by_color[best_color].size()){
            best_color = c;
        }
    }
    
    vector<int> S2 = nodes_by_color[best_color];

    cout << max_core << " " << S2.size() << "\n";
    
    cout << S1.size();
    for(int x : S1) cout << " " << x;
    cout << "\n";
    
    cout << S2.size();
    for(int x : S2) cout << " " << x;
    cout << "\n";

    return 0;
}