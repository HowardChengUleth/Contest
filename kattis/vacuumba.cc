#include <bits/stdc++.h>

using namespace std;

void solve()
{
    const double PI = acos(-1.0);
    
    double x = 0, y = 0, dir = 90;
    
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
	double rot, dist;
	cin >> rot >> dist;

	dir += rot;
	x += dist * cos(dir * PI / 180.0);
	y += dist * sin(dir * PI / 180.0);
    }

    cout << setprecision(10) << fixed << x << ' ' << y << endl;
}


int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
	solve();
    }

    return 0;
}
