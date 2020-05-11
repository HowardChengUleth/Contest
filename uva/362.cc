#include <iostream>
#include <cmath>

using namespace std;

bool do_case(int case_num)
{
  int size;

  cin >> size;
  if (size == 0) {
    return false;
  }

  cout << "Output for data set " << case_num << ", " 
       << size << " bytes:" << endl;

  int seconds = 0, last5 = 0;
  while (size > 0) {
    int chunk;
    cin >> chunk;

    size -= chunk;
    last5 += chunk;
    seconds++;
    if (seconds % 5 == 0) {
      cout << "   Time remaining: ";
      if (last5) {
	// use integer calculations to avoid rounding problems
	cout << (5*size+last5-1)/last5 << " seconds" << endl;
      } else {
	cout << "stalled" << endl;
      }
      last5 = 0;
    }
  }
  cout << "Total time: " << seconds << " seconds" << endl << endl;
  return true;
}

int main(void)
{
  int case_num = 1;

  while (do_case(case_num++))
    ;

  return 0;
}
