// 23 - 12 - 23 

#include<bits/stdc++.h>

using namespace std;

#define read() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define day() time_t now = time(0);char* x = ctime(&now);cerr<<"Right Now Is : "<<x<<"\n"

#define ii pair<int,int>
#define X first
#define Y second 

const long long MAX = (int)300 + 5;
const long long INF = (int)1e9;
const long long MOD = (int)1e9 + 7;

int n,s;
int a[MAX][MAX][4];

// 0 - up
// 1 - right
// 2 - down
// 3 - left
vector<int> adj[MAX];
int cost[MAX][MAX];

signed main(){
    
    read();
    cin >> n >> s;

    for(int i = 1,u,v;i <= n * n - 1;i++){
        cin >> u >> v;
        if(u < v)swap(u,v);

        int u_x = (u / n) + 1 - (u % n == 0);
        int u_y = (u % n) == 0 ? n : (u % n);
        int v_x = (v / n) + 1 - (v % n == 0);
        int v_y = (v % n) == 0 ? n : (v % n);
        
		//cout << u_x << " " << u_y << " " << v_x << " " << v_y << "\n";
        if(u - v == 1){
            a[u_x - 1][u_y - 1][2] = 1;
            a[u_x][u_y - 1][0] = 1;
        }else{
            a[u_x - 1][u_y - 1][1] = 1;
            a[u_x - 1][u_y][3] = 1;
        }
    }

    set<pair<int,ii>> st;
    for(int i = 1;i < n;i++){
        for(int j = 1;j < n;j++){
            int cnt = 0;
            for(int k = 0;k < 4;k++){
                if(a[i][j][k] == 1)cnt++;
            }
            
            //cerr << "--Prepare : " << i << " " << j << " " << cnt << '\n';
            st.insert({cnt,{i,j}});
        }
    }

    vector<ii> ans;
    while(!st.empty()){
        pair<int,ii> cur = *st.rbegin();
        st.erase(cur);
        int x = cur.Y.X;
        int y = cur.Y.Y;
        int cost_here = 1;
        int id = 0;
        for(int k = 0;k < 4;k++){
            if(a[x][y][k] == -1)cost_here += cost[x + (k == 2) - (k == 0)][y + (k == 1) - (k == 3)];
            else if(a[x][y][k] == 0)id = k;
        }
        cost[x][y] = cost_here;
        int u = -1,v = -1;
        if(id == 0){
            u = (x - 1) * n + (y + 1);
            v = (x - 1) * n + (y);
            a[x][y][0] = -1;
            a[x - 1][y][2] = -1;
            int cur = 0;
            for(int k = 0;k < 4;k++){
                if(a[x - 1][y][k] != 0){
                    cur++;
                }
            }
            if(x - 1 >= 1){
                st.erase({cur - 1,{x - 1,y}});
                st.insert({cur,{x - 1,y}});
            }
        }else if(id == 1){
            u = (x) * n + (y + 1);
            v = (x - 1) * n + (y + 1);
            a[x][y][1] = -1;
            a[x][y + 1][3] = -1;
            int cur = 0;
            for(int k = 0;k < 4;k++){
                if(a[x][y + 1][k] != 0){
                    cur++;
                }
            }
            if(y + 1 <= n - 1){
                st.erase({cur - 1,{x,y + 1}});
                st.insert({cur,{x,y + 1}});
            }
        }else if(id == 2){
            u = (x) * n + (y + 1);
            v = (x) * n + y;
            a[x][y][2] = -1;
            a[x + 1][y][0] = -1;
            int cur = 0;
            for(int k = 0;k < 4;k++){
                if(a[x + 1][y][k] != 0){
                    cur++;
                }
            }
            if(x + 1 <= n - 1){
                st.erase({cur - 1,{x + 1,y}});
                st.insert({cur,{x + 1,y}});
            }
        }else{
            u = (x) * n + y;
            v = (x - 1) * n + y;
            a[x][y][3] = -1;
            a[x][y - 1][1] = -1;
            int cur = 0;
            for(int k = 0;k < 4;k++){
                if(a[x][y - 1][k] != 0){
                    cur++;
                }
            }
            if(y - 1 >= 1){
                st.erase({cur - 1,{x,y - 1}});
                st.insert({cur,{x,y - 1}});
            }
        }
        if(u < v)swap(u,v);
        if(cost_here == s){
            ans.push_back({v,u});
        }
        //cout << cost_here << " " << u << " " << v << " " << cur.X << "\n";
    }
	if(ans.size() == 0)return cout << "0\n0 0\n",0;
    cout << ans.size() << "\n";
    sort(ans.begin(),ans.end());
    for(auto it : ans){
        cout << it.X << " " << it.Y << "\n";
        break;
    }
}