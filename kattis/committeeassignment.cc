#include <bits/stdc++.h>

using namespace std;

int n, m;
map<string, int> namei;
bool bad[15][15];

int lookup(const string &s)
{
  if (namei.find(s) == namei.end()) {
    int i = namei.size();
    namei[s] = i;
  }
  return namei[s];
}

int search(int label[], int index, int num)
{
  if (index >= n)
    return num;

  int ans = n;
  for (int i = 0; i <= num; i++) {
    if (i+1 > ans) break;
    label[index] = i;
    bool good = true;
    for (int j = 0; j < index && good; j++) {
      good &= (!bad[j][index] || label[j] != label[index]);
    }
    if (good) {
      ans = min(ans, search(label, index+1, max(i+1, num)));
    }
    label[index] = 0;
  }
  return ans;
}

bool solve()
{
  cin >> n >> m;
  if (!n && !m)
    return false;

  namei.clear();
  for (int i = 0; i < n; i++) {
    fill(bad[i], bad[i]+n, false);
  }
  
  for (int i = 0; i < m; i++) {
    string n1, n2;
    cin >> n1 >> n2;

    int i1 = lookup(n1);
    int i2 = lookup(n2);
    bad[i1][i2] = bad[i2][i1] = true;
  }

  int label[15] = {0};
  cout << search(label, 1, 1) << endl;

  return true;
}

int main()
{
  while (solve())
    ;

  return 0;
}
