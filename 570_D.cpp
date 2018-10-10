#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define fi first
#define pb push_back
#define int long long

const int N = 5e5 + 10;
const int MOD = 1e9 + 7;

struct book{
    int u, h;
    bool ans;
}qu[N];

int n, q, dem;
int cnt[N][26], st[N], en[N], sz[N], color[N], hi[N], posin[N];
vector<int> vi[N];
vector<int> event[N];

void dfs(int pre, int u)    {
    st[u] = ++dem; posin[dem] = u;
    sz[u] = 1;
    for(int v: vi[u])   if(v != pre)  {
        hi[v] = hi[u] + 1;
        dfs(u, v); sz[u] += sz[v];
    }
    en[u] = dem;
}

void solve(int pre, int u, bool spm)  {
    int bign = -1;
    for(int v: vi[u])   if(v != pre){
        if(bign == -1 || sz[v] > sz[bign]) bign = v;
    }
    for(int v: vi[u])   if(v != pre && v != bign)   {
        solve(u, v, 0);
    }
    if(bign != -1)  solve(u, bign, 1);
    for(int v: vi[u]) if(v != pre && v != bign) {
        for(int i = st[v]; i <= en[v]; ++i)
            cnt[ hi[ posin[i]  ] ][ color[i] ] ++;
    }
    cnt[ hi[u] ][ color[st[u]] ] ++;
    for(int even : event[u])    {
        int ehi = qu[even].h;
        int idem = 0;
        for(int i = 0; i < 26; ++i) {
            if(cnt[ehi][i] % 2 == 1) idem ++;
        }
        if(idem <= 1)   qu[even].ans = true;
    }

    if(!spm)    {
        for(int i = st[u]; i <= en[u]; ++i)
            cnt[ hi[ posin[i] ] ][ color[i] ] --;
    }
}

signed main()
{
    //freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    FOR(i, 1, n - 1)    {
        int u; cin >> u;
        vi[i + 1].pb(u); vi[u].pb(i + 1);
    }
    hi[1] = 1;
    dfs(1, 1);
    FOR(i, 1, n) {
        char x; cin >> x;
        color[st[i]] = x - 'a';
    }

    FOR(i, 1, q) {
        cin >> qu[i].u >> qu[i].h;
        if(qu[i].h >= hi[ qu[i].u ]) event[qu[i].u].pb(i);
        else qu[i].ans = true;
    }

    solve(1, 1, 1);

    FOR(i, 1, q) {
        if(qu[i].ans == false) cout << "No\n";
        else cout << "Yes\n";
    }

    return 0;
}
