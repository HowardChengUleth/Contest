#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int a, b, c;
    cin >> a >> b >> c;

    if (a+b == c ||
	a-b == c || b-a == c ||
	a*b == c ||
	a == c*b || b == c*a) {
	cout << "Possible" << endl;
    } else {
	cout << "Impossible" << endl;
    }
}

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
	solve();
    }
    return 0;
}
