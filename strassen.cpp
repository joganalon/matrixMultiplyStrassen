#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <vector>
using std::vector;

#include <stdexcept>
using std::invalid_argument;
using std::exception;

struct Matrix{
  int size;
  vector<double> data;

  //constructor
  Matrix(int size): size(size), data(size * size) {}

  //access element in row-major order
  double& operator()(int row, int column){
    return data[row * size + column];
  }

  //ditto (constant version)
  const double& operator()(int row, int column) const{
    return data[row * size + column];
  }
};

Matrix addMatrices(const Matrix& A, const Matrix&B){
  int n = A.size;
  Matrix sum(n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      sum(i, j) = A(i, j) + B(i, j);

  return sum;
}

Matrix subtractMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix difference(n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      difference(i, j) = A(i, j) - B(i, j);

  return difference;
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix product(n);

  //base case
  if(n == 1){
    product(0, 0) = A(0, 0) * B(0, 0);
    return product;
  }

  int newSize = n/2;
  
  //create submatrices
  Matrix A11(newSize), A12(newSize), A21(newSize), A22(newSize);
  Matrix B11(newSize), B12(newSize), B21(newSize), B22(newSize);

  //copy data to submatrices
  for(int i = 0; i < newSize; i++)
    for(int j = 0; j < newSize; j++){
      //A
      A11(i, j) = A(i, j);
      A12(i, j) = A(i, j + newSize);
      A21(i, j) = A(i + newSize, j);
      A22(i, j) = A(i + newSize, j + newSize);

      //B
      B11(i, j) = B(i, j);
      B12(i, j) = B(i, j + newSize);
      B21(i, j) = B(i + newSize, j);
      B22(i, j) = B(i + newSize, j + newSize);
    }
  
  //AHED
  //diagonal
  //Last CR
  //First CR
  
  Matrix S1 = multiplyMatrices(A11, subtractMatrices(B12, B22));
  Matrix S2 = multiplyMatrices(B22, addMatrices(A11, A12));
  Matrix S3 = multiplyMatrices(B11, addMatrices(A21, A22));
  Matrix S4 = multiplyMatrices(A22, subtractMatrices(B21, B11));
  Matrix S5 = multiplyMatrices(addMatrices(A11, A22), addMatrices(B11, B22));
  Matrix S6 = multiplyMatrices(subtractMatrices(A12, A22), addMatrices(B21, B22));
  Matrix S7 = multiplyMatrices(subtractMatrices(A11, A21), addMatrices(B11, B12));

  //calculate product matrix
  //s4 + s5 + s6 -s2
  Matrix C11 = subtractMatrices(addMatrices(addMatrices(S5, S6), S4), S2);
  //s1 + s2
  Matrix C12 = addMatrices(S1, S2);
  //s3 + s4
  Matrix C21 = addMatrices(S3, S4);
  //s1 - s3 + s5 - s7
  Matrix C22 = subtractMatrices(addMatrices(subtractMatrices(S1, S3), S5), S7);

  //fill product matrix
  for(int i = 0; i < newSize; i++)
    for(int j = 0; j < newSize; j++){
      product(i, j) = C11(i, j);
      product(i, j + newSize) = C12(i, j);
      product(i + newSize, j) = C21(i, j);
      product(i + newSize, j + newSize) = C22(i, j);
    }

  return product;
}

void printMatrix(const Matrix& M){
  for(int i = 0; i < M.size; i++){
    for(int j = 0; j < M.size; j++)
      cout << M(i, j)  << " ";
    cout << endl;
  }
}

void validateSize(int size){
  if(size <= 0 || (size & (size - 1) != 0))
      throw invalid_argument("size must be a power of 2 and greater than 0");
}

void populateMatrix(Matrix& M){
  for(int i = 0; i < M.size; i++)
    for(int j = 0; j < M.size; j++)
      cin >> M(i, j);
}

int main(){
  try{
    int size;
    
    cout << "enter size for square matrices: " << endl;
    cin >> size;
    validateSize(size);
    
    Matrix A(size), B(size);
    
    cout << "enter values for matrix A: " << endl;
    populateMatrix(A);
    
    cout << "enter values for matrix B: " << endl;
    populateMatrix(B);
    
    Matrix C(size);
    
    C = multiplyMatrices(A, B);
    
    cout << "product matrix: " << endl;
    printMatrix(C);
  } catch (const exception& e){
    cerr << "error: " << e.what() << endl;
    return 1;
  }
  
  return 0;
}
