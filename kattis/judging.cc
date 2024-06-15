#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    map<string, int> freq[2];
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            freq[k][s]++;
        }
    }
    
    int ans = 0;
    for (auto [s, c] : freq[0]) {
        ans += min(c, freq[1][s]);
    }
    
    cout << ans << endl;
    
    
    return 0;
}