#include <bits/stdc++.h>

using namespace std;

int main()
{
  const string item[] = { "keys", "phone", "wallet" };

  set<string> S;
  int N;
  cin >> N;
  while (N--) {
    string s;
    cin >> s;
    S.insert(s);
  }

  int found = 0;
  for (int i = 0; i < 3; i++) {
    if (S.count(item[i]) == 0) {
      cout << item[i] << endl;
    } else {
      found++;
    }
  }
  if (found == 3) {
    cout << "ready" << endl;
  }
      

  return 0;
}
