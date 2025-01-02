#include <iostream>
#include <cassert>

template<class T>
struct Triple {
    int row;
    int col;
    T value;
    Triple<T>& operator=(const Triple<T>& other) {
        row = other.row;
        col = other.col;
        value = other.value;
        return *this;
    }
};

template<class Tp>
class Matrix {
public:
    Matrix(int r, int c) : cols(c), rows(r), size(0), elmArr(nullptr) {
        elmArr = new Triple<Tp>[r * c + 1];
    }

    ~Matrix() {
        delete []elmArr;
    }

    void insert(int r, int c, Tp v) {
        if (v != Tp()) {
            Triple<Tp> t;
            t.col = c;
            t.row = r;
            t.value = v;
            elmArr[size++] = t;
        }
    }
    
    static void multiply(const Matrix& a, const Matrix& b, Matrix& res) {
        if (a.cols != b.rows)
            assert(0);

        int temp[2001][2001] = {0};
        for (int i = 0; i < a.size; i++) {
            for (int j = 0; j < b.size; j++) {
                if (a.elmArr[i].col == b.elmArr[j].row) {
                    temp[a.elmArr[i].row][b.elmArr[j].col] += a.elmArr[i].value * b.elmArr[j].value;
                }
            }
        }

        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < b.cols; j++) {
                if (temp[i][j] != 0) {
                    res.insert(i, j, temp[i][j]);
                }
            }
        }
    }

    static void multiply_and_display(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows)
            assert(0);

        int temp[2001][2001] = {0};
        for (int i = 0; i < a.size; i++) {
            for (int j = 0; j < b.size; j++) {
                if (a.elmArr[i].col == b.elmArr[j].row) {
                    temp[a.elmArr[i].row][b.elmArr[j].col] += a.elmArr[i].value * b.elmArr[j].value;
                }
            }
        }

        for (int i = 0; i < a.rows; i++) {
            for (int j = 0; j < b.cols; j++) {
                std::cout << temp[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void display() {
        int mark = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (mark < size && i == elmArr[mark].row && i == elmArr[mark].col) {
                    std::cout << elmArr[mark].value;
                    mark++;
                } else {
                    std::cout << "0";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix& operator=(const Matrix& other) {
        delete []elmArr;
        elmArr = new Triple<Tp>[other.rows * other.cols + 5];
        for (int i = 0; i < other.size; i++) {
            elmArr[i] = other.elmArr[i];
        }
        size = other.size;
        rows = other.rows;
        cols = other.cols;
        return *this;
    }

private:
    Triple<Tp>* elmArr;
    int cols, rows, size;
};

int main() {
    int n, t, m;
    std::cin >> n >> t >> m;
    Matrix<int>a(n, t), b(t, m), c(n, m);
    int tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < t; j++) {
            std::cin >> tmp;
            if (tmp != 0)
                a.insert(i, j, tmp);
        }
    }
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> tmp;
            if (tmp != 0)
                b.insert(i, j, tmp);
        }
    }
    // Matrix<int>::multiply(a, b, c);
    // c.display();
    Matrix<int>::multiply_and_display(a, b);
    return 0;
}