#include <bits/stdc++.h>

using namespace std;

int policy(const string &seq, int pol)
{
  int count = 0;
  char state = seq[0];
  for (int i = 1; i < seq.length(); i++) {
    if (seq[i] != state) {
      count++;
    }
    state = seq[i];
    
    char newstate;
    if (pol == 0) {
      newstate = 'U';
    } else if (pol == 1) {
      newstate = 'D';
    } else {
      newstate = seq[i];
    }
    if (state != newstate) {
      count++;
    }
    state = newstate;
  }

  return count;
}

int main()
{
  string seq;
  cin >> seq;

  for (int i = 0; i < 3; i++) {
    cout << policy(seq, i) << endl;
  }
 

  return 0;
}
