#include <iostream>
#include <algorithm>

using namespace std;

bool do_case()
{
  int N;
  cin >> N;
  if (N == 0) {
    return false;
  }

  int Dyoung[26][26], Dold[26][26];
  for (int i = 0; i < 26; i++) {
    fill(Dyoung[i], Dyoung[i]+26, -1);
    fill(Dold[i], Dold[i]+26, -1);
    Dyoung[i][i] = 0;
    Dold[i][i] = 0;
  }

  for (int i = 0; i < N; i++) {
    char y, d, s, t;
    int C;
    cin >> y >> d >> s >> t >> C;
    int u = s - 'A', v = t - 'A';

    if (u == v) continue;

    if (y == 'Y') {
      if (Dyoung[u][v] < 0) {
	Dyoung[u][v] = C;
      } else {
	Dyoung[u][v] = min(Dyoung[u][v], C);
      }
      
      if (d == 'B') {
	if (Dyoung[v][u] < 0) {
	  Dyoung[v][u] = C;
	} else {
	  Dyoung[v][u] = min(Dyoung[v][u], C);
	}
      }
    } else {
      if (Dold[u][v] < 0) {
	Dold[u][v] = C;
      } else {
	Dold[u][v] = min(Dold[u][v], C);
      }
      if (d == 'B') {
	if (Dold[v][u] < 0) {
	  Dold[v][u] = C;
	} else {
	  Dold[v][u] = min(Dold[v][u], C);
	}
      }
    }
  }

  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) {
	if (Dyoung[i][k] >= 0 && Dyoung[k][j] >= 0) {
	  if (Dyoung[i][j] < 0 || Dyoung[i][k] + Dyoung[k][j] < Dyoung[i][j]) {
	    Dyoung[i][j] = Dyoung[i][k] + Dyoung[k][j];
	  }
	}
	if (Dold[i][k] >= 0 && Dold[k][j] >= 0) {
	  if (Dold[i][j] < 0 || Dold[i][k] + Dold[k][j] < Dold[i][j]) {
	    Dold[i][j] = Dold[i][k] + Dold[k][j];
	  }
	}
      }
    }
  }

  char s, t;
  cin >> s >> t;
  
  int best_dist = -1;
  for (int k = 0; k < 26; k++) {
    if (Dyoung[s-'A'][k] < 0 || Dold[t-'A'][k] < 0) continue;
    if (best_dist < 0 || Dyoung[s-'A'][k] + Dold[t-'A'][k] < best_dist) {
      best_dist = Dyoung[s-'A'][k] + Dold[t-'A'][k];
    }
  }
  
  if (best_dist < 0) {
    cout << "You will never meet." << endl;
  } else {
    cout << best_dist;
    for (int k = 0; k < 26; k++) {
      if (Dyoung[s-'A'][k] < 0 || Dold[t-'A'][k] < 0) continue;
      if (best_dist == Dyoung[s-'A'][k] + Dold[t-'A'][k]) {
	cout << ' ' << (char)('A' + k);
      }
    }
    cout << endl;
  }
  
  return true;
}

int main(void)
{
  while (do_case())
    ;

  return 0;
}
