#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  int sum[45] = {0};
  int count[45] = {0};

  cin >> N;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < s.length(); j++) {
      sum[j] += s[j];
      count[j]++;
    }
  }

  for (int i = 0; i < 45; i++) {
    if (count[i]) {
      cout << (char)(sum[i] / count[i]);
    }
  }
  cout << endl;

  return 0;
}
