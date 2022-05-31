#include "matrix.hpp"

#ifndef MATRIX_CPP
#define MATRIX_CPP

using namespace std;

template <class T>
Matrix<T>::Matrix(ifstream &_file)
{
    if (!(_file.is_open()))
        throw std::runtime_error("File not openned");

    int itRow = 0;
    int itColumn = 0;

    _file >> this->rows >> this->columns;

    while (_file.good())
    {
        this->matrixValues = new T *[this->getRows()];

        while (itRow < this->getRows())
        {
            this->matrixValues[itRow] = new T[this->getColumns()];
            while (itColumn < this->getColumns())
            {
                _file >> this->matrixValues[itRow][itColumn];
                itColumn++;
            }
            itColumn = 0;
            itRow++;
        }
    }
}

template <class T>
Matrix<T>::Matrix(const int _rows, const int _columns, const T &_value)
{
    if (_rows < 0)
        throw std::runtime_error("Its not possible to create a Matrix with negative rows");

    if (_columns < 0)
        throw std::runtime_error("Its not possible to create a Matrix with negative columns");

    this->fillMatrix(_columns, _rows, 2, _value);
}

template <class T>
T Matrix<T>::getValue(int _row, int _column) const
{
    if (this->getRows() < (_row + 1) || _row < 0)
        throw std::out_of_range("This matrix does not have that number of rows");

    if (this->getColumns() < (_column + 1) || _column < 0)
        throw std::out_of_range("This matrix does not have that number of columns");

    return matrixValues[_row][_column];
}

template <class T>
void Matrix<T>::setValue(int _row, int _column, T _value)
{
    if (this->getRows() < (_row + 1) || _row < 0)
        throw std::out_of_range("This matrix does not have that number of rows");

    if (this->getColumns() < (_column + 1) || _column < 0)
        throw std::out_of_range("This matrix does not have that number of columns");

    this->matrixValues[_row][_column] = _value;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &_other) const
{
    if (this->getColumns() != _other.getColumns() || this->getRows() != _other.getRows())
        throw std::invalid_argument("Its not possible to sum two matrices with different orders");

    return this->returnMatrix(this->getColumns(), this->getRows(), 1, _other);
}

template <class T>
void Matrix<T>::operator+=(const Matrix<T> &_other)
{
    if (this->getColumns() != _other.getColumns() || this->getRows() != _other.getRows())
        throw std::invalid_argument("Its not possible to sum two matrices with different orders");

    *this = this->returnMatrix(this->getColumns(), this->getRows(), 1, _other);
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &_other) const
{
    if (this->getColumns() != _other.getColumns() || this->getRows() != _other.getRows())
        throw std::invalid_argument("Its not possible to subtract two matrices with different orders");

    return this->returnMatrix(this->getColumns(), this->getRows(), 2, _other);
}

template <class T>
void Matrix<T>::operator-=(const Matrix<T> &_other)
{
    if (this->getColumns() != _other.getColumns() || this->getRows() != _other.getRows())
        throw std::invalid_argument("Its not possible to sutract two matrices with different orders");

    *this = this->returnMatrix(this->getColumns(), this->getRows(), 2, _other);
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &_other) const
{
    if (this->getColumns() != _other.getRows())
        throw std::invalid_argument("The number of columns of Matrix A must be the same number as the number of rows of Matrix B to multiply");

    return this->returnMatrix(_other.getColumns(), this->getRows(), 4, _other);
}

template <class T>
void Matrix<T>::operator*=(const Matrix<T> &_other)
{
    if (this->getColumns() != _other.getRows())
        throw std::invalid_argument("The number of columns of Matrix A must be the same number as the number of rows of Matrix B to multiply");

    *this = this->returnMatrix(_other.getColumns(), this->getRows(), 4, _other);
}

