#include <bits/stdc++.h>

using namespace std;

void encode(const string &s)
{
  for (int i = 0; i < s.length(); ) {
    int j;
    for (j = 0; i+j < s.length() && s[i+j] == s[i]; j++)
      ;
    cout << s[i] << j;
    i += j;
  }
  cout << endl;
}

void decode(const string &s)
{
  for (int i = 0; i < s.length(); i += 2) {
    for (int j = 0; j < s[i+1] - '0'; j++) {
      cout << s[i];
    }
  }
    
  cout << endl;
}



int main()
{
  char cmd;
  string s;

  cin >> cmd >> s;
  if (cmd == 'E') {
    encode(s);
  } else {
    decode(s);
  }

  
  return 0;
}
