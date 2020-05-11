#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

typedef pair<string,string> pss;

string signature(string s)
{
  string ans;
  for (int i = 0; i < s.length(); i++) {
    if (!isspace(s[i])) ans += s[i];
  }
  sort(ans.begin(), ans.end());
  return ans;
}

void solve()
{
  pss phrase[100];
  int n = 0;

  string line;
  while (getline(cin, line) && line != "") {
    phrase[n++] = make_pair(line, signature(line));
  }
  sort(phrase, phrase+n);

  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      if (phrase[i].second == phrase[j].second) {
	cout << phrase[i].first << " = " << phrase[j].first << endl;
      }
    }
  }
}

int main()
{
  int N;
  cin >> N;

  string line;
  getline(cin, line);
  getline(cin, line);
  
  for (int i = 0; i < N; i++) {
    if (i) cout << endl;
    solve();
  }
  return 0;
}
