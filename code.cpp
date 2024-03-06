#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

void populateMatrix(double& matrix[][], int row, int column){
	fo(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			cin >> matrix[i][j];
		}
	}
}

int checkDimension(int row, int col){
	if(column > 6 || row > 6){
		cerr << "dimension should not greater than 6 by 6" << endl;
		return 1;
	}
}

int checkCompatibility(int column1, int row2){
	if(column1 != row2){
		cerr << "first column must be equal to second row" << endl
		return 1;
	}
}

void strassenMultily(double& matrix1[][], double& matrix2[][], double& matrix3[][], int row1, int column1, int row2, int column2/* int row1const, int column2const*/){
/*	//divide the matrices into n/2
	int row1a = row1/2;
	int colummn1a = column1/2;
	
	double matrix1a[row1a][column1a];
	
	int row2a = row2/2;
	int column2a = column2/2;
	
	double matrix2a[row2a][column2a];
	
	//multiply draft, we make this recursive 
	double a = matrix1[0][0] * matrix2[0][0];
	double b = matrix1[0][1] * matrix2[1][0];
	double c = matrix1[0][0] * matrix2[0][1];
	double d = matrix1[0][1] * matrix2[1][1];
	double e = matrix1[1][0] * matrix2[0][0];
	double f = matrix1[1][1] * matrix2[1][0];
	double g = matrix1[1][1] * matrix2[0][1];
	double h = matrix1[1][1] * matrix2[1][1];
	
	//adding
	for(int i = 0; i < row1; i++){
		for(int j = 0; j < column2; j++){
			matrix3[i][j] = a + b
		}
	} */
/*	int row1const = row1
	int column2const = column2;
	
	int row1a = row1/2;
	int colummn1a = column1/2;
	
	double matrix1a[row1a][column1a];
	
	int row2a = row2/2;
	int column2a = column2/2;
	
	double matrix2a[row2a][column2a];
	
	strassenMultiply(matrix1a, matrix2a, row1a, column2a, row2a, column2a, row1const, column2const);
	
	int numMults = 8;
	
	double arrayproduct[numMults];
	
	for(int i = 0; i < numMults ; i++){
			arrayproduct[i] = matrix1a[0][0] * matrix2a[0][0];
	} forgot implementation*/ 
}






int main(){
	int row1, column2;
	int row2, column2
	cout << "enter dimension for the matrix1 row first then column" << endl;
	cin >> row >> column;
	//insert dimension check
	checkDimension(row1, column1);
	
	double matrix1[row1][column1];
	populateMatrix(matrix1[][], row1, column2);

	cout << "enter dimension for the matrix2 row first then column" << endl;
	cin >> row2 >> column2;	
	checkDimension(row2, column2);
	//inssert dimension check
	
	//insert compatibility check
	checkCompatibility(column1, row2);
	
	double matrix2[][];
	populateMatrix(matrix2[][], row2, column2);
	
	//product matrix
	double matrix3[row1][column2];
	populateMatrix(matrix3[][]), row1, column2;
	
	strassenMultiply(matrix1[][], matrix2[][], matrix3[][], row1, column1, row2, column2, row1, column2);	
	
	return 0;
}

