#include <iostream>
#include "matrix.hpp"

using namespace std;

int main()
{
    try
    {
        ifstream in("myMatrix.txt");
        Matrix<int> Y;
        Matrix<int> X(2, 1, 1), A(3, 3, 1), C(3, 3, 1);
        Matrix<int> Z(3, 3, 7.0);
        Matrix<int> W(in);

        Y(2, 1) = 10;
        C = Y;
        C -= A;
        A = C - A;

        cout << A << endl;
        cout << Y << endl;
        Y -= A;
        cout << Y << endl;

        cout << endl
             << W * Z << endl;

        cout << endl
             << X << endl;
        X *= 2;
        cout << endl
             << X << endl;
        C = A * X;
        C *= Z;

        A = A * 2;

        if (A == C)
            if (X != Y)
            {
                cout << Z << endl;
                cin >> Z;
            }

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}