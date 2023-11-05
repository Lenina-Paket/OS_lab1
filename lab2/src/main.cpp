#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <random>

using namespace std;

//Функция вывода матрицы
void PrintMatrix(vector<vector<double>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Функция реализации метода Гаусса на части матрицы
void GaussEliminationPart(vector<vector<double>>& matrix, int start_row, int end_row) {
    int cols = matrix[0].size();

    for (int i = start_row; i < end_row; i++) {
        double max_elem = matrix[i][i];
        int max_row = i;

        for (int j = i + 1; j < matrix.size(); j++) {
            if (abs(matrix[j][i]) > abs(max_elem)) {
                max_elem = matrix[j][i];
                max_row = j;
            }
        }

        if (max_row > i) {
            swap(matrix[i], matrix[max_row]);
        }

        for (int j = i + 1; j < matrix.size(); j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < cols; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

// Функция реализации метода Гаусса с использованием потоков
void GaussEliminationThreaded(vector<vector<double>> &matrix, int num_threads) {
    int rows = matrix.size(); 
    int part_size = rows / num_threads; //размер части матрицы, для каждого потока

    vector<thread> threads;
    int start_row = 0;
    int end_row = 0;

    for (int i = 0; i < num_threads - 1; i++) {
        end_row = start_row + part_size;
        threads.push_back(thread(GaussEliminationPart, ref(matrix), start_row, end_row)); 
        start_row = end_row;
    }

    end_row = rows;
    threads.push_back(thread(GaussEliminationPart, ref(matrix), start_row, end_row));

    for (int i = 0; i < num_threads; i++) {
        threads[i].join(); //метод join() для каждого потока, чтобы дождаться их завершения
    }
}

// Функция обратной замены
vector<double> backSubstitution(vector<vector<double>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<double> solution(rows);
    for (int i = rows - 1; i >= 0; i--) {
        solution[i] = matrix[i][cols - 1];
        for (int j = i + 1; j < rows; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }

    return solution;
}


// Функция решения СЛАУ с использованием потоков
vector<vector<double>> SolveSystemThreaded(vector<vector<double>> matrix, int num_threads) {
    GaussEliminationThreaded(matrix, num_threads);
    return matrix;
}

int main() {
    int n, m;
    cout << "Enter size of matrix" << endl;
    cin >> n >> m;

    int num_threads;
    cout << "Enter number of threads (from 1 to threads)" << endl;
    cin >> num_threads;

    vector<vector<double>> matrix(n, vector<double>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            static random_device rd;
            static mt19937 gen(rd());
            uniform_real_distribution<double> dis(0.0, 0.9);
            matrix[i][j] = round(dis(gen)*10)/10;
        }
    }

    vector<vector<double>> matrix_solution;
    for (int i = 1; i <= num_threads; i++) {
        auto start = chrono::steady_clock::now();
        matrix_solution = SolveSystemThreaded(matrix, i);
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout << i << ' ' << chrono::duration <double, milli> (diff).count() << " ms" << endl;
    }
    vector<double> solution = backSubstitution(matrix_solution);

    /*cout << "Solution to the linear system:" << endl;
    for (int i = 0; i < solution.size(); i++) {
        cout << "x" << i + 1 << " = " << solution[i] << endl;
    }*/

    //printMatrix(matrix_solution);
    return 0;
}