#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;
typedef bitset<11> BS11;

pii p[11];
int N;

int dist(int i, int j)
{
    auto [xi, yi] = p[i];
    auto [xj, yj] = p[j];
    return abs(xi-xj) + abs(yi-yj);    
}

int memo[11][2048];

// start at v, visit all vertices in remset, and return to 0
int f(int v, BS11 &remset)
{
    if (remset.none()) {
        return dist(0, v);
    }

    int &ans = memo[v][remset.to_ulong()];
    if (ans >= 0) {
        return ans;
    }
    
    
    ans = INT_MAX;
    for (int w = 1; w <= N; w++) {
        if (remset.test(w)) {
            remset.flip(w);
            ans = min(ans, dist(v, w) + f(w, remset));
            remset.flip(w);
        }
    }
    return ans;
}

void solve()
{
    int X, Y;
    cin >> X >> Y;
    
    cin >> p[0].first >> p[0].second;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> p[i].first >> p[i].second;
    }
    
    for (int v = 1; v <= N; v++) {
        for (int s = 0; s < (1 << (N+1)); s++) {
            memo[v][s] = -1;
        }
    }
    int ans = INT_MAX;
    
    for (int v = 1; v <= N; v++) {
        BS11 remset;
        for (int i = 1; i <= N; i++) {
	  if (i != v) {
	    remset.set(i);
	  }
	}
        ans = min(ans, f(v, remset) + dist(0, v));
    }
    cout << ans << endl;
}

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        solve();
    }
    return 0;
}
