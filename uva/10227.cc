#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
  int C;
  cin >> C;
  cin.ignore(1);
  cin.ignore(1);

  while (C-- > 0) {
    bool opinion[100][100];
    int P, T;
    
    cin >> P >> T; cin.ignore(1);
    for (int i = 0; i < P; i++) {
      fill(opinion[i], opinion[i] + T, false);
    }
    
    while (cin.peek() != EOF && cin.peek() != '\n') {
      int person, tree;
      cin >> person >> tree;  cin.ignore(1);
      person--;  tree--;
      opinion[person][tree] = true;
    }

    bool skip[100];
    int count = 0;
    fill(skip, skip+P, false);

    for (int i = 0; i < P; i++) {
      if (skip[i]) continue;
      count++;
      for (int j = i+1; j < P; j++) {
	if (!skip[j] && equal(opinion[i], opinion[i] + T, opinion[j])) {
	  skip[j] = true;
	}
      }
    }

    cout << count << endl;
    if (C) {
      cout << endl;
    }
  }
  

  
  return 0;
}
