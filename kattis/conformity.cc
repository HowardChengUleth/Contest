#include <bits/stdc++.h>

using namespace std;

int main()
{
    map<vector<int>, int> freq;
    int max_freq = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
	vector<int> v(5);
	for (auto &x : v) {
	    cin >> x;
	}
	sort(begin(v), end(v));
	max_freq = max(max_freq, ++freq[v]);
    }

    int ans = 0;
    for (const auto &[ v, f ] : freq) {
	if (f == max_freq) {
	    ans += f;
	}
    }

    cout << ans << endl;
	
    
    return 0;
}
