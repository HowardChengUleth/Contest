#include <bits/stdc++.h>

using namespace std;

double sqdist(double x1, double y1, double x2, double y2)
{
    double dx = x1-x2, dy = y1-y2;
    return dx*dx + dy*dy;
}

bool solve()
{
    double d;
    int N;

    cin >> d >> N;
    if (d == 0.0 && N == 0) {
	return false;
    }

    double x[1000], y[1000];
    for (int i = 0; i < N; i++) {
	cin >> x[i] >> y[i];
    }


    int sour = 0;
    for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	    if (i == j) continue;
	    if (sqdist(x[i], y[i], x[j], y[j]) <= d*d) {
		sour++;
		break;
	    }
	}
    }

    cout << sour << " sour, " << N-sour << " sweet" << endl;

    return true;
}

int main()
{
    while (solve())
	;
    return 0;
}
