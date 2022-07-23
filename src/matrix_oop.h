#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <exception>

#define BREAK(flag) if (!flag) break

class OMatrix {
 private:
    // attributes
    int _rows, _cols;                                   // rows and columns attributes
    double **_matrix;                                   // pointer where the matrix will be allocated
        
    // secondary private methods
    void create_matrix();
    void delete_matrix();
    void print_matrix();
    OMatrix cut_matrix(int row, int column);
    OMatrix minor_matrix();

 public:
    OMatrix();                                          // default constructor
    OMatrix(int rows, int cols);                        // parameterized constructor
    OMatrix(const OMatrix& other);                      // copy constructor
    OMatrix(OMatrix&& other);                           // move constructor
    ~OMatrix();                                         // destructor

    // operators overloads
    OMatrix& operator= (const OMatrix& other);          // assignment operator overload
    bool operator== (const OMatrix& other);
    OMatrix& operator+= (const OMatrix& other);
    OMatrix operator+ (const OMatrix& other);
    OMatrix& operator-= (const OMatrix& other);
    OMatrix operator- (const OMatrix& other);
    OMatrix operator* (const OMatrix& other);
    OMatrix operator* (const double value);
    OMatrix& operator*= (const OMatrix& other);
    OMatrix& operator*= (const double value);
    double& operator() (int row, int col);               // index operator overload

    // some public methods
    bool eq_matrix(const OMatrix& other);
    void sum_matrix(const OMatrix& other);
    void sub_matrix(const OMatrix& other);
    void mul_number(const double num);
    void mul_matrix(const OMatrix& other);
    OMatrix transpose();
    OMatrix calc_complements();
    double determinant();
    OMatrix inverse_matrix();
    void fill_matrix();

    // accessor (or getter)
    int getCols();
    int getRows();

    // mutator (or setter)
    void setCols(int value);
    void setRows(int value);
};
