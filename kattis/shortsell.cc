#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> price(N);
    for (auto &x : price) {
	cin >> x;
	x *= 100;
    }

    int best_profit = 0;
    int best_sold = 0;       // highest amount we can sell for up to this point
    for (int i = 0; i < N; i++) {
	// one more day
	best_sold -= K;
	
	// try buying it back
	best_profit = max(best_profit, best_sold - price[i]);

	// update best_sold
	best_sold = max(best_sold, price[i]-K);
    }

    cout << best_profit << endl;
    
    return 0;
}
