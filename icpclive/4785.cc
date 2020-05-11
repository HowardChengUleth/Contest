#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

class Scalar;

// will represent everything as a result.  dim = 0 for scalar, 1,2,3 for
// 1,2,3-dimensional array
class Result
{
public:
  int dim;

  virtual ~Result() { }
  virtual void print() const = 0;
  virtual void print_sep() const = 0;
  virtual void print_end() const = 0;
  virtual Result *clone() const = 0;
  virtual Scalar *to_scalar() const = 0;

  virtual void negate() = 0;

  // apply +, *, -
  virtual Result *elem_op(const Result *operand, char op) const = 0;

  // apply + /, - /, * /
  virtual Result *slash_op(char op) const = 0;

  // drop
  virtual Result *drop(uint n) const = 0;

  // rho
  virtual Result *rho(const Result *dims, int &index) const = 0;
};

class Scalar : public Result
{
public:
  int value;

  Scalar(int v = 0) : value(v) { dim = 0; }

  virtual void print() const
  {
    cout << value;
  }

  virtual void print_sep() const
  {
    cout << ' ';
  }

  virtual void print_end() const
  {
    cout << endl;
  }

  virtual Result *clone() const
  {
    return new Scalar(*this);
  }

  virtual Scalar *to_scalar() const
  {
    return new Scalar(*this);
  }

  virtual void negate()
  {
    value = -value;
  }

  // apply +, *, - element-wise
  virtual Result *elem_op(const Result *operand, char op) const;

  // apply + /, - /, * /
  virtual Result *slash_op(char op) const
  {
    return clone();
  }

  virtual Result *drop(uint n) const;
  virtual Result *rho(const Result *dims, int &index) const;
};

// a vector is a vector of anything (will work for 2/3-D as well)
class Vector : public Result
{
public:
  vector<Result *> vec;

  Vector() { dim = 1; }

  Vector(const Result *r) 
    : vec(1)
  {
    vec[0] = r->clone();
    dim = r->dim + 1;
  }

  Vector(const vector<Result *> &v) 
    : vec(v.size())
  { 
    vec.resize(v.size());
    for (uint i = 0; i < vec.size(); i++) {
      vec[i] = v[i]->clone();
      dim = v[0]->dim + 1;
    }
  }
  
  ~Vector() 
  {
    for (uint i = 0; i < vec.size(); i++) {
      delete vec[i];
    }
  }

  virtual void print() const
  {
    for (uint i = 0; i < vec.size(); i++) {
      if (i > 0) vec[i]->print_sep();
      vec[i]->print();
    }
  }

  virtual void print_sep() const
  {
    if (dim == 1) {
      cout << endl;
    } else {
      cout << endl << endl;
    }
  }

  virtual void print_end() const
  {
    cout << endl;
  }

  virtual Result *clone() const
  {
    return new Vector(vec);
  }

  virtual Scalar *to_scalar() const
  {
    assert(dim == 1 && vec.size() == 1);
    return vec[0]->to_scalar();
  }

  virtual void negate()
  {
    for (uint i = 0; i < vec.size(); i++) {
      vec[i]->negate();
    }
  }

  virtual Result *elem_op(const Result *operand, char op) const;
  virtual Result *slash_op(char op) const;
  virtual Result *drop(uint n) const;
  virtual Result *rho(const Result *dims, int &index) const;
};

Result *Scalar::elem_op(const Result *operand, char op) const
{
  // I am a scalar.
  if (operand->dim == 0 ||
      (operand->dim == 1 &&
      dynamic_cast<const Vector *>(operand)->vec.size() == 1)) {
    Scalar *s = operand->to_scalar();
    int opvalue = s->value;
    delete s;

    // operand is also scalar, the result is a scalar
    switch (op) {
    case '+':
      return new Scalar(value + opvalue);
    case '-':
      return new Scalar(value - opvalue);
    case '*':
      return new Scalar(value * opvalue);
    default:
      assert(false);
      return NULL;
    }
  } else {
    // the result is a vector
    const Vector *op_vec = dynamic_cast<const Vector *>(operand);
    vector<Result *> out(op_vec->vec.size());
    for (uint i = 0; i < out.size(); i++) {
      out[i] = op_vec->vec[i]->elem_op(this, op);
      if (op == '-') out[i]->negate();
    }
    Result *ans = new Vector(out);
    for (uint i = 0; i < out.size(); i++) {
      delete out[i];
    }
    return ans;
  }
}

