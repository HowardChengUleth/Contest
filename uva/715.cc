#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void do_case(void)
{
  int A, K;

  cin >> A >> K;

  bool less[26][26];
  for (int i = 0; i < A; i++) {
    fill(less[i], less[i]+A, false);
  }

  string prev, curr;
  cin >> prev;
  for (int i = 1; i < K; i++) {
    cin >> curr;

    for (string::size_type j = 0; j < prev.length() && j < curr.length();
	 j++) {
      if (prev[j] != curr[j]) {
	less[prev[j]-'a'][curr[j]-'a'] = true;
	break;
      }
    }

    prev = curr;
  }

  for (int k = 0; k < A; k++) {
    for (int i = 0; i < A; i++) {
      for (int j = 0; j < A; j++) {
	less[i][j] |= less[i][k] && less[k][j];
      }
    }
  }

  int below[26], above[26];
  fill(below, below+A, 0);
  fill(above, above+A, 0);
  for (int i = 0; i < A; i++) {
    for (int j = 0; j < A; j++) {
      if (less[i][j]) {
	below[j]++;
	above[i]++;
      }
    }
  }

  char mapping[256];
  for (int i = 0; i < 256; i++) {
    mapping[i] = i;
  }

  for (int i = 0; i < A; i++) {
    if (below[i] + above[i] == A-1) {
      mapping[i+'a'] = below[i] + 'a';
    } else {
      mapping[i+'a'] = '.';
    }
  }

  string ciphertext;
  getline(cin, ciphertext);
  getline(cin, ciphertext);
  for (string::size_type i = 0; i < ciphertext.length(); i++) {
    if (isalpha(ciphertext[i]) && mapping[ciphertext[i]] == '.') {
      cout << "Message cannot be decrypted." << endl;
      return;
    }
  }

  for (string::size_type i = 0; i < ciphertext.length(); i++) {
    cout << mapping[ciphertext[i]];
  }
  cout << endl;


}

int main(void)
{
  int N;
  cin >> N;
  while (N-- > 0) {
    do_case();
  }
  return 0;
}
