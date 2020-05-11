#include <iostream>
#include <map>

using namespace std;

bool solve()
{
  int n;
  cin >> n;
  if (!n) return false;

  int a, b;
  cin >> a >> b;
  
  map<int,int> step;

  long long x = 0;
  int i = 0;
  while (step.find(x) == step.end()) {
    step[x] = i++;
    x = (x*x) % n;
    x = (a*x) % n;
    x = (x+b) % n;
  }

  cout << n - (i-step[x]) << endl;
  return true;
}

int main()
{
  while (solve())
    ;
  return 0;
}
