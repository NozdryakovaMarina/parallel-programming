#include <iostream>
#include <fstream>
#include <vector>
#include <random>

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


int main() {
	string fileA;
	int rowsA, colsA;
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
	return 0;
}