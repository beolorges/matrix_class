#include "matrix.hpp"

// #ifndef MATRIX_CPP
// #define MATRIX_CPP

using namespace std;

//
// Matrix::Matrix(ifstream &_file)
// {
//     if (!(_file.is_open()))
//         throw std::runtime_error("Arquivo não aberto corretamente");

//     double number = _file.get();
//     int column = 0;
//     int row = 0;

//     while (_file.good())
//         while (row < this->getRows())
//         {
//             while (column < this->getColumns())
//             {
//                 this->setValue(row, column, number);
//                 column++;
//                 number = _file.get();
//             }
//             row++;
//         }
// }

Matrix::Matrix(const int &_rows, const int &_columns, const double &_value)
{
    this->rows = _rows;
    this->columns = _columns;

    // if (this->_rows == 0 || _columns == 0)
    //     throw std::runtime_error("Its not possible to create a Matrix with value with no dimensions");

    // if (this->_rows < 0)
    //     throw std::runtime_error("Its not possible to create a Matrix with negative rows");

    // if (_columns < 0)
    //     throw std::runtime_error("Its not possible to create a Matrix with negative columns");

    this->matrixValues = (double **)malloc(_rows * _columns * sizeof(double));
    this->fillMatrix(this->getColumns(), this->getRows(), 3, _value);
}

double Matrix::getValue(int _row, int _column) const
{
    if (this->getRows() < _row || _row <= 0)
        throw std::out_of_range("This matrix does not have that number of rows");

    if (this->getColumns() < _column || _column <= 0)
        throw std::out_of_range("This matrix does not have that number of columns");

    return matrixValues[_row - 1][_column - 1];
}

void Matrix::setValue(int _row, int _column, double _value)
{
    if (this->getRows() < _row || _row <= 0)
        throw std::out_of_range("This matrix does not have that number of rows");

    if (this->getColumns() < _column || _column <= 0)
        throw std::out_of_range("This matrix does not have that number of columns");

    this->matrixValues[_row - 1][_column - 1] = _value;
}

int Matrix::maxColumns(const Matrix &_other) const
{
    if (this->getColumns() > _other.getColumns())
        return this->getColumns();

    return _other.getColumns();
}

int Matrix::maxRows(const Matrix &_other) const
{
    if (this->getRows() > _other.getRows())
        return this->getRows();

    return _other.getRows();
}

Matrix Matrix::operator*(const Matrix &_other) const
{
    if (this->getColumns() == _other.getRows())
        return this->returnMatrix(this->getRows(), this->getColumns(), 7, _other);
    else
        throw std::invalid_argument("The number of columns must be the same as the number of rows");
}

void Matrix::operator*=(const Matrix &_other)
{
    if (this->getColumns() == _other.getRows())
        *this = this->returnMatrix(this->getRows(), this->getColumns(), 8, _other);
    else
        throw std::invalid_argument("The number of columns must be the same as the number of rows");
}

void Matrix::operator=(const Matrix &_other)
{
    realloc(this->matrixValues, this->maxColumns(_other) * this->maxRows(_other) * sizeof(double));
    this->returnMatrix(this->maxColumns(_other), this->maxRows(_other), 4, _other);
}

Matrix Matrix::returnMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum) const
{
    Matrix resultMatrix(_numberOfRows, _numberOfColumns, 0);
    int itColumn = 1;
    int itRow = 1;

    /*
        SE FUNCIONAR APAGAR AS THIS -> BLA BLA BLA
    */

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // SUM OF TWO MATRIX
                resultMatrix.setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) + _matrixToSum.getValue(itRow, itColumn));

            case 2: // SUBTRACT OF TWO MATRIX
                resultMatrix.setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) - _matrixToSum.getValue(itRow, itColumn));

            case 3: // MULTIPLICATION BY A CONSTANT
                resultMatrix.setValue(itColumn, itRow, (this->getValue(itRow, itColumn)));

            case 7:
            {
                int auxIndex = 1;
                double valueToSum = 0;
                while (auxIndex < this->getColumns())
                {
                    valueToSum += this->getValue(itRow, valueToSum) * _matrixToSum.getValue(valueToSum, itRow);
                }
                resultMatrix.setValue(itRow, itColumn, valueToSum);
            }

                // case 8:
                //     if (this->getValue(itRow, itColumn) != _matrixToSum.getValue(itRow, itColumn))
                //         return false;
            }
            itColumn++;
        }
        itRow++;
    }

    // if (_numberOfTheFunction == 8)
    //     return true;

    if (_numberOfTheFunction == 0 || _numberOfTheFunction == 1 || _numberOfTheFunction == 2 || _numberOfTheFunction == 7)
        return resultMatrix;
}

void Matrix::fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const double &_constNumber)
{
    // Matrix resultMatrix(_numberOfRows, _numberOfColumns, 0);
    int itColumn = 1;
    int itRow = 1;

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // SUM OF TWO MATRIX
                    // resultMatrix.setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) * _constNumber);

            case 2: // MULTIPLICATION OF A MATRIX FOR A NUMBER
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) * _constNumber);

            case 3: // MULTIPLICATION OF A MATRIX
                this->setValue(itRow, itColumn, _constNumber);
            }
            itColumn++;
        }
        itRow++;
    }
    // if (_numberOfTheFunction == 1)
    // return resultMatrix;
}

//
// istream &operator>>(istream &input, Matrix &_matrix)
// {
//     int itColumn = 0;
//     int itRow = 0;

//     while (itRow < _matrix.getRows())
//     {
//         while (itColumn < _matrix.getColumns)
//         {
//             _matrix.setValue(itRow, itColumn, input);
//             itColumn++;
//         }
//         itRow++;
//     }
// }

//
// ostream &operator<<(ostream &output, Matrix &_matrix)
// {
//     int itColumn = 0;
//     int itRow = 0;

//     while (itRow < _matrix->getRows())
//     {
//         while (itColumn < _matrix->getColumns())
//         {
//             output << _matrix->getValue(itRow, itColumn) << " ";
//             itColumn++;
//         }
//         cout << endl;
//         itRow++;
//     }

//     return output;
// }

void Matrix::fillMatrix(const int &_numberOfColumns, const int &_numberOfRows, const int &_numberOfTheFunction, const Matrix &_matrixToSum)
{
    int itColumn = 1;
    int itRow = 1;

    while (itRow < _numberOfRows)
    {
        while (itColumn < _numberOfColumns)
        {
            switch (_numberOfTheFunction)
            {
            case 1: // EQUAL TO ANOTHER MATRIX
                this->setValue(itRow, itColumn, _matrixToSum.getValue(itRow, itColumn));

            case 2:
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) + _matrixToSum.getValue(itRow, itColumn));

            case 3:
                this->setValue(itRow, itColumn, (this->getValue(itRow, itColumn)) - _matrixToSum.getValue(itRow, itColumn));
            }
            itColumn++;
        }
        itRow++;
    }
}

// #endif