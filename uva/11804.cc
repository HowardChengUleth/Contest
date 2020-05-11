#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

struct Player
{
  string name;
  int att, def;

  bool operator<(const Player &p) const
  {
    return name < p.name;
  }
};

int best_att_val, best_def_val;
bool best_subset[10];

void search(Player p[], int n, int k, bool subset[], int p_i)
{
  if (n < k) return;

  if (k == 0) {
    int att_val = 0;
    int def_val = 0;
    for (int i = 0; i < 10; i++) {
      if (subset[i]) {
	att_val += p[i].att;
      } else {
	def_val += p[i].def;
      }
    }

    if (att_val > best_att_val ||
	(att_val == best_att_val && def_val > best_def_val)) {
      copy(subset, subset+10, best_subset);
      best_att_val = att_val;
      best_def_val = def_val;
    }
    return;
  }

  subset[p_i] = true;
  search(p, n-1, k-1, subset, p_i+1);
  subset[p_i] = false;
  search(p, n-1, k, subset, p_i+1);
}

void solve()
{
  Player p[10];

  for (int i = 0; i < 10; i++) {
    cin >> p[i].name >> p[i].att >> p[i].def;
  }

  sort(p, p+10);

  best_att_val = best_def_val = 0;
  bool subset[10] = { false };
  search(p, 10, 5, subset, 0);
  
  bool printed = false;
  cout << "(";
  for (int i = 0; i < 10; i++) {
    if (best_subset[i]) {
      if (printed) cout << ", ";
      cout << p[i].name;
      printed = true;
    }
  }
  cout << ")" << endl;

  printed = false;
  cout << "(";
  for (int i = 0; i < 10; i++) {
    if (!best_subset[i]) {
      if (printed) cout << ", ";
      cout << p[i].name;
      printed = true;
    }
  }
  cout << ")" << endl;
}

int main(void)
{
  int T;
  cin >> T;
  for (int i = 1; i <= T; i++) {
    cout << "Case " << i << ":" << endl;
    solve();
  }

  return 0;
}
