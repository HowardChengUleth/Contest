#include <bits/stdc++.h>

using namespace std;

void solve()
{
  string s;
  cin >> s;
  if (s == "P=NP") {
    cout << "skipped" << endl;
    return;
  }

  auto pos = s.find('+');
  int a = stoi(s.substr(0, pos));
  int b = stoi(s.substr(pos+1));
  cout << a+b << endl;

}

int main()
{
  int N;

  cin >> N;
  while (N--) {
    solve();
  }
  
  return 0;
}
