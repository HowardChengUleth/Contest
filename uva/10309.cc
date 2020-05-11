#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Board {
public:
  Board(int rows = 0, int cols = 0) 
    : m_rows(0), m_cols(0), m_init(NULL), m_final(NULL) {
    setSize(rows, cols);
  }

  ~Board() {
    clear();
  }

  void setSize(int rows, int cols) {
    clear();

    m_rows = rows;
    m_cols = cols;
    m_init = new bool *[m_rows];
    m_final = new bool *[m_rows];
    for (int i = 0; i < m_rows; i++) {
      m_init[i] = new bool[m_cols];
      m_final[i] = new bool[m_cols];
      fill(m_init[i], m_init[i]+m_cols, false);
      fill(m_final[i], m_final[i]+m_cols, false);
    }
  }

  void solve() const;
  
  bool needToChange(int row, int col) const {
    return m_init[row][col] != m_final[row][col];
  }

  void findShortest(vector< vector<int> > &A, const vector<bool> &indep, 
		    vector<bool> &soln, vector<bool> &best, int &best_weight,
		    int curr_weight = 0, unsigned int index = 0) const;

  friend istream &operator>>(istream &is, Board &b);

private:
  int m_rows, m_cols;
  bool **m_init, **m_final;

  void clear(void) {
    for (int i = 0; i < m_rows; i++) {
      delete[] m_init[i];
      delete[] m_final[i];
    }
    delete[] m_init;
    delete[] m_final;
  }

  unsigned int numVars() const {
    return m_rows * m_cols;
  }
  
  unsigned int coords2Index(int row, int col) const {
    return row * m_cols + col;
  }
  
  void index2Coords(unsigned int index, int &row, int &col) const {
    row = index / m_cols;
    col = index % m_cols;
  }
};

istream &operator>>(istream &is, Board &b)
{
  int rows, cols;
  rows = cols = 10;
  b.setSize(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      char c;
      is >> c;
      b.m_init[i][j] = (c == 'O');
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      b.m_final[i][j] = 0;
    }
  }
  return is;
}

void Board::solve() const
{
  vector< vector<int> > A(numVars());   // last column is the RHS
  vector<bool> indep(numVars());        // whether a column is independent

  for (unsigned int i = 0; i < A.size(); i++) {
    A[i].resize(numVars()+1);
  }

  // form coefficient matrix
  for (unsigned int i = 0; i < numVars(); i++) {
    int row1, col1;
    index2Coords(i, row1, col1);
    for (unsigned int j = 0; j < numVars(); j++) {
      int row2, col2;
      index2Coords(j, row2, col2);
      A[i][j] = (abs(row1-row2) + abs(col1-col2) <= 1);
    }
  }

  // form right hand side vector
  for (unsigned int i = 0; i < numVars(); i++) {
    int row, col;
    index2Coords(i, row, col);
    A[i][numVars()] = needToChange(row, col);
  }

  // do elimination
  unsigned int rank = 0;
  for (unsigned int j = 0; j < numVars(); j++) {
    indep[j] = false;

    // find pivot
    unsigned int pivot;
    for (pivot = rank; pivot < numVars(); pivot++) {
      if (A[pivot][j]) {
	break;
      }
    }

    if (pivot >= numVars()) {
      // no pivot found
      continue;
    }
      
    // swap rows if necessary
    if (rank != pivot) {
      for (unsigned int k = 0; k <= numVars(); k++) {
	swap(A[rank][k], A[pivot][k]);
      }
    }

    // now eliminate
    for (unsigned int i = 0; i < numVars(); i++) {
      if (i == rank || A[i][j] == 0) continue;
      for (unsigned int k = 0; k <= numVars(); k++) {
	A[i][k] = (A[i][k] + A[rank][k]) % 2;
      }
    }
    rank++;
    indep[j] = true;
  }

  // check for solvability
  for (unsigned int i = rank+1; i < numVars(); i++) {
    if (A[i][numVars()]) {
      cout << -1 << endl;
      return;
    }
  }

  vector<bool> soln(numVars()), best(numVars());
  int best_weight = numVars();
  findShortest(A, indep, soln, best, best_weight);

  cout << ((best_weight > 100) ? -1 : best_weight) << endl;
}

void Board::findShortest(vector< vector<int> > &A, const vector<bool> &indep, 
			 vector<bool> &soln, vector<bool> &best, 
			 int &best_weight, int curr_weight, 
			 unsigned int index) const
{
  if (curr_weight >= best_weight) {
    return;
  }

  if (index < numVars()) {
    if (indep[index]) {
      findShortest(A, indep, soln, best, best_weight, curr_weight, index+1);
    } else {
      soln[index] = false;
      findShortest(A, indep, soln, best, best_weight, curr_weight, index+1);
      soln[index] = true;
      findShortest(A, indep, soln, best, best_weight, curr_weight+1, index+1);
      soln[index] = false;
    }
    return;
  }

  int weight = curr_weight;
  for (unsigned int i = 0; i < numVars(); i++) {
    if (!indep[i]) continue;
    soln[i] = (A[i][numVars()] == 1);
    for (unsigned int j = 0; j < numVars(); j++) {
      if (indep[i] || !A[i][j]) continue;
      soln[i] = !soln[i];
    }
    if (soln[i]) {
      weight++;
    }
  }
  if (weight < best_weight) {
    copy(soln.begin(), soln.end(), best.begin());
    best_weight = weight;
  }
}


int main(void)
{
  string name;
  while (cin >> name && name != "end") {
    Board board;
    cin >> board;
    cout << name << ' ';
    board.solve();
  }

  return 0;
}
