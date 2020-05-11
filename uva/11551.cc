#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

typedef vector<vector<int> > Matrix;

const int MODULUS = 1000;

// Sets src = dest.
void CopyMatrix(const Matrix &src, Matrix *dest) {
  dest->resize(src.size());
  for (int i = 0; i < src.size(); ++i) {
    (*dest)[i].assign(src[i].begin(), src[i].end());
  }
}

// Computes c = ab with elements mod MODULUS without optimization (i.e. O(n^3)).
void MatrixMultiply(const Matrix &a, const Matrix &b, Matrix *c) {
  assert(a.size());
  assert(b.size());
  assert(a[0].size() == b.size());

  int num_cols = static_cast<int>(b[0].size());
  int num_rows = static_cast<int>(a.size());

  Matrix result(num_rows, vector<int>(num_rows));

  for (int i = 0; i < num_rows; ++i) {
    for (int j = 0; j < num_cols; ++j) {
      int sum = 0;
      for (int y = 0; y < a[i].size(); ++y) {
        sum += a[i][y] * b[y][j];
        sum %= MODULUS;
      }
      result[i][j] = sum;
    }
  }

  // Copy result to c.
  CopyMatrix(result, c);
}

// Performs binary exponentiation: c = a^b (mod MODULUS).
void MatrixBinExp(const Matrix &a, const int &b, Matrix *c) {
  c->resize(static_cast<int>(a.size()),
            vector<int>(static_cast<int>(a.size()), 0));

  // Initialize c to be identity matrix.
  for (int i = 0; i < a.size(); ++i) {
    (*c)[i][i] = 1;
  }

  Matrix buf(static_cast<int>(a.size()),
             vector<int>(static_cast<int>(a.size())));
  
  // Set buf = a.
  CopyMatrix(a, &buf);

  int n = b;

  while (n) {
    if (n & 1) {
      MatrixMultiply(*c, buf, c);
      n--;
    }
    MatrixMultiply(buf, buf, &buf);
    n >>= 1;
  }
}

int main() {
  int num_cases;
  scanf("%d", &num_cases);

  while (num_cases--) {
    int vector_size;
    int num_iterations;
    scanf("%d %d", &vector_size, &num_iterations);

    // Read in initial vector.
    Matrix initial_vector(vector_size, vector<int>(1));
    for (int i = 0; i < vector_size; ++i) {
      scanf("%d", &initial_vector[i][0]);
    }

    // Read in transformation matrix.
    Matrix transform_matrix(vector_size, vector<int>(vector_size, 0));
    for (int i = 0; i < vector_size; ++i) {
      int num_elements_to_add;

      scanf("%d", &num_elements_to_add);
      for (int j = 0; j < num_elements_to_add; ++j) {
        int element_index;
        scanf("%d", &element_index);
        transform_matrix[i][element_index] = 1;
      }
    }

    Matrix repeated_transform(vector_size, vector<int>(vector_size));
    Matrix result_vector(vector_size, vector<int>(1));

    MatrixBinExp(transform_matrix, num_iterations, &repeated_transform);
    MatrixMultiply(repeated_transform, initial_vector, &result_vector);

    // Output result.
    for (int i = 0; i < result_vector.size(); ++i) {
      printf("%s%d", i ? " " : "", result_vector[i][0]);
    }
    printf("\n");
  }

  return 0;
}
