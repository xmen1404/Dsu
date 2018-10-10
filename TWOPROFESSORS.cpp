#include<bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define FOR(a, b, c) for(int a = b; a <= c;++a)

const int N = 1e5 + 10;

int n, sum;
int cnt[N];
pair<int, int> t[N];
vector< pair<int, int> > tmp;

signed main()
{
    freopen("test.inp", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n;
    FOR(i, 1, n) {
        cin >> t[i].fi >> t[i].se;
        tmp.pb({t[i].fi, 0});
        tmp.pb( {t[i].fi, 1} );
    }
    sort(tmp.begin(), tmp.end());
    int maxn = 2;
    for(auto v: tmp)    {
        if(v.se == 0) sum ++;
        else sum --;
        maxn = max(maxn, sum);
    }

    if(maxn > 2) cout << maxn;
    else {
        int pos = 0;
        if(t[1].fi > t[2].fi) swap(t[1], t[2]);
        for(int i = 0 ; i< tmp.size(); ++i) if(tmp[i].fi == t[1].fi)   {
            pos = i; break;
        }
        // now we need to finddown the las posi which haven
        int cnt = 0;
        pos ++;
        while(pos < tmp.size() && tmp[pos].fi != t[2].fi){
            //cout << pos << ' ' << tmp[pos].fi << ' ' << t[2].fi << '\n';
            cnt ++;
            pos ++;
        }
        if(cnt % 2 == 1) cout << "3";
        else cout << "2";
    }
}
