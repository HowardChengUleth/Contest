#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

int dist2(pii p1, pii p2)
{
  int dx = p1.first - p2.first, dy = p1.second - p2.second;
  return dx*dx + dy*dy;
}

void split_set(pii prev, pii guess, const set<pii> &cand,
	       set<pii> &closer, set<pii> &farther, set<pii> &same)
{
  closer.clear();
  farther.clear();
  same.clear();

  for (auto p : cand) {
    int d1 = dist2(prev, p);
    int d2 = dist2(guess, p);
    if (d1 == d2) {
      same.insert(p);
    } else if (d1 < d2) {
      farther.insert(p);
    } else {
      closer.insert(p);
    }
  }
  
  
}

int main()
{
  pii prev(4,4);
  set<pii> cand;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      cand.emplace(i, j);
    }
  }

  cout << prev.first << ' ' << prev.second << " ." << endl;
  while (cand.size() > 1) {
    set<pii> closer, farther, same;
    int bestsize = 1000;
    pii best_guess;
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
	set<pii> C, F, S;
	split_set(prev, pii(i, j), cand, C, F, S);
	int maxsize = max(C.size(), max(F.size(), S.size()));
	if (maxsize < bestsize) {
	  bestsize = maxsize;
	  closer.swap(C);
	  farther.swap(F);
	  same.swap(S);
	  best_guess = pii(i, j);
	}
      }
    }

    cout << best_guess.first << ' ' << best_guess.second << " ?" << endl;
    prev = best_guess;
    
    string resp;
    cin >> resp;
    if (resp == "Same") {
      cand.swap(same);
    } else if (resp == "Farther") {
      cand.swap(farther);
    } else {
      cand.swap(closer);
    }
  }

  for (auto [r, c] : cand) {
    cout << r << ' ' << c << " !" << endl;
  }

  return 0;
}
