#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> person(n);
  iota(begin(person), end(person), 0);

  vector<int> opus(n);
  for (auto &x : opus) {
    cin >> x;
  }

  int curr = 0;
  while (person.size() > 1) {
    int skip = opus[person[curr]];
    int leave = (curr + skip - 1) % person.size();
    person.erase(begin(person) + leave);
    curr = (leave < person.size()) ? leave : 0;
  }

  cout << person[0]+1 << endl;
  
  return 0;
}
