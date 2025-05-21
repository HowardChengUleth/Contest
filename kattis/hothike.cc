#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> temp(n);
    for (auto &t : temp) {
	cin >> t;
    }

    int best_day, best = INT_MAX;
    for (int i = 0; i + 2 < n; i++) {
	int t = max(temp[i], temp[i+2]);
	if (t < best) {
	    best_day = i+1;
	    best = t;
	}
    }
    cout << best_day << ' ' << best << endl;
    
    return 0;
}
