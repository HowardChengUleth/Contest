#include <bits/stdc++.h>

using namespace std;

int main()
{
  string key, cipher;
  cin >> cipher >> key;

  string plain;

  for (int i = 0; i < cipher.length(); i++) {
    int keyc;
    if (i < key.length()) {
      keyc = key[i] - 'A';
    } else {
      keyc = plain[i-key.length()] - 'A';
    }
    plain += (char)((cipher[i] - 'A' + (26 - keyc)) % 26 + 'A');
  }

  cout << plain << endl;

  return 0;
}