Result *Vector::elem_op(const Result *operand, char op) const
{
  vector<Result *> out(vec.size());

  // check if I am really a vector
  if (dim == 1 && vec.size() == 1) {
    // I am really a scalar
    Scalar *s = to_scalar();
    Result *ans = s->elem_op(operand, op);
    delete s;
    return ans;
  }
  
  // I am a vector.
  if (operand->dim == 0 ||
      (operand->dim == 1 && 
      dynamic_cast<const Vector *>(operand)->vec.size() == 1)) { 
    // operand is scalar

    for (uint i = 0; i < out.size(); i++) {
      out[i] = vec[i]->elem_op(operand, op);
    }
  } else {
    // the other operand is a vector
    for (uint i = 0; i < out.size(); i++) {
      out[i] = vec[i]->elem_op(dynamic_cast<const Vector *>(operand)->vec[i], 
			       op);
    }
  }
  Result *ans = new Vector(out);
  for (uint i = 0; i < out.size(); i++) {
    delete out[i];
  }
  return ans;
}

Result *Vector::slash_op(char op) const
{
  Result *ans;
  if (dim == 1) {
    // just a list of scalars
    ans = vec[vec.size()-1]->clone();
    for (int i = (int)vec.size()-2; i >= 0; i--) {
      Result *old = ans;
      ans = vec[i]->elem_op(ans, op);
      delete old;
    }
  } else {
    assert(dim > 1);
    vector<Result *> out(vec.size());
    for (uint i = 0; i < vec.size(); i++) {
      out[i] = vec[i]->slash_op(op);
    }
    ans = new Vector(out);
    for (uint i = 0; i < out.size(); i++) {
      delete out[i];
    }
  }
  
  return ans;
}

Result *Scalar::drop(uint n) const
{
  Result *vec = new Vector(this);
  Result *ans = vec->drop(n);
  delete vec;
  return ans;
}

Result *Vector::drop(uint n) const
{
  vector<Result *> out;
  while (n < vec.size()) {
    out.push_back(vec[n]->clone());
    n++;
  }
  Result *ans = new Vector(out);
  for (uint i = 0; i < out.size(); i++) {
    delete out[i];
  }
  return ans;
}

Result *Scalar::rho(const Result *dims, int &index) const
{
  Result *vec = new Vector(this);
  Result *ans = vec->rho(dims, index);
  delete vec;
  return ans;
}

Result *Vector::rho(const Result *dims, int &index) const
{
  assert(dims->dim < 2);
  assert(dim == 1);

  if (dims->dim == 0) {
    Result *dims_vec = new Vector(dims);
    Result *ans = rho(dims_vec, index);
    delete dims_vec;
    return ans;
  }

  const Vector *dims_vec = dynamic_cast<const Vector *>(dims);
  Scalar *sizer = dims_vec->vec[0]->to_scalar();
  int size = sizer->value;
  delete sizer;

  vector<Result *> out;
  for (int i = 0; i < size; i++) {
    if (dims_vec->vec.size() == 1) {
      // 1-D vector
      out.push_back(vec[index++]->clone());
      if (index == (int)vec.size()) index = 0;
    } else {
      // 2-D or 3-D
      Result *new_dims = dims_vec->drop(1);
      out.push_back(rho(new_dims, index));
      delete new_dims;
    }
  }
  Result *ans = new Vector(out);
  for (uint i = 0; i < out.size(); i++) {
    delete out[i];
  }
  return ans;
}

Result *iota(int n)
{
  vector<Result *> out;
  for (int i = 1; i <= n; i++) {
    out.push_back(new Scalar(i));
  }
  Result *ans = new Vector(out);
  for (uint i = 0; i < out.size(); i++) {
    delete out[i];
  }
  return ans;
}

map<string, Result *> vars;

bool is_nested(const vector<string> &token, int start, int end)
{
  if (token[start] != "(" || token[end-1] != ")") {
    return false;
  }
  int level = 1;
  for (int i = start+1; i < end-1; i++) {
    if (token[i] == "(") level++;
    else if (token[i] == ")") level--;
    if (level == 0) return false;
  }
  return true;
}

