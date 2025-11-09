#include <bits/stdc++.h>

using namespace std;

int minnum(string s)
{
  if (s == "D" || s == "0") {
    return 0;
  }
  
  replace(begin(s), end(s), 'B', '8');
  replace(begin(s), end(s), '0', 'D');   // in case of leading 0
  replace(begin(s) + 1, end(s), 'D', '0');
  return stoi(s, nullptr, 16);
}

int maxnum(string s)
{
  replace(begin(s), end(s), '8', 'B');
  replace(begin(s), end(s), '0', 'D');
  return stoi(s, nullptr, 16);
}

int main()
{
  int N;
  cin >> N;
  
  int maxsum = 0;
  int minsum = 0;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;

    maxsum += maxnum(s);
    minsum += minnum(s);
  }

  cout << hex << uppercase << maxsum << endl;
  cout << hex << uppercase << minsum << endl;

  return 0;
}
