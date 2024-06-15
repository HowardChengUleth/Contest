#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    
    bool used[201] = { false };
    int last = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        used[x] = true;
        last = x;
    }
    
    bool bad = false;
    for (int i = 1; i <= last; i++) {
        if (!used[i]) {
            cout << i << endl;
            bad = true;
        }
    }
    
    if (!bad) {
        cout << "good job" << endl;
    }
    return 0;
}