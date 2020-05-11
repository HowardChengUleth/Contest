#include <iostream>

using namespace std;

int soln(int n, int m, int c)
{
  // number of candidate lower right corners for a chessboard on that
  // row if the row ends with a white or black square
  int rowW = (m-8)/2 + 1;
  int rowB = (m > 8) ? (m-9)/2 + 1 : 0;
  
  // figure out number of rows that ends with white or black square
  int numrowW, numrowB;
  numrowW = numrowB = (n-7)/2;
  if ((n-7) % 2 == 1) {
    if (c) {
      numrowW++;
    } else {
      numrowB++;
    }
  }
  
  /*
  cout << "rowW = " << rowW << endl;
  cout << "rowB = " << rowB << endl;
  cout << "numrowW = " << numrowW << endl;
  cout << "numrowB = " << numrowB << endl;
  */
  return numrowW*rowW + numrowB*rowB;
}

int main(void)
{
  int n, m, c;
  while (cin >> n >> m >> c && (n || m || c)) {
    cout << soln(n, m, c) << endl;
  }
  return 0;
}
