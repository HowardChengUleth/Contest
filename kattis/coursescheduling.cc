#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  map<string, set< pair<string,string>>> freq;

  for (int i = 0; i < n; i++) {
    string first, last, course;
    cin >> first >> last >> course;
    freq[course].emplace(first, last);
  }

  for (auto [ name, S ] : freq) {
    cout << name << ' ' << S.size() << endl;
  }

  return 0;
}
