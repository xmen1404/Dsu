#include<bits/stdc++.h>
using namespace std;

#define FOR(a, b, c)    for(int a = b; a <= c; ++a)
#define fi first
#define se second
#define pb push_back
#define ii pair<long long, int>

const int N = 1e5 + 10;
const long long oo = 1e15;

int n, m, chain = 1, cnt, q;
int chainhead[N], chainid[N], st[N], en[N], pr[N], Inpos[N], sz[N];
long long la[N*4];
pair<long long, int> node[4*N];
stack<int> prin[N];
vector<int> vi[N];

void dfs(int pre, int u){
    pr[u] = pre; sz[u] = 1;
    for(int v: vi[u])   if(v != pre)    {
        dfs(u, v); sz[u] += sz[v];
    }
}

void hld(int u) {
    if(chainhead[chain] == 0) chainhead[chain] = u;
    chainid[u] = chain;
    st[u] = ++cnt; Inpos[cnt] = u;

    int bign = -1;
    for(int v: vi[u])   if(v != pr[u]){
        if(bign == -1 || sz[bign] < sz[v]) bign = v;
    }

    if(bign != -1) hld(bign);
    for(int v: vi[u])   if(v != pr[u] && v != bign)    {
        chain ++; hld(v);
    }
    en[u] = cnt;
}
void true_val(int i, int l, int r)  {
    if(!la[i] || node[i].fi >= oo) return;
    node[i].fi += la[i];
    if(l != r)  {
        la[i << 1] += la[i];
        la[i << 1 | 1] += la[i];
    }
    la[i] = 0;
}
void upd(int i, int l, int r, int ql, int qr, int val)  {
    true_val(i, l, r);
    if(l > qr || l > r || ql > r) return;
    if(ql <= l && r <= qr)  {
        if(val == -1)   {
            int tmp = Inpos[l];
            node[i].fi -= 1LL * prin[tmp].top();
            prin[tmp].pop();
            if(prin[tmp].size()) node[i].fi += 1ll * prin[tmp].top();
            else node[i] = ii(oo, tmp);
        } else {
            if(node[i].fi >= oo) return;
            node[i].fi += 1ll * val;
            if(l != r)  {
                la[2*i] += 1ll * val; la[2*i + 1] += 1ll * val;
            }
        }
        return;
    }
    int mid = (l + r) / 2;
    upd(i << 1, l, mid, ql, qr, val); upd(i << 1 | 1, mid + 1, r, ql, qr, val);
    node[i] = min(node[i<<1], node[i<<1|1]);
}

ii getm(int i, int l, int r, int ql, int qr)    {
    true_val(i, l, r);
    if(l > qr || ql > r || l > r || node[i].fi >= oo) return ii(oo, 0);
    if(ql <= l && r <= qr)  return node[i];
    int mid = (l + r) / 2;
    return min(getm(i<<1, l, mid, ql, qr), getm(i<<1|1, mid + 1, r, ql, qr));
}

void build(int i, int l, int r) {
    if(l > r) return;
    if(l == r)  {
        int u = Inpos[l];
        if(prin[u].size() == 0) node[i] = ii(oo, u);
        else {
            node[i] = ii(prin[u].top() * 1ll, u);
        }
        return;
    }
    int mid = (l + r) / 2;
    build(i<<1, l, mid); build(i<<1|1, mid + 1, r);
    node[i] = min(node[i<<1], node[i<<1|1]);
}

int solve(int u, int v) {
    ii res = ii(oo, 0);
    while(chainid[u] != chainid[v]) {
        //cout << u << ' ' << v << ' ' << chainid[u] << ' ' << chainid[v] << '\n';
        if(chainid[u] < chainid[v]) swap(u, v);
        int head = chainhead[ chainid[u] ];
        res = min(res, getm(1, 1, n, st[head], st[u]));
        u = pr[head];
    }
    // u, v in the same chian;
    if(st[u] > st[v]) swap(u, v);
    res = min(res, getm(1, 1, n, st[u], st[v]));
    if(res.fi == oo) return -1;
    else return res.se;
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    scanf("%d%d%d", &n, &m, &q);
    FOR(i, 1, n - 1)    {
        int u, v; scanf("%d%d", &u, &v);
        vi[u].pb(v); vi[v].pb(u);
    }
    dfs(1, 1);
    hld(1);

    vector<int> nextmp;
    FOR(i, 1, m)    {
        int x; scanf("%d", &x);
        nextmp.pb(x);
    }
    for(int i = nextmp.size() - 1; i >= 0; --i)
        prin[nextmp[i]].push(i + 1);

    build(1, 1, n);

    //cout << solve(1, 2) << '\n';
    //return 0;

    while(q --) {
        int t; scanf("%d", &t);
        if(t == 2)  {
            int u, k; scanf("%d%d", &u, &k);
            upd(1, 1, n, st[u], en[u], k);
        } else {
            int u, v, k; scanf("%d%d%d", &u, &v, &k);
            vector<int> tmp;
            for(int i = 1; i <= k; ++i) {
                int nex = solve(u, v);
                if(nex == -1) break;
                else {
                    tmp.pb(prin[nex].top());
                    upd(1, 1, n, st[nex], st[nex], -1);
                }
            }
            printf("%d ", tmp.size());
            for(int v: tmp) printf("%d ", v);
            printf("\n");
        }
    }
}
