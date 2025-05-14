#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, Y;
  cin >> N >> Y;

  bool seen[100] = { false };

  for (int i = 0; i < Y; i++) {
    int k;
    cin >> k;
    seen[k] = true;
  }

  int found = 0;
  for (int i = 0; i < N; i++) {
    if (!seen[i]) {
      cout << i << endl;
    } else {
      found++;
    }
  }

  cout << "Mario got " << found << " of the dangerous obstacles." << endl;

  return 0;
}
