#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;

  map<string,string> owner{
    { "fishing", "alice" },
    { "golf", "bob" },
    { "hockey", "charlie" }
  };

  for (int i = 0; i < N; i++) {
    string owner2, game, garbage;

    cin >> owner2 >> garbage >> garbage >> garbage >> game;
    if (owner[game] == owner2) {
      cout << owner2 << " already has " << game << endl;
    } else {
      cout << owner2 << " borrows " << game << " from " << owner[game] << endl;
    }
    owner[game] = owner2;
  }
  

  return 0;
}
