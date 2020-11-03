#include <iostream>
#include <string>

using namespace std;

int main()
{
  string N, M;
  cin >> N >> M;

  int n = N.length();
  int m = M.length()-1;

  if (m+1 > n) {
    N = string(m+1-n, '0') + N;
    n = N.length();
  }
  
  string intpart = N.substr(0, n-m), decpart = N.substr(n-m);

  while (decpart[decpart.length()-1] == '0') {
    decpart.erase(decpart.length()-1);
  }
  if (decpart != "") {
    cout << intpart << "." << decpart << endl;
  } else {
    cout << intpart << endl;
  }
  
  return 0;
}