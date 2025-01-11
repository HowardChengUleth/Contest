#include <bits/stdc++.h>

using namespace std;

const string present = "Present!";

int main()
{
  int N;
  cin >> N;

  string prev, name;
  int abscount = 0;
  
  N--;
  cin >> prev;
  for (int i = 0; i < N; i++) {
    cin >> name;
    if (prev != present && name != present) {
      cout << prev << endl;
      abscount++;
    }
    
    prev = name;
  }
  if (prev != present) {
    cout << prev << endl;
    abscount++;
  }

  if (abscount == 0) {
    cout << "No Absences" << endl;
  }
  
  return 0;
}
