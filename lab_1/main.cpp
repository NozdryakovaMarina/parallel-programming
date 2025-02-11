#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;


void saveMatrixToFile(const string& filename, vector<vector<int>>& matrix) {
	ofstream out("/paralProg/lab_1/" + filename); 

	if (!out.is_open()) {
		throw runtime_error("Couldn't open the file for writing: " + filename);
	}
	else
	{
		for (int i = 0; i < matrix.size(); ++i) {
			for (int j = 0; j < matrix[0].size(); ++j) {
				out << matrix[i][j] << " ";
			}
			out << endl;
		}
		out.close();
		cout << "Successfully! Matrix is created and written to a file " << filename << endl;
	}
}

vector<vector<int>> createMatrix(int rows, int cols, int minValue, int maxValue) {
	if (rows <= 0 || cols <= 0) {
		throw runtime_error("Size of the matrix must be positive");
	}

	vector<vector<int>> matrix(rows, vector<int>(cols));
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<> distrib(minValue, maxValue); 

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			matrix[i][j] = distrib(generator);
		}
	}

	return matrix;
}


void createMatrixFile(const string& filename, int rows, int cols, int minValue, int maxValue) {
	vector<vector<int>> matrix = createMatrix(rows, cols, minValue, maxValue);
	saveMatrixToFile(filename, matrix);
}

vector<vector<int>> multiplyMatrix(vector<vector<int>> matrixA, vector<vector<int>> matrixB) {
	if (matrixA.empty() || matrixB.empty()) {
		throw runtime_error("Matrices must be filled in");
	}
	int rowsA = matrixA.size();
	int colsA = matrixA[0].size();
	int rowsB = matrixB.size();
	int colsB = matrixB[0].size();

	if (colsA != rowsB) {
		throw runtime_error("It is impossible to multiply matrices: incompatible sizes");
	}

	vector<vector<int>> matrixxResult(rowsA, vector<int>(colsB));

	for (int i = 0; i < rowsA; ++i) {
		for (int j = 0; j < colsB; ++j) {
			for (int k = 0; k < colsA; ++k) {
				matrixxResult[i][j] += matrixA[i][k] * matrixB[k][j];
			}
		}
	}

	return matrixxResult;
}

vector<vector<int>> loadMatrixFromFile(const string& filename, int rows, int cols) {
	ifstream input("/paralProg/lab_1/" + filename);


	if (!input.is_open()) {
		throw runtime_error("Couldn't open the file for writing: " + filename);
	}

	vector<vector<int>> matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			input >> matrix[i][j];
		}
	}

	input.close();
	return matrix;
}

void writeResult(string filename, vector<vector<int>>& matrixResult, int rows, int cols, clock_t end, clock_t start) { 

	ofstream data("/paralProg/lab_1/" + filename);
	if (!data.is_open()) {
		throw runtime_error("Couldn't open the file for writing: " + filename);
		return;
	}

	ofstream result("/paralProg/lab_1/result.txt", ios::app);
	if (!result.is_open()) {
		throw runtime_error("Couldn't open the file result.txt");
		data.close();
		return;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			data << matrixResult[i][j] << " ";
		}
		data << endl;
	}
	data.close(); 

	result << "Size matrix: " << rows << "x" << cols << " | " << "Lead time: " << (double)(end - start) / (double)(CLOCKS_PER_SEC) << endl;
	result.close(); 
}


int main() {
	srand(time(nullptr));
	string fileA, fileB, fileResult;
	int rowsA, colsA, rowsB, colsB;
	int minValue, maxValue;

	cout << "Enter the file name for the first matrix:";
	cin >> fileA;

	cout << "Enter the number of rows and columns for the first matrix:";
	cin >> rowsA >> colsA;

	cout << "Enter the minimum value for the matrix elements: ";
	cin >> minValue;
	cout << "Enter the maximum value for the matrix elements: ";
	cin >> maxValue;

	createMatrixFile(fileA, rowsA, colsA, minValue, maxValue);

	cout << "Enter the file name for the second matrix:";
	cin >> fileB;

	cout << "Enter the number of rows and columns for the second matrix:";
	cin >> rowsB >> colsB;

	createMatrixFile(fileB, rowsB, colsB, minValue, maxValue);

	cout << "Enter the file name to save the result:";
	cin >> fileResult; 

	vector<vector<int>> matrixA, matrixB, resultMatrix;

	matrixA = loadMatrixFromFile(fileA, rowsA, colsA);
	matrixB = loadMatrixFromFile(fileB, rowsB, colsB);
	 
	clock_t start, end;
	start = clock();

	resultMatrix = multiplyMatrix(matrixA, matrixB);
	
	end = clock();

	writeResult(fileResult, resultMatrix, resultMatrix.size(), resultMatrix[0].size(), end, start);

	return 0;
}