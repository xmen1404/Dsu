#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
const int N = 3e5 + 10;
const int M = 2,500,005;
const int oo = 1e9;
typedef pair<int, int> ii;

struct query{
    int u1, u2;
}t[N];

struct tree{
    int st, en;
    vector<int> man;
    int nex[30];
}trie[2][M];
int n, q, cnt;
int bit[N], pos[2][N], ans[N], inpos[2][N];
vector<int> event[M];

void upd(int pos, int val)  {
    for(int i = pos; i < N; i += (i & -i))
        bit[i] += val;
}
int get(int pos)    {
    int res = 0;
    for(int i = pos; i >= 1; i -= (i & -i)) res += bit[i];
    return res;
}
void dfs(int base, int pre, int u)  {
    trie[base][u].st = cnt + 1;

    for(int v: trie[base][u].man)
        pos[base][v] = ++cnt, inpos[base][cnt] = v;

    FOR(i, 0, 25)   if(trie[base][u].nex[i] != -1)  {
        dfs(base, u, trie[base][u].nex[i]);
    }
    trie[base][u].en = cnt;
}
void prepare() {
    FOR(i, 0, M - 1)
        memset(trie[0][i].nex, -1, sizeof trie[0][i].nex), memset(trie[1][i].nex, -1, sizeof trie[1][i].nex);
    FOR(i, 1, n)    {
        int cur = 0;
        for(int j = 0; j < s[i].length(); ++j) {
            if(trie[0][cur].nex[s[i][j] - 'a'] != -1) cur = trie[0][cur].nex[s[i][j] - 'a'];
            else {
                trie[0][cur].nex[s[i][j] - 'a'] = ++cnt;
                cur = cnt;
             }
        }
        trie[0][cur].man.pb(i);
    }
    cnt = 0; dfs(0, 0, 0);
    cnt = 0;
    FOR(i, 1, n) reverse(s[i].begin(), s[i].end());
    FOR(i, 1, n)    {
        int cur = 0;
        for(int j = 0; j < s[i].length(); ++j) {
            if(trie[1][cur].nex[s[i][j] - 'a'] != -1) cur = trie[1][cur].nex[s[i][j] - 'a'];
            else {
                trie[1][cur].nex[s[i][j] - 'a'] = ++cnt;
                cur = cnt;
             }
        }
        trie[1][cur].man.pb(i);
    }
    cnt = 0; dfs(1, 0, 0);
}

void solve(int pre, int u, bool spm)    {

}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> q;
    FOR(i, 1, n) cin >> s[i];
    prepare();
    FOR(i, 1, q)    {
        string s1, s2; cin >> s1 >> s2;
        int t1 = 0;
        for(int j = 0; j < s1.length(); ++j) {
            if(trie[0][t1].nex[s1[j] - 'a'] == -1) {
                t1 = -1; break;
            }
            t1 = trie[0][t1].nex[s1[j] - 'a'];
        }
        int t2 = 0;
        for(int j = 0; j < s2.length(); ++j) {
            if(trie[1][t1].nex[s2[j] - 'a'] == -1) {
                t2 = -1; break;
            }
            t2 = trie[0][t1].nex[s1[j] - 'a'];
        }
        if(t1 != t2) {
            event[t1].pb(i);
            t[i].u1 = t1; t[i].u2 = t2;
        }
    }
    solve(0, 0, 0);
    FOR(i, 1, q) cout << ans[i] << '\n';
}
