#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <mpi.h>

using namespace std;

void saveMatrixToFile(const string& filename, vector<vector<int>>& matrix) {
    ofstream out("/paralProg/lab_3/" + filename);

    if (!out.is_open()) {
        throw runtime_error("Couldn't open the file for writing: " + filename);
    }
    else {
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

vector<vector<int>> multiplyMatrixMPI(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB,
    int rowsA, int colsA, int colsB, int rank, int size) {

    // Проверка ошибок (как в MatrixMultiplicator)
    int error_code = 0;
    if (rank == 0) {
        if (matrixA.empty() || matrixB.empty()) {
            error_code = 1;
        }
        else if (colsA != matrixB.size()) {
            error_code = 2;
        }
    }
    MPI_Bcast(&error_code, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (error_code != 0) return {};

    // Распределение матрицы B (как в MatrixMultiplicator)
    for (int i = 0; i < matrixB.size(); ++i) {
        MPI_Bcast(matrixB[i].data(), colsB, MPI_INT, 0, MPI_COMM_WORLD);
    }

    // Распределение строк матрицы A с использованием Scatterv (как в MatrixMultiplicator)
    vector<vector<int>> localA;
    if (rank == 0) {
        vector<int> counts(size), displs(size);
        int rows_per_process = rowsA / size;
        int remainder = rowsA % size;

        // Подготовка буфера для отправки
        vector<int> send_buffer;
        send_buffer.reserve(rowsA * colsA);
        for (const auto& row : matrixA) {
            send_buffer.insert(send_buffer.end(), row.begin(), row.end());
        }

        // Расчет counts и displs
        for (int i = 0; i < size; ++i) {
            counts[i] = (rows_per_process + (i < remainder ? 1 : 0)) * colsA;
            displs[i] = (i == 0) ? 0 : displs[i - 1] + counts[i - 1];
        }

        // Прием своей части данных
        vector<int> recv_buffer(counts[0]);
        MPI_Scatterv(send_buffer.data(), counts.data(), displs.data(), MPI_INT,
            recv_buffer.data(), counts[0], MPI_INT, 0, MPI_COMM_WORLD);

        // Преобразование буфера в localA
        int my_rows = counts[0] / colsA;
        localA.resize(my_rows, vector<int>(colsA));
        for (int i = 0; i < my_rows; ++i) {
            copy(recv_buffer.begin() + i * colsA, recv_buffer.begin() + (i + 1) * colsA, localA[i].begin());
        }
    }
    else {
        int rows_per_process = rowsA / size;
        int remainder = rowsA % size;
        int my_rows = rows_per_process + (rank < remainder ? 1 : 0);
        int my_count = my_rows * colsA;

        vector<int> recv_buffer(my_count);
        MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT,
            recv_buffer.data(), my_count, MPI_INT, 0, MPI_COMM_WORLD);

        localA.resize(my_rows, vector<int>(colsA));
        for (int i = 0; i < my_rows; ++i) {
            copy(recv_buffer.begin() + i * colsA, recv_buffer.begin() + (i + 1) * colsA, localA[i].begin());
        }
    }

    // Локальное умножение (оптимизированный вариант)
    vector<vector<int>> local_result(localA.size(), vector<int>(colsB, 0));
    for (size_t i = 0; i < localA.size(); ++i) {
        for (int k = 0; k < matrixB.size(); ++k) {
            int temp = localA[i][k];
            for (int j = 0; j < colsB; ++j) {
                local_result[i][j] += temp * matrixB[k][j];
            }
        }
    }

    // Сбор результатов (как в MatrixMultiplicator)
    vector<vector<int>> result;
    if (rank == 0) {
        result.resize(rowsA, vector<int>(colsB));
    }

    // Подготовка буфера для отправки
    vector<int> send_buffer;
    send_buffer.reserve(local_result.size() * colsB);
    for (const auto& row : local_result) {
        send_buffer.insert(send_buffer.end(), row.begin(), row.end());
    }

    if (rank == 0) {
        vector<int> counts(size), displs(size);
        int rows_per_process = rowsA / size;
        int remainder = rowsA % size;

        for (int i = 0; i < size; ++i) {
            counts[i] = (rows_per_process + (i < remainder ? 1 : 0)) * colsB;
            displs[i] = (i == 0) ? 0 : displs[i - 1] + counts[i - 1];
        }

        vector<int> recv_buffer(rowsA * colsB);
        MPI_Gatherv(send_buffer.data(), send_buffer.size(), MPI_INT,
            recv_buffer.data(), counts.data(), displs.data(), MPI_INT,
            0, MPI_COMM_WORLD);

        if (rank == 0) {
            for (int i = 0; i < rowsA; ++i) {
                copy(recv_buffer.begin() + i * colsB, recv_buffer.begin() + (i + 1) * colsB, result[i].begin());
            }
        }
    }
    else {
        MPI_Gatherv(send_buffer.data(), send_buffer.size(), MPI_INT,
            nullptr, nullptr, nullptr, MPI_INT,
            0, MPI_COMM_WORLD);
    }

    return result;
}

vector<vector<int>> loadMatrixFromFile(const string& filename, int rows, int cols) {
    ifstream input("/paralProg/lab_3/" + filename);

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

void writeResult(string filename, vector<vector<int>>& matrixResult, int rows, int cols, double averageTime) {
    ofstream data("/paralProg/lab_3/" + filename);
    if (!data.is_open()) {
        throw runtime_error("Couldn't open the file for writing: " + filename);
        return;
    }

    ofstream result("/paralProg/lab_3/result0.txt", ios::app);
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

    result << "Size matrix: " << rows << "x" << cols << " | " << "Average lead time: " << averageTime << " seconds" << endl;
    result.close();
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    string fileA, fileB, fileResult;
    int rowsA, colsA, rowsB, colsB;
    int minValue, maxValue;
    vector<vector<int>> matrixA, matrixB, resultMatrix;
    double totalTime = 0.0;
    const int numExperiments = 10;

    if (rank == 0) {
        srand(time(nullptr));
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
    }

    MPI_Bcast(&rowsA, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colsA, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&rowsB, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&colsB, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        matrixA = loadMatrixFromFile(fileA, rowsA, colsA);
        matrixB = loadMatrixFromFile(fileB, rowsB, colsB);
    }
    else {
        matrixB.resize(rowsB, vector<int>(colsB));
    }

    for (int i = 0; i < numExperiments; ++i) {
        MPI_Barrier(MPI_COMM_WORLD);
        double start_time = MPI_Wtime();

        resultMatrix = multiplyMatrixMPI(matrixA, matrixB, rowsA, colsA, colsB, rank, size);

        MPI_Barrier(MPI_COMM_WORLD);
        double end_time = MPI_Wtime();

        if (rank == 0) {
            totalTime += (end_time - start_time);
        }
    }

    if (rank == 0) {
        double averageTime = totalTime / numExperiments;
        writeResult(fileResult, resultMatrix, rowsA, colsB, averageTime);
        cout << "Matrix multiplication completed in average " << averageTime << " seconds" << endl;
    }

    MPI_Finalize();
    return 0;
}