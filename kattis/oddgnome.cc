#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int g;
    cin >> g;

    vector<int> id(g);
    for (int i = 0; i < g; i++) {
	cin >> id[i];
    }

    for (int i = 1; i < g-1; i++) {
	if (id[i-1]+1 != id[i]) {
	    cout << i+1 << endl;
	    return;
	}
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
	solve();
    }

    return 0;
}
