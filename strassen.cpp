#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

#include <vector>
using std::vector;

struct Matrix{
  vector<vector<double>> data;

  //constructor
  Matrix(int size): data(size, vector<double>(size)) {}
};

Matrix addMatrices(const Matrix& A, const Matrix&B){
  int n = A.data.size();
  Matrix sum(n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      sum.data[i][j] = A.data[i][j] + B.data[i][j];

  return sum;
}

Matrix subtractMatrices(const Matrix& A, const Matrix& B){
  int n = A.data.size();
  Matrix difference(n);

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      difference.data[i][j] = A.data[i][j] - B.data[i][j];

  return difference;
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B){
  int n = A.data.size();
  Matrix product(n);

  //base case
  if(n == 1){
    product.data[0][0] = A.data[0][0] * B.data[0][0];
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
      A11.data[i][j] = A.data[i][j];
      A12.data[i][j] = A.data[i][j + newSize];
      A21.data[i][j] = A.data[i + newSize][j];
      A22.data[i][j] = A.data[i + newSize][j + newSize];

      //B
      B11.data[i][j] = B.data[i][j];
      B12.data[i][j] = B.data[i][j + newSize];
      B21.data[i][j] = B.data[i + newSize][j];
      B22.data[i][j] = B.data[i + newSize][j + newSize];
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
      product.data[i][j] = C11.data[i][j];
      product.data[i][j + newSize] = C12.data[i][j];
      product.data[i + newSize][j] = C21.data[i][j];
      product.data[i + newSize][j + newSize] = C22.data[i][j];
    }

  return product;
}

void printMatrix(const Matrix& M){
  for(auto& row : M.data){
    for(auto& data : row)
      cout << data << " ";
    cout << endl;
  }
}

void validateSize(int size){
  if(size % 2 != 0){
    cerr << "size must be a multiple of 2" << endl;
    exit(1);
  }
}

void populateMatrix(Matrix& M){
  for(auto& row : M.data)
    for(auto& data :row)
      cin >> data;
}

int main(){
  int size;

  cout << "enter size: " << endl;
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
  
  return 0;
}