template <class T>
void Matrix<T>::operator=(const Matrix<T> &_other)
{
    delete this->matrixValues;
    this->fillMatrix(_other.getColumns(), _other.getRows(), 2, 0);
    this->fillMatrix(this->getColumns(), this->getRows(), 1, _other);
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &_other) const
{
    int itColumn = 0;
    int itRow = 0;

    if (this->getColumns() != _other.getColumns())
        return false;

    if (this->getRows() != _other.getRows())
        return false;

    while (itRow < this->getRows())
    {
        while (itColumn < this->getColumns())
        {
            if (this->getValue(itRow, itColumn) != _other.getValue(itRow, itColumn))
                return false;
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }

    return true;
}
template <class T>
T &Matrix<T>::operator()(int const &_columns, int const &_rows)
{
    if (this->getRows() < (_rows + 1) || _rows < 0)
        throw std::out_of_range("This matrix does not have that number of rows");

    if (this->getColumns() < (_columns + 1) || _columns < 0)
        throw std::out_of_range("This matrix does not have that number of columns");

    return this->matrixValues[_columns][_rows];
}

template <class T>
Matrix<T> Matrix<T>::returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix<T> &_matrixToSum) const
{
    Matrix<T> resultMatrix(_numberOfRows, _numberOfColumns);
    int itColumn = 0;
    int itRow = 0;

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // SUM OF TWO MATRIX
                resultMatrix.setValue(itRow, itColumn, this->getValue(itRow, itColumn) + _matrixToSum.getValue(itRow, itColumn));
                break;

            case 2: // SUBTRACT OF TWO MATRIX
                resultMatrix.setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) - _matrixToSum.getValue(itRow, itColumn));
                break;

            case 3: // TRANSPOSITION OF A MATRIX
                resultMatrix.setValue(itRow, itColumn, (this->getValue(itColumn, itRow)));
                break;

            case 4: // MULTIPLICATOIN OF TWO MATRIX
                int auxIndex = 0;
                T valueToSum = 0;
                while (auxIndex < this->getColumns())
                {
                    valueToSum += (this->getValue(itRow, auxIndex) * _matrixToSum.getValue(auxIndex, itColumn));
                    auxIndex++;
                }
                resultMatrix.setValue(itRow, itColumn, valueToSum);
                break;
            }
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }

    return resultMatrix;
}

template <class T>
Matrix<T> Matrix<T>::returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const T &_const) const
{
    Matrix<T> resultMatrix(_numberOfRows, _numberOfColumns);
    int itColumn = 0;
    int itRow = 0;

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // MULTIPLICATION BY A CONSTANT
                resultMatrix.setValue(itRow, itColumn, this->getValue(itRow, itColumn) * _const);
                break;
            }
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }

    return resultMatrix;
}

template <class T>
void Matrix<T>::fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const T &_constNumber)
{
    int itColumn = 0;
    int itRow = 0;

    this->rows = _numberOfRows;
    this->columns = _numberOfColumns;

    if (_numberOfTheFunction == 2)
        this->matrixValues = new T *[_numberOfRows];
    while (itRow < _numberOfRows)
    {
        if (_numberOfTheFunction == 2)
            this->matrixValues[itRow] = new T[_numberOfColumns];
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {

            case 1: // MULTIPLICATION OF A MATRIX FOR A NUMBER
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) * _constNumber);
                break;

            case 2: // MULTIPLICATION OF A MATRIX
                this->setValue(itRow, itColumn, _constNumber);
                break;
            }
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }
}

template <class T>
void Matrix<T>::fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix<T> &_matrixToSum)
{
    int itColumn = 0;
    int itRow = 0;

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // EQUAL TO ANOTHER MATRIX
                this->setValue(itRow, itColumn, _matrixToSum.getValue(itRow, itColumn));
                break;

            case 2: // SUM OF TWO MATRICES
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn) + _matrixToSum.getValue(itRow, itColumn)));
                break;

            case 3: // SUBTRACT OF TWO MATRICES
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) - _matrixToSum.getValue(itRow, itColumn));
                break;
            }
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }
}

template <class T>
istream &operator>>(istream &input, Matrix<T> &_matrix)
{
    int itColumn = 0;
    int itRow = 0;
    T value = 0;

    while (itRow < _matrix.getRows())
    {
        while (itColumn < _matrix.getColumns())
        {
            input >> value;
            _matrix.setValue(itRow, itColumn, value);
            itColumn++;
        }
        itColumn = 0;
        itRow++;
    }

    return input;
}

template <class T>
std::ostream &operator<<(ostream &output, const Matrix<T> &_matrix)
{
    int itColumn = 0;
    int itRow = 0;

    while (itRow < _matrix.getRows())
    {
        while (itColumn < _matrix.getColumns())
        {
            output << _matrix.getValue(itRow, itColumn) << " ";
            itColumn++;
        }
        itColumn = 0;

        if ((itRow + 1) != _matrix.getRows())
            output << endl;

        itRow++;
    }

    return output;
}
#endif