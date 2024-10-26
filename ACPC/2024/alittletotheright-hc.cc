#include <bits/stdc++.h>

using namespace std;

typedef vector<int> Trophy;

Trophy read_trophy(int p)
{
  Trophy t(p);
  for (auto &x : t) {
    cin >> x;
  }
  return t;
}

struct Compare
{
  int key;

  Compare(int k)
    : key{k} { }
  
  bool operator()(const Trophy &t1, const Trophy &t2) const {
    return t1[key] < t2[key];
  }
};

int main()
{
  int n, p;
  cin >> n >> p;

  Trophy trophy[1000];
  for (int i = 0; i < n; i++) {
    trophy[i] = read_trophy(p);
  }

  bool inc[50];
  fill(inc, inc+p, true);

  int ans = 0;
  for (int i = 0; i < p; i++) {
    if (!inc[i]) continue;
    sort(trophy, trophy+n, Compare(i));

    for (int j = 1; j < n; j++) {
      if (trophy[j][i] == trophy[j-1][i]) {
	inc[i] = false;
	break;
      }
    }

    if (inc[i]) {
      for (int k = i+1; k < p; k++) {
	bool good = true;
	for (int j = 1; j < n; j++) {
	  good &= (trophy[j-1][k] < trophy[j][k]);
	}
	if (good) {
	  inc[k] = false;
	}
      }
    }
  }

  cout << count(inc, inc+p, true) << endl;
  
  return 0;
}
