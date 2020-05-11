//
// if X = the number of coconuts on the last day, and 
//    P = number of people
//
// then the original number of coconuts is:
//
//   C = X*(P/(P-1))^P + (P/(P-1))^P * (P-1) - (P - 1)
//
// For this to be an integer, it must be true that X + P - 1 is divisible
// by (P-1)^P.  Assuming X > 0, we have X >= (P-1)^P - (P-1).  So in the
// formula above:
//
//   C >= ((P-1)^P - (P-1))*(P/(P-1))^P + (P/(P-1))^P * (P-1) - (P - 1)
//     =  (P/(P-1))^P * (P-1)^P - (P-1)

#include <iostream>
#include <cmath>

using namespace std;

double bound(int people)
{
  double p = people;
  
  return pow(p, p) - p + 1;
}

bool check(int coco, int people)
{
  for (int i = 0; i < people; i++) {
    if (coco <= 0) return false;
    if (coco % people != 1) return false;
    coco--;                     // to monkey
    coco -= coco/people;
  }
  return coco % people == 0;
}

int main()
{
  int coco;
  while (cin >> coco && coco >= 0) {
    int found = -1;
    for (int p = 2; bound(p) <= coco; p++) {
      if (check(coco, p)) {
	found = p;
      }
    }
    cout << coco << " coconuts, ";
    if (found >= 0) {
      cout << found << " people and 1 monkey" << endl;
    } else {
      cout << "no solution" << endl;
    }
  }
  return 0;
}
