#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define fi first
#define se second
#define pb push_back
#define int long long

const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int n, dem, root;
int color[N];
vector<int> vi[N];
map<int, int> cnt[N];
pair<int, int> ans[N];

void dfs(int u){
    sz[u] = 1;
    st[u] = ++dem;
    for(int v: vi[u])   {
        hi[v] = hi[u] + 1;
        dfs(v); sz[u] += sz[v];
    }
    en[u] = dem;
}

void solve(int u, bool spm)  {
    int bign = -1;
    for(int v: vi[u])   {
        solve(v);
        if(bign == -1 || cnt[bign].size() < cnt[v].size())  {
            bign = v;
        }
    }

}

signed main()
{
    //freopen("test.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(j, 1, n)    {
        string s; cin >> s;
        int tmp = 0ll;
        for(int i = 0; i < s.length(); ++i ) tmp = (tmp * 26 + s[i] - 'a') % MOD;
        color[i] = tmp;
        int pr; cin >> pr;
        if(pr)  vi[pr].pb(i);
        else root = i;
    }
    solve(root);
}
