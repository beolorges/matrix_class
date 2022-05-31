#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>

using namespace std;

/*-------------------------------PREVIOUSLY DECLARATIONS--------------------------*/
template <class T>
class Matrix;

template <typename T>
istream &operator>>(istream &input, Matrix<T> &_matrix);

template <typename T>
ostream &operator<<(ostream &output, const Matrix<T> &_matrix);

/*-------------------------------CLASS DECLARATION---------------------------*/
template <class T>
class Matrix
{
private:
    int rows;
    int columns;
    T **matrixValues;

    /*--------------------------- FILLING MATRICES FUNCTIONS---------------------------------*/
    Matrix returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum = Matrix()) const;
    Matrix returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const T &_const = 0) const;
    void fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const T &_constToMultiply = 0);
    void fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum = Matrix());

public:
    /*----------------------------CONSTRUCTORS AND DESTRUCTOR----------------------------*/
    Matrix() : rows(0), columns(0){};
    Matrix(const int _rows, const int _columns, const T &_value = 0);
    Matrix(const Matrix &_other) : rows(_other.getRows()), columns(_other.getColumns()) { matrixValues = (T **)malloc(rows * columns * sizeof(T)); };
    Matrix(ifstream &_file);
    ~Matrix() { delete matrixValues; };

    /*-----------------------------------GET OPERATIONS---------------------------------*/
    int getRows() const { return this->rows; };
    int getColumns() const { return this->columns; };
    T getValue(int _row, int _column) const;

    /*-----------------------------------SET OPERATIONS---------------------------------*/
    void setValue(int _row, int _column, T _value);

    /*-------------------------------MATH OVERLOAD OPERATIONS---------------------------*/
    Matrix operator+(Matrix const &_other) const;
    Matrix operator-(Matrix const &_other) const;
    Matrix operator*(Matrix const &_other) const;
    void operator=(Matrix const &_other);
    void operator+=(Matrix const &_other);
    void operator-=(Matrix const &_other);
    void operator*=(Matrix const &_other);
    T &operator()(int const &_columns, int const &_rows);
    Matrix operator*(T const &_other) const { return this->returnMatrix(this->getColumns(), this->getRows(), 1, _other); };
    Matrix operator~() const { return this->returnMatrix(this->getRows(), this->getColumns(), 3, Matrix()); };
    void operator*=(T const &_other) { this->fillMatrix(this->getColumns(), this->getRows(), 1, _other); };

    /*-------------------------------COMPARATORS OVERLOAD ---------------------------*/
    bool operator==(Matrix const &_other) const;
    bool operator!=(Matrix const &_other) const { return !(*this == _other); };

    /*---------------------------------FRIEND FUNCTIONS-------------------------------*/
    friend istream &operator>><>(istream &input, Matrix<T> &_matrix);
    friend ostream &operator<< <>(ostream &output, const Matrix<T> &_matrix);
};

#include "matrix.cpp"

#endif