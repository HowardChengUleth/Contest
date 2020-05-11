#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main(void)
{
  int cases;

  cin >> cases;
  cin.ignore();
  cin.ignore();
  while (cases-- > 0) {
    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);
    cin.ignore();

    istringstream is1(line1), is2(line2);
    vector<int> p;
    int t;
    
    while (is1 >> t) {
      p.push_back(t);
    }
    
    vector<string> Xp(p.size());
    for (unsigned int i = 0; i < p.size(); i++) {
      string d;
      is2 >> d;
      Xp[p[i]-1] = d;
    }
    for (unsigned int i = 0; i < p.size(); i++) {
      cout << Xp[i] << endl;
    }
    
    if (cases) {
      cout << endl;
    }
  }
  return 0;
}
