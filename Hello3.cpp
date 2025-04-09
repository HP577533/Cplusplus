#include <iostream>
#include <vector>

using namespace std;

// Function to display a matrix
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    int rows = mat1.size();
    int cols = mat1[0].size();
    vector<vector<int>> result(rows, vector<int>(cols));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    return result;
}

int main() {
    // Example matrices
    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    cout << "Matrix 1:" << endl;
    displayMatrix(matrix1);

    cout << "Matrix 2:" << endl;
    displayMatrix(matrix2);

    // Adding matrices
    vector<vector<int>> result = addMatrices(matrix1, matrix2);

    cout << "Resultant Matrix after Addition:" << endl;
    displayMatrix(result);

    return 0;
}