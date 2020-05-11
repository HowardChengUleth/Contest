#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(void)
{
  int n;
  cin >> n;

  string country, name;
  map<string, int> m;

  while (n-- > 0) {
    cin >> country;
    getline(cin, name);
    m[country]++;
  }

  for (map<string,int>::const_iterator it = m.begin(); it != m.end(); ++it) {
    cout << it->first << " " << it->second << endl;
  }
  return 0;
}
    
    
