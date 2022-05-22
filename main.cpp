#include <iostream>
#include "matrix.hpp"

int main()
{
    try
    {
        Matrix m1(1, 1, 1);
        std::cout << m1.getValue(1, 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}