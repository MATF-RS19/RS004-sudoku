#ifndef SUDOKU_H
#define SUDOKU_H

#include<fstream>
#include<QTextStream>
#include<iostream>
#include<algorithm>
#include<unistd.h>

using namespace std;
class Sudoku
{
private:
    /* Sudoku is a 2D matrix, pointed to by grid, of the size dimension * dimension
     */
    int dimension;
    int** grid;

public:
    Sudoku(int dim);
    Sudoku(Sudoku &s);


    /*  These functions check if the current grid is a valid Sudoku
     * Only checkSudoku or checkFullSuudoku should be called. It uses all of the other functions to check the grid
     * number 0 is used to indicate an empty field and checkSudoku ignores it
     *
     *
     * checkFullSudoku will perform a check to make sure that only only numbers in interval [1, 9] exist in the grid
     */
    bool checkSudoku();
    bool checkFullSudoku();
    bool checkRows();
    bool checkCols();
    bool checkSquares();
    bool checkSquare(int i, int j);



    /* Attempts to change the current grid into a valid Sudoku
     * Upon success returns true
     * If the current grid is not zeroed, there is a chance that a valid Sudoku can't be found
     * If this is the case, it returns false
     *
     * The arguments row and col indicate which row and col the generation should start at
     * The default way to use the alghoritm is by passing 0 to both arguments
     */
    bool generateSudoku(int row, int col);



    /* Creates a new grid which has only 1 valid solution
     * NOTE: grid must be set to  a fully solved sudoku, before calling this function, such as calling generateSudoku(0, 0)
     */
    void generateUnsolvedSudoku();


    /* Used to check the number of solutions
     * The result is stored in a variable pointed to by counter
     * *counter should always be initalised to 0
     * After finding 2 solutions it exits - this is because it's impossible to check the amount of solutions
     *  for grids which are almost empty
     */
    void countSolutions(int row, int col, int* counter);


    /*Empties the grid of all numbers - this is done by setting all values to 0
     */
    void resetSudoku();


    /* Getters for the private variables
     * NOTE: the internal SudokuGrid can be changed by using getGrid
     */
    int** getGrid();
    int getDimension();


    /*  Gets a sudoku from a file in location path
     *  Mainly used for testing purposes
     */
    void getSudokuFromFile(string path);


    /* Outputs the current grid in a readable format to the iostream cout
     */
    void printGrid();
};

#endif // SUDOKU_H
