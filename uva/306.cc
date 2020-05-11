#include <iostream>
#include <string>

using namespace std;

int find_cycle(int perm[], int n, int index, int cycle[])
{
  int len = 0;
  int start = index;
  cycle[len++] = index;
  index = perm[index];

  while (start != index) {
    cycle[len++] = index;
    index = perm[index];
  }
  return len;
}

void apply(int n, int cycle[200][200], int cycle_len[200], string &text, int k)
{
  string old = text;

  for (int i = 0; i < n; i++) {
    int kk = k % cycle_len[i];
    text[cycle[i][kk]] = old[i];
  }
}

int main(void)
{
  int n;
  int perm[200];
  int cycle_len[200];
  int cycle[200][200];
  
  while (cin >> n && n > 0) {
    for (int i = 0; i < n; i++) {
      cin >> perm[i];
      perm[i]--;
    }
    
    for (int i = 0; i < n; i++) {
      cycle_len[i] = find_cycle(perm, n, i, cycle[i]);
    }

    int k;
    while (cin >> k && k > 0) {
      cin.ignore(1);
      string text;
      getline(cin, text);
      text.resize(n, ' ');
      apply(n, cycle, cycle_len, text, k);
      cout << text << endl;
    }
    cout << endl;
  }
  return 0;
}
