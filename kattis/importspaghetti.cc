#include <bits/stdc++.h>

using namespace std;

int n;
map<string,int> namei;
string name[500];

const int INF = 1000000000;
int D[500][500];

int main()
{
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> name[i];
    namei[name[i]] = i;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      D[i][j] = INF;
    }
  }
  
  for (int i = 0; i < n; i++) {
    string s1;
    int L;
    cin >> s1 >> L;

    string line;
    getline(cin, line);
    for (int k = 0; k < L; k++) {
      getline(cin, line);
      for (auto &c : line) {
	if (c == ',') c = ' ';
      }
      istringstream iss(line);
      string s2;
      iss >> s2;
      assert(s2 == "import");
      while (iss >> s2) {
	D[namei[s1]][namei[s2]] = 1;
      }
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
	D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
      }
    }
  }

  int cycle_len = INF;
  int min_i = -1;
  for (int i = 0; i < n; i++) {
    cycle_len = min(cycle_len, D[i][i]);
    if (cycle_len == D[i][i]) {
      min_i = i;
    }
  }
  if (cycle_len == INF) {
    cout << "SHIP IT" << endl;
  } else {
    int c = min_i;
    for (int i = 0; i < cycle_len; i++) {
      cout << name[c] << ' ';
      for (int j = 0; j < n; j++) {
	if (D[c][j] == 1 && D[j][min_i] == cycle_len-i-1) {
	  c = j;
	  break;
	}
      }
    }
    cout << endl;
  }

  return 0;
}
