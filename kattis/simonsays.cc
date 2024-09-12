#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  cin.ignore(1);

  for (int i = 0; i < N; i++) {
    string line;
    getline(cin, line);
    if (line.find("Simon says ") == 0) {
      cout << line.substr(11) << endl;
    }
  }
  

  return 0;
}
