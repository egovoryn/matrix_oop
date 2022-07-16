#include "matrix_oop.h"

void OMatrix::create_matrix() {
    _matrix = new double*[_rows];  // array of pointers
    for (auto i = 0; i < _rows; i++) {
        _matrix[i] = new double[_cols] {0};
    }
}

void OMatrix::delete_matrix() {
    for (auto i = 0; i < _rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

OMatrix::OMatrix() {
    _rows = 3;
    _cols = 3;
    create_matrix();
}

/* : <attribute_name>(value) syntax helps to automatically fill attributes with values */
OMatrix::OMatrix(int rows, int cols) : _rows(rows), _cols(cols) {
    if (_rows <= 0 || _cols <= 0) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        create_matrix();
    }
}

OMatrix::OMatrix(const OMatrix& other) : _rows(other._rows), _cols(other._cols) {
    create_matrix();
    *this = other;
}

OMatrix::OMatrix(OMatrix&& other)
: _rows(other._rows), _cols(other._cols), _matrix(other._matrix) {
    other._rows = other._cols = 0;
    other._matrix = nullptr;
}

OMatrix::~OMatrix() {
    if (_matrix) {
        delete_matrix();
    }
}

bool OMatrix::eq_matrix(const OMatrix& other) {
    // 1 – SUCCESS; 0 – FAIL
    bool flag = false;
    if (other._rows == _rows && other._cols == _cols) {
        flag = true;
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                if (fabs(_matrix[i][j] - other._matrix[i][j]) > 1e-7) {
                    flag = false;
                    BREAK(flag);
                }
            }
            BREAK(flag);
        }
    }
    return flag;
}

void OMatrix::sum_matrix(const OMatrix& other) {
    // C(i,j) = A(i,j) + B(i,j)
    if (_rows != other._rows || _cols != other._cols) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] + other._matrix[i][j];
            }
        }
    }
}

void OMatrix::sub_matrix(const OMatrix& other) {
    // C(i,j) = A(i,j) - B(i,j)
    if (_rows != other._rows || _cols != other._cols) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] - other._matrix[i][j];
            }
        }
    }
}

void OMatrix::mul_number(const double num) {
    // B = λ × A = λ × A(i,j)
    if (std::isnan(num) || std::isinf(num)) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                _matrix[i][j] = _matrix[i][j] * num;
            }
        }
    }
}

void OMatrix::mul_matrix(const OMatrix& other) {
    // C(i,j) = A(i,k) × B(k,j)
    if (_cols != other._rows) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        OMatrix temp(_rows, other._cols);
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < other._cols; j++) {
                for (auto k = 0; k < _cols; k++) {
                    temp._matrix[i][j] += _matrix[i][k] * other._matrix[k][j];
                }
            }
        }
        *this = temp;
    }
}

OMatrix OMatrix::transpose() {
    OMatrix temp(_cols, _rows);
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            temp._matrix[j][i] = _matrix[i][j];
        }
    }
    return temp;
}

OMatrix OMatrix::cut_matrix(int row, int column) {
    int offColumn = 0;
    int offRow = 0;
    int size = _rows;
    int colz = size - 1;
    OMatrix temp(colz, colz);
    for (auto i = 0; i < colz; i++) {
        if (i == row) offRow = 1;
        offColumn = 0;
        for (auto j = 0; j < colz; j++) {
            if (j == column) offColumn = 1;
            temp._matrix[i][j] = _matrix[i + offRow][j + offColumn];
        }
    }
    return temp;
}

double OMatrix::determinant() {
    double det = 0.0;
    if (_cols != _rows) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        int size = _rows;
        if (size == 1) {
            det = _matrix[0][0];
        } else if (size == 2) {
            det = _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
        } else {
            int degree = 1;
            for (auto j = 0; j < size; j++) {
                OMatrix temp = cut_matrix(0, j);
                // (-1)^(1+j) * matrix[0][j] * minor_j
                det = det + degree * _matrix[0][j] * temp.determinant();
                degree *= -1;
            }
        }
    }
    return det;
}

