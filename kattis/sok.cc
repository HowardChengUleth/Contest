#include <bits/stdc++.h>

using namespace std;

int main()
{
    double bought[3], need[3];

    for (int i = 0; i < 3; i++) {
	cin >> bought[i];
    }

    for (int i = 0; i < 3; i++) {
	cin >> need[i];
    }

    double left[3];
    double best_portions = DBL_MAX;
    for (int i = 0; i < 3; i++) {
	double portions = bought[i] / need[i];
	best_portions = min(best_portions, portions);
    }

    for (int j = 0; j < 3; j++) {
	left[j] = bought[j] - best_portions * need[j];
	cout << fixed << setprecision(10) << left[j] << ' ';
    }

    return 0;
}
