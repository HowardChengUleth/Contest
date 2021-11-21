#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> tiii;

int main()
{
  int N, T, K;
  cin >> N >> T >> K;

  int type[100000] = {0};
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    type[x-1]++;
  }

  // for each type, if we use that type to make the combo, then we have
  // to pay to buy the type and lose out on not selling it.  So the cost
  // is the sum of those two values
  tiii cost[100000];
  for (int i = 0; i < T; i++) {
    int a, b;
    cin >> a >> b;

    int buy = a * (2 - type[i]);
    int sell = b * type[i];
    cost[i] = tiii(buy+sell, buy, sell);
  }
  sort(cost, cost+T);

  ll profit = 0;
  for (int i = 0; i < K; i++) {
    profit -= get<1>(cost[i]);
  }
  for (int i = K; i < T; i++) {
    profit += get<2>(cost[i]);
  }
  cout << profit << endl;
  return 0;
}
