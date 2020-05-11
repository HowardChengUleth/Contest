#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int search(string &s, map<string, int> &result, int pieces)
{
  if (result.find(s) != result.end()) {
    return result[s];
  }

  result[s] = pieces;

  // try jumping right
  for (int i = 0; i < 10; i++) {
    if (s[i] == 'o' && s[i+1] == 'o' && s[i+2] == '-') {
      s[i] = s[i+1] = '-';
      s[i+2] = 'o';
      int temp = search(s, result, pieces-1);
      s[i] = s[i+1] = 'o';
      s[i+2] = '-';
      result[s] = min(temp, result[s]);
    }
  }

  // jump left
  for (int i = 0; i < 10; i++) {
    if (s[i] == '-' && s[i+1] == 'o' && s[i+2] == 'o') {
      s[i+1] = s[i+2] = '-';
      s[i] = 'o';
      int temp = search(s, result, pieces-1);
      s[i+1] = s[i+2] = 'o';
      s[i] = '-';
      result[s] = min(temp, result[s]);
    }
  }
  return result[s];
}

void solve()
{
  string s;
  cin >> s;

  int pieces = 0;
  for (int i = 0; i < 12; i++) {
    if (s[i] == 'o') pieces++;
  }
  
  map<string, int> result;
  cout << search(s, result, pieces) << endl;
}

int main()
{
  int n;
  cin >> n;
  while (n--) {
    solve();
  }
  return 0;
}
