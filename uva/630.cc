#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

string signature(const string &s)
{
  string sig = s;
  sort(sig.begin(), sig.end());
  return sig;
}

void solve(void)
{
  int n;
  map<string, vector<string> > dict;

  cin >> n;
  while (n-- > 0) {
    string s;
    cin >> s;
    dict[signature(s)].push_back(s);
  }

  string word;
  while (cin >> word && word != "END") {
    cout << "Anagrams for: " << word << endl;
    string sig = signature(word);
    if (dict.find(sig) == dict.end()) {
      cout << "No anagrams for: " << word << endl;
    } else {
      for (int i = 0; i < dict[sig].size(); i++) {
	cout << setw(3) << i+1 << ") " << dict[sig][i] << endl;
      }
    }
  }
}

int main(void)
{
  int M;
  cin >> M;
  while (M-- > 0) {
    solve();
    if (M) cout << endl;
  }
  return 0;
}
