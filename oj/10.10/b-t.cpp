#include <iostream>
#include <utility>
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

    Matrix& T() {
        // 转置
        for (int i = 0; i < size; i++) {
            std::swap(elmArr[i].col, elmArr[i].row);
        }
        return *this;
    }

    static void multiply(const Matrix& a, const Matrix& b, Matrix& res) {
        if (a.cols != b.rows)
            assert(0);
        for (int i = 0; i < a.size; i++) {
            const Triple<Tp>& ai = a.elmArr[i];
            for (int j = 0; j < b.size; j++) {
                const Triple<Tp>& bj = b.elmArr[j];
                if (ai.col == bj.row) {
                    int row = ai.row;
                    int col = bj.col;
                    Tp value = ai.value * bj.value;

                    bool found = false;
                    for (int k = 0; k < res.size; k++) {
                        if (res.elmArr[k].row == row && res.elmArr[k].col == col) {
                            res.elmArr[k].value += value;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        res.insert(row, col, value);
                    }
                }
            }
        }
    }

    bool exists(int r, int c, Triple<Tp>& tmp) {
        for (int i = 0; i < size; i++) {
            if (elmArr[i].col == c && elmArr[i].row == r) {
                tmp = elmArr[i];
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                Triple<Tp> tmp;
                if (exists(i, j, tmp)) {
                    std::cout << tmp.value;
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
    Matrix<int>::multiply(a, b, c);
    c.display();
    return 0;
}