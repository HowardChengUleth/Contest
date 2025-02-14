#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

string name[10];
int n;
bool bad[10][10];

bool check(int perm[10])
{
  for (int i = 0; i < n-1; i++) {
    if (bad[perm[i]][perm[i+1]]) {
      return false;
    }
  }

  return true;
}

bool solve()
{
  if (!(cin >> n))
    return false;

  for (int i = 0; i < n; i++) {
    cin >> name[i];
    fill(bad[i], bad[i]+n, false);
  }
  sort(name, name+n);

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    string n1, n2;
    cin >> n1 >> n2;
    int i1 = find(name, name+n, n1) - name;
    int i2 = find(name, name+n, n2) - name;
    
    bad[i1][i2] = true;
    bad[i2][i1] = true;;
  }

  int perm[10];
  for (int i = 0; i < n; i++) {
    perm[i] = i;
  }

  do {
    if (check(perm)) {
      for (int i = 0; i < n; i++) {
	cout << name[perm[i]] << ' ';
      }
      cout << endl;
      return true;
    }
  } while (next_permutation(perm, perm+n));

  cout << "You all need therapy." << endl;
  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
