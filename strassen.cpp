#include <iostream>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#include <vector>
using std::vector;

struct Matrix{
  int size;
  vector<vector<double>> data;

  //constructor to initialise matrix with given size
  Matrix(int n): size(n), data(n, vector<double>(n)){}
};

Matrix addMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix sum(n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      sum.data[i][j] = A.data[i][j] + B.data[i][j];
    }
  }

  return sum;
}

Matrix subtractMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix difference(n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      difference.data[i][j] = A.data[i][j] - B.data[i][j];
    }
  }

  return difference;
}

Matrix  naiveMultiplyMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix product(n);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
	product.data[i][j] += A.data[i][k] * B.data[k][j];
      }
    }
  }

  return product;
}

Matrix multiplyMatrices(const Matrix& A, const Matrix& B){
  int n = A.size;
  Matrix product(n);

  //base case: if the matrices are 1 by 1
  if(n == 1){
    product.data[0][0] = A.data[0][0] * B.data[0][0];
    return product;
  }

  //split the matrices into quadrants
  int newSize = n/2;

  //create submatrices of A and B
  //using temporary storages
  Matrix A11(newSize), A12(newSize), A21(newSize), A22(newSize);
  Matrix B11(newSize), B12(newSize), B21(newSize), B22(newSize);

  //divide A into quadrants
  for(int i = 0; i < newSize; i++){
    for(int j = 0; j < newSize; j++){
      A11.data[i][j] = A.data[i][j];
      A12.data[i][j] = A.data[i][j + newSize];
      A21.data[i][j] = A.data[i + newSize][j];
      A22.data[i][j] = A.data[i + newSize][j + newSize];
      
      //divide B into quadrants
      B11.data[i][j] = B.data[i][j];
      B12.data[i][j] = B.data[i][j + newSize];
      B21.data[i][j] = B.data[i + newSize][j];
      B22.data[i][j] = B.data[i + newSize][j + newSize];
    }
  }

  //calculate intermediate matrices
  Matrix M1 = multiplyMatrices(addMatrices(A11, A22), addMatrices(B11, B22));
  Matrix M2 = multiplyMatrices(addMatrices(A21, A22), B11);
  Matrix M3 = multiplyMatrices(A11, subtractMatrices(B12, B22));
  Matrix M4 = multiplyMatrices(A22, subtractMatrices(B21, B11));
  Matrix M5 = multiplyMatrices(addMatrices(A11, A12), B22);
  Matrix M6 = multiplyMatrices(subtractMatrices(A12, A22), addMatrices(B11, B12));
  Matrix M7 = multiplyMatrices(subtractMatrices(A12, A22), addMatrices(B21, B22));

  //calculate product matrix
  Matrix C11 = addMatrices(subtractMatrices(addMatrices(M1, M4), M5), M7);
  Matrix C12 = addMatrices(M3, M5);
  Matrix C21 = addMatrices(M2, M4);
  Matrix C22 = addMatrices(subtractMatrices(addMatrices(M1, M3), M2), M6);

  //fill product matrix
  for(int i = 0; i < newSize; i++){
    for(int j = 0; j < newSize; j++){
      product.data[i][j] = C11.data[i][j];
      product.data[i][j + newSize] = C12.data[i][j];
      product.data[i + newSize][j] = C21.data[i][j];
      product.data[i + newSize][j + newSize] = C22.data[i][j];
    }
  }

  return product;
}

void printMatrix(const Matrix& m){
  for(int i = 0; i < m.size; i++){
    for(int j = 0; j < m.size; j++){
      cout << m.data[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
  int size;
  cout << "enter size of matrices: ";
  cin >> size;

  //create matrices
  Matrix A(size), B(size);

  //input matrices
  cout << "enter elements of matrix a: " << endl;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cin >> A.data[i][j];
    }
  }
  
  cout << "enter elements of matrix b: " << endl;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      cin >> B.data[i][j];
    }
  }

  //multiply matrices using divide and conquer
  Matrix result = multiplyMatrices(A, B);

  //print the result
  cout << "Resultant matrix: " << endl;
  printMatrix(result);

  return 0;
}
