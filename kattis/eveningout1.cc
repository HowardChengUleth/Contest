#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
    ll A, B;
    cin >> A >> B;
    
    ll R = A % B;
    
    cout << min(R, B-R) << endl;
    
    return 0;
}