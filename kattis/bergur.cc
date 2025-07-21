#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<int> a(N);
    for (auto &val : a) {
	cin >> val;
    }

    int total = 0;
    int min_rest = INT_MAX;
    
    for (int i = N-1; i >= 0; i--) {
	min_rest = min(a[i], min_rest);
	total += min_rest;
    }

    cout << total << endl;

    return 0;
}
