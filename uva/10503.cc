#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

pair<int,int> piece[14];
int n, m;
int start, end;

bool possible(int perm[], int n, int m, int last, int index = 0)
{
  if (index >= n) {
    return last == end;
  }

  for (int i = index; i < m; i++) {
    swap(perm[i], perm[index]);
    if (last == piece[perm[index]].first &&
	possible(perm, n, m, piece[perm[index]].second, index+1)) {
      return true;
    }
    if (last == piece[perm[index]].second &&
	piece[perm[index]].first != piece[perm[index]].second &&
	possible(perm, n, m, piece[perm[index]].first, index+1)) {
      return true;
    }
    
    swap(perm[i], perm[index]);
  }

  return false;
}

bool solve()
{
  cin >> n;
  if (n == 0) return false;
  cin >> m;

  int dummy;

  // first and last piece can't rotate?
  cin >> dummy >> start;
  cin >> end >> dummy;
  for (int i = 0; i < m; i++) {
    cin >> piece[i].first >> piece[i].second;
  }

  int perm[14];
  for (int i = 0; i < m; i++) {
    perm[i] = i;
  }
  if (possible(perm, n, m, start)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return true;
}

int main(void)
{
  while (solve())
    ;

  return 0;
}
