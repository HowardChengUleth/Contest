#include <iostream>
#include <map>

using namespace std;

void read_tree(int pos, map<int, int> &pile)
{
  int num;

  cin >> num;
  if (num == -1) {
    return;
  }

  pile[pos] += num;
  read_tree(pos-1, pile);
  read_tree(pos+1, pile);
}

bool solve_case(int num)
{
  map<int,int> pile;

  read_tree(0, pile);

  if (pile.size() == 0) {
    return false;
  }

  cout << "Case " << num << ":" << endl;
  for (map<int,int>::const_iterator it = pile.begin(); it != pile.end(); ++it) {
    if (it != pile.begin()) cout << ' ';
    cout << it->second;
  }
  cout << endl;

  return true;
}

int main(void)
{
  int num = 1;
  while (solve_case(num++)) {
    cout << endl;
  }
  return 0;
}
