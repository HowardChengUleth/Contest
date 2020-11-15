// this is just a simulation problem...as with all simulation, follow all
// rules carefully

#include <bits/stdc++.h>

using namespace std;

int N;
int pt[100000];

int winner1()
{
  int len[2] = {0};
  int i, j;
  for (i = 0; i < N; i = j) {
    for (j = i+1; j < N && pt[i] == pt[j]; j++)
      ;
    len[pt[i]] = max(len[pt[i]], j-i);
  }
  if (len[0] > len[1]) {
    return 0;
  } else if (len[0] < len[1]) {
    return 1;
  } else {
    return -1;
  }
}

int winner2()
{
  int lead[2] = {0};
  int score = 0;
  for (int i = 0; i < N; i++) {
    score += (pt[i] ? 1 : -1);
    int player = (score > 0);
    lead[player] = max(lead[player], abs(score));
  }
  if (lead[0] > lead[1]) {
    return 0;
  } else if (lead[1] > lead[0]) {
    return 1;
  } else {
    return -1;
  }
}

int main()
{
  cin >> N;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    pt[i] = (s[0] == 'Y');
  }

  if (winner1() == winner2()) {
    cout << "Agree" << endl;
  } else {
    cout << "Disagree" << endl;
  }

  return 0;
}
