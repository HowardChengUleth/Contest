#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool consec(const string &s1, const string &s2)
{
  int n1 = atoi(s1.c_str()), n2 = atoi(s2.c_str());
  return n1+1 == n2;
}

bool solve(int id)
{
  int n;
  cin >> n;
  if (!n) return false;

  cout << "Case " << id << ":" << endl;
  
  string num[100000];
  for (int i = 0; i < n; i++) {
    cin >> num[i];
  }

  int i, j;
  for (i = 0; i < n; i = j) {
    for (j = i+1; j < n && consec(num[j-1], num[j]); j++)
      ;
    if (i == j-1) {
      cout << num[i] << endl;
    } else {
      cout << num[i] << "-";
      int k;
      for (k = 0; k < num[i].length() && num[i][k] == num[j-1][k]; k++)
	;
      cout << num[j-1].substr(k) << endl;
    }
  }

  cout << endl;
  return true;
}

int main()
{
  int id = 1;
  while (solve(id++))
    ;
  
  return 0;
}
