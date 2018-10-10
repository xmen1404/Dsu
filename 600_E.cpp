#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define fi first
#define se second
#define pb push_back
#define int long long

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int n, dem;
int color[N];
vector<int> vi[N];
map<int, int> cnt[N];
pair<int, int> ans[N];

void solve(int pre, int u)  {
    int bign = -1;
    for(int v: vi[u])   if(v != pre){
        solve(u, v);
        if(bign == -1 || cnt[bign].size() < cnt[v].size())  {
            bign = v;
        }
    }
    if(bign != -1)  {
        cnt[u].swap(cnt[bign]);
        ans[u] = ans[bign];
    }
    int tmp = ++cnt[u][color[u]];
    if(ans[u].fi < tmp) {
        ans[u].se = color[u]; ans[u].fi = tmp;
    }else if(tmp == ans[u].fi) ans[u].se += color[u];

    for(int v: vi[u])   if(v != pre && v != bign)   {
        for(auto it: cnt[v]){
            int tmp = cnt[u][it.fi] += it.se;
            if(tmp > ans[u].fi) {
                ans[u].fi = tmp; ans[u].se = it.fi;
            }else if(ans[u].fi == tmp) ans[u].se += it.fi;
        }
    }
    //cout << u << ' ' << ans[u].fi << ' ' << ans[u].se << '\n';
}

signed main()
{
    //freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n) cin >> color[i];
    FOR(i, 1, n - 1)    {
        int u, v; cin >> u >> v;
        vi[u].pb(v); vi[v].pb(u);
    }
    solve(1, 1);
    FOR(i, 1, n) cout << ans[i].se << ' ';
}
