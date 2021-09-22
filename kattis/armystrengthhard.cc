#include <bits/stdc++.h>

using namespace std;

void solve()
{
  int NG, NM;
  cin >> NG >> NM;

  vector<int> G(NG), MG(NM);
  for (auto &x : G) {
    cin >> x;
  }
  for (auto &x : MG) {
    cin >> x;
  }

  int maxG = *max_element(begin(G), end(G));
  int maxMG = *max_element(begin(MG), end(MG));

  if (maxG >= maxMG) {
    cout << "Godzilla" << endl;
  } else {
    cout << "MechaGodzilla" << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
