#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "MagicSquare.h"

using namespace std;

int main()
{
    //first initialize the squaresize which will be inputted by the user
    size_t squareSize;
    cout << "Enter a square size: ";
    cin >> squareSize;
    MagicSquare s(squareSize);//constructor call with squaresize entered by the user
    cout << "Enter square format: " << "\n";
    //overloaded operator >> allows us to enter the square in the literal form of a square
    cin >> s;

    s.solveSquare(0); //recursive function call, this will output the solutions it finds

    std::cout << "Solving complete!\n";
    std::cout << "There were " << s.get_solutions() << " solutions!" << "\n"; //the amount of solutions will be outputted here
    return 0;
}