OMatrix OMatrix::minor_matrix() {
    OMatrix minor(_rows, _cols);
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            OMatrix tmp_matrix = cut_matrix(i, j);
            minor._matrix[i][j] = tmp_matrix.determinant();
        }
    }
    return minor;
}

void OMatrix::fill_matrix() {
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            _matrix[i][j] = i + j;
        }
    }
}

OMatrix OMatrix::calc_complements() {
    // M. = (-1)^(i+j) * minor_ij
    OMatrix temp = minor_matrix();
    if (_cols != _rows) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        int size = _rows;
        for (auto i = 0; i < size; i++) {
            for (auto j = 0; j < size; j++) {
                temp._matrix[i][j] *= pow(-1.0, i + j);
            }
        }
    }
    return temp;
}

OMatrix OMatrix::inverse_matrix() {
    double det = determinant();
    OMatrix transp(_rows, _cols);
    if (_cols != _rows || !det) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    } else {
        OMatrix comp = calc_complements();
        transp = comp.transpose();
        transp.mul_number(1.0 / det);
    }
    return transp;
}

OMatrix& OMatrix::operator= (const OMatrix& other) {
    if (this != &other) {
        delete_matrix();
        _rows = other._rows;
        _cols = other._cols;
        create_matrix();
    }
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            _matrix[i][j] = other._matrix[i][j];
        }
    }
    return *this;
}

bool OMatrix::operator== (const OMatrix& other) {
    bool flag = true;
    if (_rows == other._rows && _cols == other._cols) {
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                if (_matrix[i][j] != other._matrix[i][j]) flag = false;
                BREAK(flag);
            }
            BREAK(flag);
        }
    } else {
        flag = false;
    }
    return flag;
}

OMatrix& OMatrix::operator+= (const OMatrix& other) {
    return *this = *this + other;
}

OMatrix OMatrix::operator+(const OMatrix& other) {
    OMatrix res = *this;
    res.sum_matrix(other);
    return res;
}

OMatrix& OMatrix::operator-= (const OMatrix& other) {
    return *this = *this - other;
}

OMatrix OMatrix::operator- (const OMatrix& other) {
    OMatrix res = *this;
    res.sub_matrix(other);
    return res;
}

OMatrix OMatrix::operator* (const OMatrix& other) {
    OMatrix res = *this;
    res.mul_matrix(other);
    return res;
}

OMatrix OMatrix::operator* (const double value) {
    OMatrix res = *this;
    res.mul_number(value);
    return res;
}

OMatrix& OMatrix::operator*= (const OMatrix& other) {
    return *this = *this * other;
}

OMatrix& OMatrix::operator*= (const double value) {
    return *this = *this * value;
}

// index operator overload
double& OMatrix::operator()(int row, int col) {
    if (row >= _rows || col >= _cols || row < 0 || col < 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    } else {
        return _matrix[row][col];
    }
}

int OMatrix::getCols() {
    return _cols;
}

int OMatrix::getRows() {
    return _rows;
}

void OMatrix::setCols(int value) {
    if (value <= 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    } else {
        OMatrix tmp(_rows, value);
        if (value < _cols) {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < value; j++) {
                    tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        } else {
            for (auto i = 0; i < _rows; i++) {
                for (auto j = 0; j < value; j++) {
                    if (j >= _cols)
                        tmp._matrix[i][j] = 0;
                    else
                        tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        }
        delete_matrix();
        _cols = value;
        create_matrix();
        *this = tmp;
    }
}

void OMatrix::setRows(int value) {
    if (value <= 0) {
        throw std::out_of_range("Incorrect input, index is out of range");
    } else {
        OMatrix tmp(value, _cols);
        if (value < _rows) {
            for (auto i = 0; i < value; i++) {
                for (auto j = 0; j < _cols; j++) {
                    tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        } else {
            for (auto i = 0; i < value; i++) {
                for (auto j = 0; j < _cols; j++) {
                    if (i >= _rows)
                        tmp._matrix[i][j] = 0;
                    else
                        tmp._matrix[i][j] = _matrix[i][j];
                }
            }
        }
        delete_matrix();
        _rows = value;
        create_matrix();
        *this = tmp;
    }
}

void OMatrix::print_matrix() {
    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            std::cout << _matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
