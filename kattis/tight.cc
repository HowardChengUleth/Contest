#include <bits/stdc++.h>

using namespace std;

// memo[n][k] = percentage of tight words of length n, ending with k
double memo[101][10];

int max_digit;

double f(int n, int k)
{
    if (memo[n][k] >= 0.0) {
	return memo[n][k];
    }

    if (n == 1) {
	// all length 1 words are tight
	return memo[n][k] = 100.0/(max_digit+1);
    }

    memo[n][k] = 0.0;
    for (int i = max(0, k-1); i <= min(max_digit, k+1); i++) {
	memo[n][k] += f(n-1, i)/(max_digit+1);
    }

    return memo[n][k];
}

bool solve()
{
    int k, n;
    if (!(cin >> k >> n)) {
	return false;
    }
    max_digit = k;

    for (int i = 0; i <= n; i++) {
	for (int j = 0; j <= k; j++) {
	    memo[i][j] = -1;
	}
    }

    double ans = 0.0;
    for (int j = 0; j <= k; j++) {
	ans += f(n, j);
    }

    cout << fixed << setprecision(10) << ans << endl;

    return true;
}

int main(void)
{
    while (solve())
	;

    return 0;
}
