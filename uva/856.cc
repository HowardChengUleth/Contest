#include <iostream>
#include <string>

using namespace std;

string word[] = { "zero", "one", "two", "three", "four", "five", "six",
		  "seven", "eight", "nine" };

string words[1000];

string key(const string &cipher, const string &word)
{
  string ans;

  for (unsigned int i = 0; i < cipher.length(); i++) {
    int add = cipher[i] - 'A' - word[i] + 'a';
    while (add < 1) {
      add += 26;
    }
    while (add > 26) {
      add -= 26;
    }
    ans += (char)('A' + add - 1);
  }
  return ans;
}

int main(void)
{
  for (int i = 0; i < 1000; i++) {
    int d0 = i % 10;
    int d1 = (i/10) % 10;
    int d2 = (i/100) % 10;
    words[i] = word[d2] + word[d1] + word[d0];
  }

  string cipher;
  bool first = true;
  while (cin >> cipher) {
    if (!first) cout << endl;
    for (int i = 999; i >= 0; i--) {
      if (words[i].length() != cipher.length()) continue;
      cout << key(cipher, words[i]) << " -> " << words[i] << endl;
    }

    first = false;
  }

  return 0;
}
