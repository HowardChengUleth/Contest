#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int main(void)
{
  int count = 0;
  string s;
  
  while (cin >> s) {
    if (s.find('?') != string::npos) continue;
    int sign = (s.find('+') != string::npos) ? 1 : -1;
    replace(s.begin(), s.end(), '+', ' ');
    replace(s.begin(), s.end(), '-', ' ');
    replace(s.begin(), s.end(), '=', ' ');
    istringstream iss(s);
    int a, b, c;
    iss >> a >> b >> c;
    if (a + sign*b == c) {
      count++;
    }
  }
  cout << count << endl;
  
  return 0;
}
