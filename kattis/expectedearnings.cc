#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main()
{
  int n, k;
  double p;

  cin >> n >> k >> p;
  if ((n-k)*p < k*(1 - p)) {
    cout << "spela" << endl;
  } else {
    cout << "spela inte!" << endl;
  }

  return 0;
}

/*
int main()
{
  ll n, k, p;
  double dp;

  const ll mult = 100'000'000;

  cin >> n >> k >> dp;
  p = dp * mult + 0.5;
  if ((n-k)*p < k*(mult - p)) {
    cout << "spela" << endl;
  } else {
    cout << "spela inte!" << endl;
  }

  return 0;
}
*/
