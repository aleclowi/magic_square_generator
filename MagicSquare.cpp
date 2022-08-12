#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include "MagicSquare.h"

bool MagicSquare::empty(size_t row, size_t col) const
{
	//conditions for if the index entered is zero, then the spot is empty
	if (mask[row][col] == 0)
	{
		return true;
	}
	//any other number here will return false
	else
	{
		return false;
	}
}

bool MagicSquare::taken(int i) const
{
	//create a bool variable that will find the taken number in the stored set
	auto track = tracker.find(i) != tracker.end();

	//if this variable reads true then the number is taken
	if (track == true)
	{
		return true;
	}
	//any other numbers not in the set will return false
	else
	{
		return false;
	}
}

bool MagicSquare::checkRow()
{
	//create the nested for loop to loop through each in dex of the square
	for (int i = 0; i < squareSize; ++i)
	{
		//here we create a bool flag, this is just to break the loop if the empty is read as false
		bool flag = false;
		int sum = 0;
		for (int j = 0; j < squareSize; ++j)
		{
			//if the index is not empty, add it to the sum
			if (!empty(i, j))
			{
				sum += magic[i][j]; //added square into to the sum
			}
			//any other possibilities break the loop because checkRow is not valid yet or the row is empty
			else
			{
				flag = true;
				break;
			}
		}
		//if the entire row is empty, break the loop because we are not adding anything here yet
		if ((flag))
		{
			break;
		}
		//if the row sum is not equal to the private variable squareSum, then checkRow is not valid
		if (squareSum != sum)
		{
			return false;
		}
	}
	//this nested for loop will loop through the column indexes.
	for (int j = 0; j < squareSize; ++j)
	{
		//create the column sum variable
		int sumCol = 0;
		//check each row index in each column, these are the numbers we will be adding
		for (int i = 0; i < squareSize; ++i)
		{
			sumCol += magic[i][j];
		}
		//after the columns have been added, we check to see if it matches the square sum.
		//if the square sum is greater than or equal to the column sum, then this will be true, otherwise false
		if (sumCol > squareSum)
		{
			return false;
		}
	}
	return true;
}


bool MagicSquare::checkValid()
{
	//for this function will will check the rows, columns, AND both diagonals to see if they match squareSum
	//nested for loop for the sum of the rows
	for (int i = 0; i < squareSize; ++i)
	{
		int sumRow = 0;
		for (int j = 0; j < squareSize; ++j)
		{
			//add the indexes of the rows together to another variable
			sumRow += magic[i][j];
		}
		//if they're not equal, then the square is not valid yet
		if (sumRow != squareSum)
		{
			return false;
		}
	}
	//nested for loop for the columns, the same code we used for the rows is conducted here
	for (int j = 0; j < squareSize; ++j)
	{
		int sumCol = 0;
		for (int i = 0; i < squareSize; ++i)
		{
			sumCol += magic[i][j];
		}
		if (sumCol != squareSum)
		{
			return false;
		}
	}
	//create variables for the diagonals
	int sumDiag1 = 0;
	int sumDiag2 = 0;
	//nesting is not needed since we are checking addition of specific indexes
	for (int k = 0; k < squareSize; ++k)
	{
		//here is the sum of the left to right diagonal
		sumDiag1 += magic[k][k];
		//here is the sum of the right to left diagonal
		sumDiag2 += magic[k][squareSize - 1 - k];
	}
	//if either one of the diagonals are not equal to the squareSum, the checkValid is false
	if (sumDiag1 != squareSum || sumDiag2 != squareSum)
	{
		return false;
	}

	return true;
}

int MagicSquare::solveSquare(int index)
{
	//these two variables will be modified over and over again through recursion
	int row = (index / squareSize); //total index should be 4 for 2x2, 9 for 3x3, 16, for 4x4, so this will look to every index of the square
	int col = (index % squareSize); //this will take the columns as they're divided up by the index divisible by the square Size
	int count = 0; // this will be the counter of solutions which we will set equal to solutions at the the end
	// if the index is at the last index of the square, n^2, we will check to see if the square is valid
	if (index == squareSize * squareSize)
	{
		//if the square ends up being valid, then print the solution! use the normal nested for loop 
		if (checkValid() == true)
		{
			for (int j = 0; j < squareSize; j++)
			{
				for (int k = 0; k < squareSize; k++)
				{
					std::cout << magic[j][k] << " ";
				}
				std::cout << "\n";
			}
			std::cout << "\n";
			//returning 1 here will take the solution and count it towards the solutions
			return 1;
		}
		//if the possible square is not valid, return 0 since it's not a solti
		return 0;
	}
	//In this section we will place values into the empty cells, so if a cell is empty...
	if (empty(row, col) == true)
	{
		//starting a1 one, try every number from 1 to n^2 in each index of magicSquare to check to see if it works
		for (int i = 1; i < (squareSize * squareSize + 1); i++)
		{
			magic[row][col] = i;
			//if the cell has been taken already, or filled in by the user, then move on to the next possibility
			if (taken(i) == true)
			{
				continue;
			}
			//if the row has been solved with the indexes we attempted, then throw the indexes into our tracker(taken) set
			if (checkRow() == true)
			{
				tracker.insert(i);
				//here is our recursive call, the amount of times this runs will addd to the amount of solutions we have
				count += solveSquare(index + 1);
				//Then we have to erase the cells we inputted because if we don't it will read each one as taken over and over again
				tracker.erase(i);
			}
		}
	}
	else
	{
		//set the mask we created equal to the magic square. this allows us to keep any number that was inputted by the user
		//in the specific index in which it was entered.
		magic[row][col] = mask[row][col];
		count += solveSquare(index + 1); // another recursive call for solutions
	}

	magic[row][col] = 0; //after a particular solution is finished, this will reset the square to check for the next solution
	solutions = count; //set the count we had equal to the solutions 
	return count; //return the amount of solutions we had, this will allow the getter function to work
}

int MagicSquare::get_solutions()
{
	return solutions; //simply return the amount of solutions stored from the recursive function
}

std::istream& operator>>(std::istream& is, MagicSquare& s)
{
	//create a string which will be each input string from the user
	std::string index;
	// a nested for loop for the inputs, similar to the nesting for magic square, since the 
	//user input will input in the format of a square.
	for (int row = 0; row < s.squareSize; ++row)
	{
		for (int col = 0; col < s.squareSize; ++col)
		{
			//input the strings entered by the user
			is >> index;
			//here is where we depict whether or not a user has entered a star or a number
			//if a start was entered, we can continue since the square already has zeros inputted
			//into it for the empty cells
			if (index == "*")
			{
				continue;
			}
			//if a number is entered, place it in the tracker(taken) set and input it into the mask and
			//square vector in the specific position it was put in. using a mask will allow the number to not be deleted in the 
			//recrusive function.
			else
			{
				s.mask[row][col] = std::stod(index);
				s.magic[row][col] = std::stod(index);
				s.tracker.insert(std::stod(index));
			}
		}
	}
	return is; //return the input stream
}

std::ostream& operator << (std::ostream& os, const MagicSquare& s)
{
	//for the output stream we simply output it in the form of a 2D vector, separating the cells by a space
	for (int row = 0; row < s.magic.size(); ++row)
	{
		for (int col = 0; col < s.magic.size(); ++col)
		{
			os << s.magic[row][col] << ' ';
		}
		os << '\n';
	}
	return os;
}

