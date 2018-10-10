#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define FOR(a, b, c) for(int a = b; a <= c; ++a)

const int mod = 1e9 + 7;
const int N = 2e5 + 10;
const int oo = 1e9;

typedef pair<int, int> ii;

int n, ans, euler, ok = 0;
int color[N], pos[N], maxn[N], sz[N], st[N], en[N];
vector<int> vi[N];
map<ii, int> eg;
map<int, int> cnt;

void dfs(int pre, int u)    {
    sz[u] = 1;  st[u] = ++euler;
    pos[euler] = u;
    for(int v: vi[u]) if(v != pre){
        dfs(u, v); sz[u] += sz[v];
    }
    en[u] = euler;
}

void solve(int pre, int u, bool spm)  {
    int bign = -1;
    for(int v: vi[u])   if(v != pre) {
        if(bign == -1 || sz[bign] < sz[v])
            bign = v;
    }
    for(int v: vi[u]) if(v != bign && v != pre) solve(u, v, 0);
    if(bign != -1) solve(u, bign, 1);
    cnt[ color[u] ] ++;
    if(cnt[ color[u] ] == maxn[ color[u] ]) ok ++;
    for(int v: vi[u]) if(v != pre && v != bign){
        for(int i = st[v]; i <= en[v]; ++i) {
            cnt[ color[ pos[i] ] ] ++;
            if(cnt[ color[ pos[i] ] ] == maxn[ color[ pos[i] ] ]) ok++;
        }
    }
    if(ok == cnt.size() && u != 1) ans ++;
    if(!spm)    {
        for(int i = st[u]; i <= en[u]; ++i) {
            if(cnt[ color[ pos[i] ] ] == maxn[ color[ pos[i] ] ]) ok--;
            cnt[ color[ pos[i] ] ] --;
            if(cnt[ color[ pos[i] ] ] == 0) cnt.erase( color[ pos[i] ] );
        }
    }

}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n - 2)    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        color[i] = d;
        maxn[d] ++;
        ii a1 = {min(a, b), max(a, b)};
        ii a2 = {min(a, c), max(a, c)};
        ii a3 = {min(b, c), max(b, c)};

        if(eg.count(a1)) {
            int v = eg[a1];
            vi[v].pb(i); vi[i].pb(v);
        } else eg[a1] = i;
        if(eg.count(a2)) {
            int v = eg[a2];
            vi[v].pb(i); vi[i].pb(v);
        } else eg[a2] = i;
        if(eg.count(a3)) {
            int v = eg[a3];
            vi[v].pb(i); vi[i].pb(v);
        } else eg[a3] = i;
    }

    dfs(1, 1);
    //return 0;
    solve(1, 1, 1);
    cout << ans;
}
