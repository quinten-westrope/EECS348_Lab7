#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size]{};
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this == &other) {
            return *this;
        }

        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        matrix_size = other.matrix_size;

        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }

    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }

    Matrix(const Matrix& other) : matrix_size(other.matrix_size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }
    }

    //overloaded + operator - matrix addition
    friend Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2);

    //overloaded * operator - matrix multiplication
    friend Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2);
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    // TODO: Read matrix data from the file
    //    Make sure to handle potential errors and invalid input
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("Could not open file.");
    }

    int size;
    file >> size;

    matrix_1 = Matrix(size);
    matrix_2 = Matrix(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_1.matrix_data[i][j];
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_2.matrix_data[i][j];
        }
    }
}

void print_matrix(const Matrix& matrix) {
    // TODO: Print the matrix to the console
    for (int i = 0; i < matrix.matrix_size; ++i) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    // TODO: Print both matrices to the console
    cout << "Matrix 1:" << endl;
    print_matrix(matrix_1);
    cout << "\nMatrix 2:" << endl;
    print_matrix(matrix_2);
}

Matrix add_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    // TODO: Implement matrix addition
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < result.matrix_size; ++i) {
        for (int j = 0; j < result.matrix_size; ++j) {
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

Matrix multiply_matrices(const Matrix& matrix_1, const Matrix& matrix_2) {
    // TODO: Implement matrix multiplication
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < result.matrix_size; ++i) {
        for (int j = 0; j < result.matrix_size; ++j) {
            result.matrix_data[i][j] = 0;
            for (int k = 0; k < result.matrix_size; ++k) {
                result.matrix_data[i][j] += matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j];
            }
        }
    }
    return result;
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
    return add_matrices(matrix_1, matrix_2);
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2) {
    return multiply_matrices(matrix_1, matrix_2);
}


void get_diagonal_sum(const Matrix& matrix) {
    double main_diagonal_sum = 0, secondary_diagonal_sum = 0;
    int size = matrix.matrix_size;

    for (int i = 0; i < size; ++i) {
        //sum of main diagonal top left to bottom right
        main_diagonal_sum += matrix.matrix_data[i][i];

        //sum of secondary diagonal top right to bottom left
        secondary_diagonal_sum += matrix.matrix_data[i][size - i - 1];
    }

    //printing sum of main and diagonal elements from matrix 1
    cout << "Total sum of diagonals: " << main_diagonal_sum + secondary_diagonal_sum << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
     // TODO: Swap the rows 'row1' and 'row2' in the matrix
    //    Handle invalid row indices
    if (row1 < 0 || row2 < 0 || row1 >= matrix.matrix_size || row2 >= matrix.matrix_size) {
        cout << "Invalid row indices." << endl;
        return;
    }
    for (int j = 0; j < matrix.matrix_size; ++j) {
        swap(matrix.matrix_data[row1][j], matrix.matrix_data[row2][j]);
    }
    print_matrix(matrix);
}

int main(int argc, char* argv[]) {
    //displaying all of the outputs based on the given input in matrix.txt
    
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << endl;
    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);
    cout << endl;

    cout << "add_matrices result:" << endl;
    Matrix add_result_1 = matrix_1 + matrix_2;
    print_matrix(add_result_1);
    cout << endl;

    cout << "multiply_matrices result:" << endl;
    Matrix multiply_result_1 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);
    cout << endl;

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);
    cout << endl;

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    cout << endl;

    return 0;
}