int find_op(const vector<string> &token, int start, int end)
{
  const string ops[10] = {
    "+/", "-/", "*/", "+", "-", "*", "drop", "iota", "rho", "="
  };

  int level = 0;
  for (int i = start; i < end; i++) {
    if (token[i] == "(") level++;
    else if (token[i] == ")") level--;
    else if (level == 0) {
      if (find(ops + 0, ops + 10, token[i]) != ops + 10) {
	return i;
      }
    }
  }
  return -1;
}

Result *eval(const vector<string> &token, int start, int end)
{
  assert(start < end);

  // check to see if it is just ( expr )
  if (is_nested(token, start, end)) {
    return eval(token, start+1, end-1);
  }


  // find leftmost operator outside of brackets.  This is done last
  int op_index = find_op(token, start, end);

  Result *ans;
  if (op_index != -1) {
    // treat each operator
    if (token[op_index] == "+/"  || token[op_index] == "-/"  ||
	token[op_index] == "*/") {
      Result *r = eval(token, op_index+1, end);
      ans = r->slash_op(token[op_index][0]);
      delete r;
      return ans;
    } else if (token[op_index] == "+" || token[op_index] == "-" ||
	       token[op_index] == "*") {
      Result *right = eval(token, op_index+1, end);
      Result *left = eval(token, start, op_index);
      ans = left->elem_op(right, token[op_index][0]);
      delete left;
      delete right;
      return ans;
    } else if (token[op_index] == "drop") {
      Result *right = eval(token, op_index+1, end);
      Result *left = eval(token, start, op_index);
      Scalar *left2 = left->to_scalar();
      assert(left2->value >= 0);
      ans = right->drop(left2->value);
      delete left;
      delete right;
      delete left2;
      return ans;
    } else if (token[op_index] == "iota") {
      Result *right = eval(token, op_index+1, end);
      Scalar *right2 = right->to_scalar();
      ans = iota(right2->value);
      delete right;
      delete right2;
      return ans;
    } else if (token[op_index] == "rho") {
      Result *right = eval(token, op_index+1, end);
      Result *left = eval(token, start, op_index);
      int index = 0;
      ans = right->rho(left, index);
      delete right;
      delete left;
      return ans;
    } else if (token[op_index] == "=") {
      const string &name = token[op_index-1];
      Result *right = eval(token, op_index+1, end);
      delete vars[name];
      vars[name] = right;
      return vars[name]->clone();
    } else {
      cout << "dying with token = " << token[op_index] << " at index "
	   << op_index << endl;
      assert(false);
    }
  } else {
    // if there is no operator, must be a scalar, vector, or a variable name

    if (end - start > 1) {
      // a vector
      vector<Result *> out;
      for (int i = start; i < end; i++) {
	Result *temp = eval(token, i, i+1);
	out.push_back(temp->to_scalar());
	delete temp;
      }
      ans = new Vector(out);
      for (uint i = 0; i < out.size(); i++) {
	delete out[i];
      }
      return ans;
    }

    // either a scalar or a variable
    if (isdigit(token[start][0])) {
      return new Scalar(atoi(token[start].c_str()));
    } else {
      return vars[token[start]]->clone();
    }
  }

  return ans;
}

Result *eval(string line)
{
  bool to_erase = false;
  for (int i = line.size()-1; i >= 0; i--) {
    if (to_erase) {
      line.erase(i, 1);
      to_erase = false;
    } else {
      to_erase = line[i] == '/';
    }
  }

  istringstream iss(line);
  vector<string> token;
  string word;
  while (iss >> word) {
    token.push_back(word);
  }

  return eval(token, 0, token.size());
}

int main(void)
{
  int case_num = 1;
  string line;
  while (getline(cin, line) && line != "#") {
    cout << "Case " << case_num++ << ": " << line << endl;
    Result *result = eval(line);
    result->print();
    result->print_end();
    delete result;
  }

  for (map<string, Result *>::iterator it = vars.begin(); it != vars.end(); 
       ++it) {
    delete it->second;
  }

  return 0;
}
	
