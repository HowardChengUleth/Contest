#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    
    vector<int> A(n+1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        A[i] = 1 - (x % 2);
    }
    
    partial_sum(begin(A), end(A), begin(A));
    
    int ans = 0;
    for (int i = m; i <= n; i++) {
        if (A[i] - A[i-m] >= 2) {
            ans++;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}