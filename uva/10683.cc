#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main(void)
{
  // cancel common factors between total and new total
  const int total = 12 * 3 * 3; // 24 * 60 * 60 * 100;
  const int newtotal = 5 * 5 * 5; // 10 * 100 * 100 * 100;
  string line;
  
  while (getline(cin, line)) {
    int HH, MM, SS, CC;
    HH = (line[0] - '0')*10 + line[1] - '0';
    MM = (line[2] - '0')*10 + line[3] - '0';
    SS = (line[4] - '0')*10 + line[5] - '0';
    CC = (line[6] - '0')*10 + line[7] - '0';

    long long part = ((HH * 60 + MM) * 60 + SS) * 100 + CC;
    long long newpart = part * newtotal / total;

    CC = newpart % 100;  newpart /= 100;
    SS = newpart % 100;  newpart /= 100;
    MM = newpart % 100;  newpart /= 100;
    HH = newpart;
    cout << setw(1) << setfill('0') << HH;
    cout << setw(2) << setfill('0') << MM;
    cout << setw(2) << setfill('0') << SS;
    cout << setw(2) << setfill('0') << CC;
    cout << endl;
  }
  return 0;
}
