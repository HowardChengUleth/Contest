#include <bits/stdc++.h>

using namespace std;

bool deck_done(const vector<int> &deck)
{
  for (int i = 0; i < deck.size(); i++) {
    if (deck[i] != i) return false;
  }
  return true;
}

void do_shuffle(vector<int> &deck, string dir)
{
  vector<int> old = deck;
  int n = deck.size();

  int curr[2];
  if (dir == "out") {
    curr[0] = 0;
    curr[1] = (n+1)/2;
  } else {
    curr[0] = n/2;
    curr[1] = 0;
  }

  for (int h = 0; h < 2; h++) {
    for (int i = 0; i < (n+1)/2; i++) {
      deck[2*i+h] = old[curr[h]++];
    }
  }
}

int main()
{
  int n;
  string dir;

  cin >> n >> dir;

  vector<int> deck(n);
  iota(begin(deck), end(deck), 0);
  
  int count = 0;
  do {
    do_shuffle(deck, dir);
    count++;
  } while (!deck_done(deck));

  cout << count << endl;
  
  return 0;
}
