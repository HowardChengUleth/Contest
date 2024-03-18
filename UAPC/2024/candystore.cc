#include <bits/stdc++.h>

using namespace std;

int main()
{
  map<string, vector<string>> M;

  int N, Q;
  cin >> N >> Q;
  for (int i = 0; i < N; i++) {
    string first, last;
    cin >> first >> last;
    string init = string(1, first[0]) + string(1, last[0]);
    M[init].push_back(first + " " + last);
  }

  for (int i = 0; i < Q; i++) {
    string init;
    cin >> init;

    if (M[init].size() == 0) {
      cout << "nobody" << endl;
    } else if (M[init].size() > 1) {
      cout << "ambiguous" << endl;
    } else {
      cout << M[init][0] << endl;
    }
  }
  return 0;
}
