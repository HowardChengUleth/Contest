#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<int> pos(n);
    for (auto &x : pos) {
	cin >> x;
    }

    int a = *min_element(begin(pos), end(pos));
    int b = *max_element(begin(pos), end(pos));

    cout << 2*(b-a) << endl;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
	solve();
    }
    
    return 0;
}
