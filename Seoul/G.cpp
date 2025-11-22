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
const int mod = 998244353, N = 100000;

int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    vector<long long> b(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    for(int i = 0; i < n; ++i) cin >> b[i];

    long long low = 0, high = 1e18 + 1e6;
    long long res = -1;
    while(low <= high) {
        long long mid = (low + high) >> 1;
        //bug(mid);
        long long used = 0;
        bool bad = false;
        for(int i = 0; i < n; ++i) {
            if(a[i] < mid) {
                long long val = (mid - a[i] + b[i] - 1)/b[i];
                if(x - val < used) {
                    bad = true;
                    break;
                }
                used += (mid - a[i] + b[i] - 1)/b[i];
            }
        }

        if(used <= x && !bad) {
            res = mid;
            low = mid + 1;
        }
        else high = mid - 1;
    }

    for(int i = 0; i < n; ++i) {
        if(a[i] < res) {
            long long need = (res - a[i] + b[i] - 1)/b[i];
            x -= need;
            a[i] += need*b[i];
        }
    }

    assert(x >= 0);

    for(int i = 0; i < n && x; ++i) {
        if(a[i] == res) {
            a[i] += b[i];
            --x;
        }
    }

    assert(x == 0);

    for(int i = 0; i < n; ++i) cout << a[i] << " ";
    
}