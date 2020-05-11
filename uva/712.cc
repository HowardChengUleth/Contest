#include <iostream>
#include <string>

using namespace std;

int evaluate(const string tree, int n, const string order[], const string &vva)
{
  int len = tree.length();
  if (len == 1) {
    return tree[0] - '0';
  }

  int var = order[0][1] - '1';
  int start = (vva[var] - '0') * len/2;

  return evaluate(tree.substr(start, len/2), n, order+1, vva);

}

int main(void)
{
  int tree_num = 0;
  int n;

  while (cin >> n && n > 0) {
    cout << "S-Tree #" << ++tree_num << ":" << endl;
    
    string order[7];
    string tree;
    for (int i = 0; i < n; i++) {
      cin >> order[i];
    }
    cin >> tree;

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
      string vva;
      cin >> vva;
      cout << evaluate(tree, n, order, vva);
    }
    cout << endl << endl;
  }
  return 0;
}
