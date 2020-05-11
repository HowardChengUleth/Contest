#include <iostream>
#include <string>


using namespace std;

void do_case()
{
  int N;
  cin >> N;
  string s;
  cin >> s;

  int count[8] = {0};

  for (int i = 0; i < 38; i++) {
    int num = 0;
    for (int j = 0; j < 3; j++) {
      num = 2*num + (s[i+j] == 'H');
    }
    count[num]++;
  }

  cout << N;
  for (int i = 0; i < 8; i++) {
    cout << ' ' << count[i];
  }
  cout << endl;
}

int main(void)
{
  int P;
  cin >> P;
  while (P-- > 0) {
    do_case();
  }
  return 0;
}
