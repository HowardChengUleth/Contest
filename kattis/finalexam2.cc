#include <bits/stdc++.h>

using namespace std;

int main()
{
  int score = 0;

  int n;
  cin >> n;

  char prev = '\0';
  for (int i = 0; i < n; i++) {
    char ans;
    cin >> ans;
    score += (prev == ans);
    prev = ans;
  }

  cout << score << endl;
  return 0;
}
