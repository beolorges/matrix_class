#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iostream>

class Matrix
{
private:
    int rows;
    int columns;
    double **matrixValues;

    void setRows(int _row) { this->rows = _row; };
    void setColumns(int _column) { this->columns = _column; };

    // FUNÇÕES AUXILIARES
    int maxColumns(const Matrix &_other) const;
    int maxRows(const Matrix &_other) const;

    Matrix returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum = Matrix()) const;
    void fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const double &_constToMultiply = 0);
    void fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum = Matrix());

public:
    // CONSTRUCTORS AND DESTRUCTOR
    Matrix() : rows(-1), columns(-1) { matrixValues = (double **)malloc(0 * sizeof(double)); };
    Matrix(const int &_rows, const int &_columns, const double &_value);
    Matrix(const Matrix &_other) : rows(_other.getRows()), columns(_other.getColumns()) { matrixValues = (double **)malloc(rows * columns * sizeof(double)); };
    // Matrix(ifstream &_file);
    ~Matrix()
    {
        free(matrixValues);
        delete[] matrixValues;
    };

    // GET OPERATIONS
    int getRows() const { return this->rows; };
    int getColumns() const { return this->columns; };
    double getValue(int _row, int _column) const;

    // SET OPERATIONS
    void setValue(int _row, int _column, double _value);

    // MATH OPERATORS OVERLOAD
    Matrix operator+(Matrix const &_other) const { return this->returnMatrix(this->maxColumns(_other), this->maxRows(_other), 1, Matrix()); };
    Matrix operator-(Matrix const &_other) const { return this->returnMatrix(this->maxColumns(_other), this->maxRows(_other), 2, Matrix()); };
    Matrix operator*(Matrix const &_other) const;
    // Matrix operator*(double const &_other) const { return this->returnMatrix(this->getColumns(), this->getRows(), 1, _other); };
    Matrix operator~() const { return this->returnMatrix(this->getRows(), this->getColumns(), 3, Matrix()); };
    void operator=(Matrix const &_other);
    void operator+=(Matrix const &_other) { this->returnMatrix(this->maxColumns(_other), this->maxRows(_other), 1, _other); };
    void operator-=(Matrix const &_other) { this->returnMatrix(this->maxColumns(_other), this->maxRows(_other), 2, _other); };
    void operator*=(Matrix const &_other);
    void operator*=(double const &_other) { this->fillMatrix(this->getColumns(), this->getRows(), 2, _other); };
    // double &operator()(int _columns, int _rows) { return &(this->getValue(_rows, _columns)); };

    // COMPARATORS OVERLOAD
    bool operator==(Matrix const &_other) const;
    bool operator!=(Matrix const &_other) const { return !(*this == _other); };

    // friend functions
    //  IOSTREAM OPERATORS
    // friend istream &operator>>(istream &input, Matrix &_matrix);
    // friend ostream &operator<<(ostream &output, const Matrix &_matrix);
};

// #include "matrix.cpp"

#endif