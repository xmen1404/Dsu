#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back

const int N = 1e5 + 10;
const int M = 30 * N;
const int oo = 1e9;

struct trie{
    int cnt, real;
    vector<int> st, en, child, tie, pos, inpos;
    vector< map<int, int> > nex;
    void add()  {
        this->st.pb(0); this->en.pb(0); this->tie.pb(0); this->pos.pb(0); this->inpos.pb(0);
        this->child.pb(0);
        map<int, int> tmp; this->nex.pb(tmp);
    }
}t[2];

struct query{
    string s1, s2;
    int u1, u2, ans;
} qu[N];

int n, m, q;
int bit[N];
vector<int> event[M];
string s[N];

void upd(int pos, int val)  {
    for(int i = pos; i < N; i += (i & -i))
        bit[i] += val;
}
int get(int pos)    {
    int res = 0; for(int i = pos; i >= 1; i -= (i & -i)) res += bit[i];
    return res;
}
void dfs(int base, int pre, int u)  {
    t[base].st[u] = t[base].real + 1;
    t[base].child[u] = 1;
    if(t[base].tie[u] > 0)  {
        int v = t[base].tie[u];
        //if(base == 0) cout << v << " u=" << u << ' ' << t[base].real << '\n';
        t[base].pos[v] = ++t[base].real;
        t[base].inpos[ t[base].real ] = v;
    }

    FOR(i, 0, 25)   if(t[base].nex[u].count(i)) {
        int v = t[base].nex[u][i];
        dfs(base, u, v);
        t[base].child[u] += t[base].child[v];
    }
    t[base].en[u] = t[base].real;
}
void decomp(int base)   {
    t[base].cnt = t[base].real = 0;
    t[base].add();
    FOR(i, 1, n)    {
        int cur = 0;
        for(char x: s[i]) {
            //cout << x << ' ';
            if(t[base].nex[cur].count(x - 'a') == true) cur = t[base].nex[cur][x - 'a'];
            else {
                t[base].cnt ++; t[base].add();
                t[base].nex[cur][x - 'a'] = t[base].cnt;
                cur = t[base].cnt;
            }
        }
        t[base].tie[cur] = i;
    }
    dfs(base, 0, 0);
}

void solve(int pre, int u, bool spm)    {
    int bign = -1;
    FOR(i, 0, 25) if(t[0].nex[u].count(i)) {
        int v = t[0].nex[u][i];
        if(bign == -1 || t[0].child[bign] < t[0].child[v]) bign = v;
    }
    FOR(i, 0, 25) if(t[0].nex[u].count(i)) {
        int v = t[0].nex[u][i];
        if(v != bign) solve(u, v, 0);
    }
    if(bign != -1) solve(u, bign, 1);
    if(t[0].tie[u]) {
        int v = t[0].tie[u];
        upd(t[1].pos[v], 1);
    }
    FOR(i, 0, 25) if(t[0].nex[u].count(i)) {
        int v = t[0].nex[u][i];
        if(v != bign) {
            FOR(ptr, t[0].st[v], t[0].en[v])    {
                int nex = t[0].inpos[ptr];
                upd(t[1].pos[nex], 1);
            }
        }
    }
    for(auto v: event[u])   {
        int u2 = qu[v].u2;
        if(t[1].en[u2] >= t[1].st[u2]) qu[v].ans = get(t[1].en[u2]) - get(t[1].st[u2] - 1);
    }
    if(!spm)    {
        FOR(i, t[0].st[u], t[0].en[u]) {
            int nex = t[0].inpos[i];
            upd(t[1].pos[nex], -1);
        }
    }
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    FOR(i, 1, n) cin >> s[i];
    decomp(0);
    FOR(i, 1, n) reverse(s[i].begin(), s[i].end());
    decomp(1);
    FOR(i, 1, q)    {
        cin >> qu[i].s1 >> qu[i].s2;
        reverse(qu[i].s2.begin(), qu[i].s2.end());
        int t1 = 0;
        for(char x: qu[i].s1)   {
            if(t[0].nex[t1].count(x - 'a') == false) {
                t1 = -1; break;
            }
            t1 = t[0].nex[t1][ x - 'a' ];
        }
        int t2 = 0;
        for(char x: qu[i].s2)   {
            if(t[1].nex[t2].count(x - 'a') == false){
                t2 = -1; break;
            }
            t2 = t[1].nex[t2][x - 'a' ];
        }

        if(t1 != -1 && t2 != -1)    {
            event[t1].pb(i);
            qu[i].u1 = t1, qu[i].u2 = t2;
        }
        qu[i].ans = 0;
    }
    solve(0, 0, 1);
    FOR(i, 1, q) cout << qu[i].ans << '\n';
}
