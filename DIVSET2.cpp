#include<bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back

typedef pair<int, int> ii;

const int N = 1e5;
const int mod = 1e9 + 7;

int n, sum;
int deg[N], ndeg[N], a[N];
bool visit[N], alive[N];
vector<int> vi[N], ans[N];

void solve()    {
    memset(visit, false, sizeof visit);
    for(int i = 1; i <= n; ++i ) ndeg[i] = deg[i];
    set<ii> st;
    for(int i = 1; i <= n; ++i) if(!alive[i]) {
        st.insert(ii(ndeg[i], i));
        visit[i] = true;
    }
    while(!st.empty() && st.begin()->fi < st.size() - 1)    {
        auto it = st.begin();
        ii cur = (*it); st.erase(it);
        visit[cur.se] = false;
        for(int v: vi[cur.se]) if(visit[v]) {
            it = st.find(ii(ndeg[v], v));
            st.erase(it);
            ndeg[v] --;
            st.insert(ii(ndeg[v], v));
        }
    }
    return;
}

signed main()
{
    //freopen("DIVSET2.inp", "r", stdin);
    //freopen("DIVSET2.out", "r", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        cin >> a[i];
        for(int j = 1; j < i; ++j) if(a[i] % a[j] != 0 && a[j] % a[i] != 0) {
            deg[i] ++; deg[j] ++;
            vi[i].pb(j);    vi[j].pb(i);
        }
    }
    int cnt = n;
    while(cnt) {
        solve();
        sum ++;
        for(int i = 1; i <= n; ++i) if(visit[i]) {
            cnt --;
            alive[i] = true;
            ans[sum].pb(i);
            for(int v: vi[i]) if(!alive[v]) deg[v] --;
        }
    }
    cout << sum << '\n';
    for(int i = 1; i <= sum ;++i) {
        for(int v: ans[i]) cout << v << ' '; cout << '\n';
    }
}
