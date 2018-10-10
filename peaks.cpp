#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define pb push_back
#define pii pair< int, pair<int, int> >
#define ii pair<int, int>

const int mod = 1e9 + 7;
const int oo = 1e9;
const int N = 2005;

int n, m, cnt;
int dx[] = {-1, -1, 1, 1, 0, 0, 1, -1}, dy[] = {1, -1, 1, -1, 1, -1, 0, 0};
ii pr[N][N], pos[N];
int ans[N * N], a[N][N];
vector<pii> tmp;
set<ii> peak[N][N];
bool visit[N][N];

ii findn(int i, int j) {
    return (pr[i][j] == ii(i, j)) ? ii(i, j) : (pr[i][j] = findn(pr[i][j].fi, pr[i][j].se)); // done
}
bool check(int x, int y) { return (x >= 1 && x <= n && y >= 1 && y <= m); }
void uni(int val, int x, int y) {
    for(int t = 0; t <= 7; ++t)  {
        int nx = x + dx[t], ny = y + dy[t];
        if(check(nx, ny) && val <= a[nx][ny])   {
            //if(val == 15) cout << nx << ' ' << ny << ' ' << a[nx][ny] << '\n';

            ii pu = findn(x, y);
            ii pv = findn(nx, ny);
            if(pu != pv)    {
                if(peak[pu.fi][pu.se].size() > peak[pv.fi][pv.se].size()) swap(pu, pv);

                pr[pu.fi][pu.se] = pv;
                for(auto it = peak[pu.fi][pu.se].begin(); it != peak[pu.fi][pu.se].end(); ++it)
                    peak[pv.fi][pv.se].insert((*it));
                peak[pu.fi][pu.se].clear();
                //done tranfor
                set<ii> &cur = peak[pv.fi][pv.se];
                while(cur.size() > 1)   {
                    auto st = cur.begin();
                    auto en = cur.end(); en --;
                    if(st->fi == en->fi) break;
                    //if(st->fi == 15) cout << en->fi << ' ' << val << '\n';
                    ans[st->se] = val;
                    cur.erase(st);
                }
            }
        }
    }
}

void bfs(int i, int j)  {
    int maxn = a[i][j]; visit[i][j] = true;
    //if(a[i][j] == 13) cout << "check " << i << ' ' << j << ' ' << a[i][j] << '\n';
    queue<ii> pq;
    pq.push(ii(i, j));
    while(!pq.empty())  {
        int x = pq.front().fi, y = pq.front().se;
        //if(a[i][j] == 13) cout << "eg " << x << ' ' << y << '\n';
        pq.pop();
        for(int i1 = 0; i1 < 8; ++i1) {
            int nx = x + dx[i1], ny = y + dy[i1];
            if(check(nx, ny) && a[nx][ny] == a[i][j] && !visit[nx][ny])   {
                visit[nx][ny] = true;
                pr[nx][ny] = ii(i, j);
                pq.push(ii(nx, ny));
            }
            if(check(nx, ny)) maxn = max(maxn, a[nx][ny]);
        }
    }
    //if(a[i][j] == 13) cout << i << ' ' << j << ' ' << maxn << '\n';
    if(maxn == a[i][j]) {
        //cout << "check " << i << ' ' << j << ' ' << a[i][j] << '\n';
        pos[++cnt] = ii(i, j);
        peak[i][j].insert(ii(maxn, cnt));
    }
}

signed main()
{
    //freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    FOR(i, 1, n) FOR(j, 1, m)   {
        cin >> a[i][j];
        tmp.pb({ a[i][j], {i, j} });
        pr[i][j] = ii(i, j);
    }

    FOR(i, 1, n) FOR(j, 1, m) if(!visit[i][j])  {
        //cout << i << ' ' << j << '\n';
        bfs(i, j);
    }

    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    for(auto v: tmp)   uni(v.fi, v.se.fi, v.se.se);
    cout << cnt << '\n';
    vector<ii> fina;
    FOR(i, 1, cnt) fina.pb(ii(a[ pos[i].fi ][ pos[i].se ], ans[i]));
    sort(fina.begin(), fina.end());
    for(int i = fina.size() - 1; i >= 0; --i) cout << fina[i].fi << ' ' << fina[i].se << '\n';
}
