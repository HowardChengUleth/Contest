#include <bits/stdc++.h>

using namespace std;

int get_total()
{
  int total = 0;

  string line;
  while (getline(cin, line) && line != "") {
    total += stoi(line);
  }
  return total;
}

int main()
{
  vector<int> elf;

  int total;
  while ((total = get_total()) > 0) {
    elf.push_back(total);
  }
  sort(begin(elf), end(elf));
  int n = elf.size();

  cout << elf[n-1]+elf[n-2]+elf[n-3] << endl;

  
  return 0;
}
