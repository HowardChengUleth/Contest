#include <bits/stdc++.h>

using namespace std;

int main()
{
  string s;
  getline(cin, s);

  if (s.substr(s.length()-3) == "eh?") {
    cout << "Canadian!" << endl;
  } else {
    cout << "Imposter!" << endl;
  }
  
  return 0;
}
