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
     * Only checkSudoku should be called. It uses all of the other functions to check the grid
     */
    bool checkSudoku();
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
     * On failure, returns false and the current grid is left unchanged
     * On succsess, returns true and the current grid is deleted and replaced with a new one
     * Uses a brute force method and the call while(generateUnsolvedSudoku()); will always produce a valid result
     */
    bool generateUnsolvedSudoku();


    /* Used to check the number of solutions
     * The result is stored in a variable pointed to by counter
     * *counter should always be initalised to 0
     * After finding 2 solutions it exits - this is because it's impossible to check the amount of solutions
     *  for grids which are almost empty, since it's too large.
     */
    void countSolutions(int row, int col, int* counter);



    /* Getters for the private variables
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
