#include <bits/stdc++.h>

using namespace std;

int num_pairs(const string &word, const string &pattern)
{
  auto pos = word.find(pattern);
  if (pos == string::npos)
    return 0;

  return 1 + num_pairs(word.substr(pos+1), pattern);
}

int num_pairs(const string &word)
{
  const string pattern[6] = { "aa", "ee", "ii", "oo", "uu", "yy" };
  int ans = 0;
  for (int i = 0; i < 6; i++) {
    ans += num_pairs(word, pattern[i]);
  }

  return ans;
}

bool solve()
{
  int N;

  cin >> N;
  if (N == 0)
    return false;

  string best_word;
  int best_val = -1;
  for (int i = 0; i < N; i++) {
    string word;
    cin >> word;
    int val = num_pairs(word);
    if (val > best_val) {
      best_word = word;
      best_val = val;
    }
  }
  cout << best_word << endl;

  return true;
}

int main()
{
  while (solve())
    ;
  
  return 0;
}
