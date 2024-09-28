#include <iostream>
#include <string>
#include <cctype>

using namespace std;

void solve()
{
  string line;
  getline(cin, line);

  bool seen[26] = {false};
  
  for (int i = 0; i < line.length(); i++) {
    if (!isalpha(line[i])) continue;
    char c = tolower(line[i]);
    seen[c - 'a'] = true;
  }

  string missing;
  for (int i = 0; i < 26; i++) {
    if (!seen[i]) {
      missing += ('a' + i);
    }
  }

  if (missing == "") {
    cout << "pangram" << endl;
  } else {
    cout << "missing " << missing << endl;
  }
}

int main()
{
  string line;
  
  int N;
  cin >> N;
  getline(cin, line);

  for (int i = 0; i < N; i++) {
    solve();
  }

  
  return 0;
}
