#ifndef _MAGICSQUARE_
#define _MAGICSQUARE_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>

typedef std::vector<std::vector<int>> Magic; //declare the 2D vector type as Magic so we dont have to keep typing it out

class MagicSquare
{
public:

    /**
    Constructor:  It will store the square as a 2D vector where 0 indicates 
    no value has been placed in the slot at a given row and column yet. 
    This will also store a 2D vector that masks the square to store exact indexes
    of taken values

    @param the size of the square inputted by the user
    */

    MagicSquare(size_t squareSize) : squareSize(squareSize), tracker()
    {
        magic.assign(squareSize, std::vector<int>(squareSize, 0));
        mask.assign(squareSize, std::vector<int>(squareSize, 0));
    }
    /**
    bool function empty: checks if a given position in the magic square is empty

    @param row index and column in dex of the square
    @return true or false if the spot is empty
    */

    bool empty(size_t row, size_t column) const;

    /**
    bool function taken: checks if a given number is already used in the magic square

    @param and int that represents the take number
    @return true or false if the number has been taken
    */

    bool taken(int i) const;

    /**
    bool function checkRow: after each row is filled (except for the last), checks if
    the square could potentially be valid - it will check that the sum of each row is the
    target sum squareSum and that the sum of each partially filled column does not exceed squareSum

    @param none
    @return true if the square is valid so far and false if it fails
    */

    bool checkRow();

    /**
    bool function checkValid: checks if a complete magic square satisfies the proper
    conditions to be a solution. Similar to checkRow, but it also checks to see if the
    sums of the diagonals are valid as well

    @param none
    @return true if the square is valid, false otherwise
    */

    bool checkValid();

    /**
    RECURSIVE FUNCTION solveSquare: generates solutions for the square, calls checkValid
    and checkRow appropriately 

    @param an index tracking the number of slots already considered in the recursion
    @return prints out solutions to the squares and the int number of solutions there are
    */

    int solveSquare(int index);

    /**
    getter function get_solutions: this will just return the count (# of solutions) from solveSquare

    @param none
    @return number of solutions stored in private variable
    */

    int get_solutions();

    /**
    overloaded stream operator >> to read from the user's input into a std::vector<std::vector<int>>
    making the asterisks entered by the user into zeros, also adding numbers entered by the user
    into a taken set and keeping them in the spot they were entered

    @param an input stream and MagicSquare class object
    @return a stream that properly processes the user input
    */

    friend std::istream& operator>>(std::istream& is, MagicSquare& s);

    /**
    overloaded stream operator << output in the desired format of the square

    @param an output stream and MagicSquare class object
    @return outputs the desired square format
    */

    friend std::ostream& operator << (std::ostream& os, const MagicSquare& s);


private:
    size_t squareSize; // size of the square
    Magic magic; // the magic square 2D vector
    Magic mask; // the mask of the magic square
    int solutions; // the count of of the amount of solutions
    std::set<int> tracker; // set of taken numbers
    const int squareSum = squareSize * (squareSize * squareSize + 1) / 2; // sum formula
};



#endif