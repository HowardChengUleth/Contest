#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

bool solve(bool first)
{
  int n;
  cin >> n;
  if (n == 0) {
    return false;
  }

  if (!first) {
    cout << endl;
  }

  // use pairs: first component is the element, second component is the
  // index
  pii L1[5000], L2[5000];
  for (int i = 0; i < n; i++) {
    cin >> L1[i].first;
    L1[i].second = i;
  }
  for (int i = 0; i < n; i++) {
    cin >> L2[i].first;
    L2[i].second = i;
  }

  // sort by element (first component)
  sort(L1, L1+n);
  sort(L2, L2+n);

  // now use a map to remember the translation of elements from first
  // list to second list
  map<int, int> trans;
  for (int i = 0; i < n; i++) {
    trans[L1[i].first] = L2[i].first;
  }

  // switch first and second component in list 1 so we can sort it and
  // get it back to original order
  for (int i = 0; i < n; i++) {
    swap(L1[i].first, L1[i].second);
  }
  sort(L1, L1+n);

  // now do the final output
  for (int i = 0; i < n; i++) {
    cout << trans[L1[i].second] << endl;
  }
  

  return true;
}

int main()
{
  bool first = true;
  while (solve(first)) {
    first = false;
  }
  
  return 0;
}
