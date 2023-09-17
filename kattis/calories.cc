#include <bits/stdc++.h>

using namespace std;

const int cal[5] = {9, 4, 4, 4, 7};

void process(const string &line, double &fatC, double &totalC)
{
  int amount[5];
  char type[5];
  
  istringstream iss(line);
  for (int i = 0; i < 5; i++) {
    string item;
    iss >> item;
    amount[i] = stoi(item);
    type[i] = item.back();
  }

  double c[5];
  double total = 0.0, total_perc = 0.0;

  for (int i = 0; i < 5; i++) {
    if (type[i] == 'g') {
      c[i] = amount[i]*cal[i];
      total += c[i];
    } else if (type[i] == 'C') {
      c[i] = amount[i];
      total += c[i];
    } else {
      assert(type[i] == '%');
      total_perc += amount[i];
    }
  }

  total = total*100.0/(100.0-total_perc);
  for (int i = 0; i < 5; i++) {
    if (type[i] == '%') {
      c[i] = (amount[i]/100.00)*total;
    }
  }

  fatC += c[0];
  totalC += total;
}

int main(void)
{
  string line;
  double fatC, totalC;

  while (getline(cin, line) && line != "-") {
    fatC = totalC = 0.0;
    process(line, fatC, totalC);
    while (getline(cin, line) && line != "-") {
      process(line, fatC, totalC);
    }
    cout << fixed << setprecision(0) << fatC * 100.0 / totalC << '%' << endl;
  }
  
  return 0;
}
