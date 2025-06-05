#include <bits/stdc++.h>

using namespace std;

const int MAX_D = 2016;
const int INF = 1'000'000'000 + 2;

int S;
vector<int> D, C, F, U;
vector<int> weight, cost;

// memo[d][k] = best cost to win d delegates using first k items
int memo[MAX_D+1][MAX_D+1];

int f(int d, int k)
{
    int &ans = memo[d][k];
    if (ans != -1) {
	return ans;
    }

    if (k == 0) {
	return ans = (d == 0) ? 0 : INF;
    }

    // don't use item k-1
    ans = f(d, k-1);

    // use item k-1 if possible
    if (d >= weight[k-1]) {
	ans = min(ans, min(INF, f(d-weight[k-1], k-1) + cost[k-1]));
    }

    return ans;
}

void knapsack(int need)
{
    for (int d = 0; d <= MAX_D; d++) {
	for (int k = 0; k <= weight.size(); k++) {
	    memo[d][k] = -1;
	}
    }

    int best = INF;
    for (int d = need; d <= MAX_D; d++) {
	best = min(best, f(d, weight.size()));
    }

    if (best == INF) {
	cout << "impossible" << endl;
    } else {
	cout << best << endl;
    }
}

int main()
{
    cin >> S;
    D.resize(S);
    C.resize(S);
    F.resize(S);
    U.resize(S);
    weight.reserve(S);
    cost.reserve(S);

    for (int i = 0; i < S; i++) {
	cin >> D[i] >> C[i] >> F[i] >> U[i];
    }

    int totalD = accumulate(begin(D), end(D), 0);
    int voteC = 0;     // number of sure votes for C
    for (int i = 0; i < S; i++) {
	int total_voters = C[i] + F[i] + U[i];
	int threshold = total_voters/2 + 1;
	
	if (C[i] >= threshold) {
	    // C wins for sure
	    voteC += D[i];
	} else {
	    int needC = threshold - C[i];
	    if (U[i] >= needC) {
		// can be infuenced
		
		//
		// add knapsack item with weight = D and cost = U
		weight.push_back(D[i]);
		cost.push_back(needC);
	    }
	}
    }

    // number of delegates needed
    int need = max(0, totalD/2 + 1 - voteC);
    knapsack(need);
    
    return 0;
}
    
