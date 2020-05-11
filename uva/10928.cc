#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main(void)
{
  int N;
  cin >> N; cin.ignore(1);
  while (N--) {
    int P;
    cin >> P; cin.ignore(1);
    int count[1000];
    fill(count, count+P, 0);
    for (int i = 0; i < P; i++) {
      string line;
      getline(cin, line);
      istringstream iss(line);
      int dummy;
      while (iss >> dummy) {
	count[i]++;
      }
    }

    int minimum = *min_element(count, count+P);
    bool printed = false;
    for (int i = 0; i < P; i++) {
      if (count[i] == minimum) {
	if (printed) {
	  cout << ' ';
	}
	cout << i+1;
	printed = true;
      }
    }
    
    cout << endl;
  }
  return 0;
}
