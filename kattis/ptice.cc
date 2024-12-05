#include <bits/stdc++.h>

using namespace std;

const string name[] = {
  "Adrian", "Bruno", "Goran"
};

const string pattern[] = {
  "ABC", "BABC", "CCAABB"
};

int match(string correct, string pattern)
{
  int ans = 0;
  for (int i = 0; i < correct.length(); i++) {
    ans += (correct[i] == pattern[i % pattern.length()]);
  }

  return ans;
}

int main()
{
  int N;
  cin >> N;

  string correct;
  cin >> correct;

  int matches[3] = {0};
  for (int i = 0; i < 3; i++) {
    matches[i] = match(correct, pattern[i]);
  }

  int M = *max_element(matches, matches+3);
  cout << M << endl;
  for (int i = 0; i < 3; i++) {
    if (matches[i] == M) {
      cout << name[i] << endl;
    }
  }
  
  return 0;
}
