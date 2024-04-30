#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  int ans = 0;
  while (N--) {
    string s;
    cin >> s;
    transform(begin(s), end(s), begin(s), ::tolower);
    if (s.find("rose") != string::npos ||
	s.find("pink") != string::npos) {
      ans++;
    }
  }

  if (ans) {
    cout << ans << endl;
  } else {
    cout << "I must watch Star Wars with my daughter" << endl;
  }


  
  return 0;
}
