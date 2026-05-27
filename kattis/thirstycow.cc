#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    
    vector<int> a(N);
    for (auto &x : a) {
        cin >> x;
    }
    cout << *max_element(begin(a), end(a)) << endl;
    
    return 0;
}