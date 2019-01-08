#include "sudoku.h"


int **allocateMatrixMemory(int dimension){
    int** m = new int *[dimension];
    int i, j;
    for(i = 0; i < dimension; i++){
        m[i] = new int[dimension];
        for(j = 0; j < dimension; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

void deallocateMatrixMemory(int** m, int dimension){
    int i;
    for(i = 0; i < dimension; i++){
        delete m[i];
    }
    delete m;
}

int* randomArray(int size){
    int *array = new int[size];
    int i;
    for(i = 0; i < size; i++){
        array[i] = i + 1;
    }
    random_shuffle(&array[0], &array[size]);

    return array;
}

int* zeroArray(int size){
    int *array = new int[size];
    int i;
    for(i = 0; i < size; i++){
        array[i] = 0;
    }

    return array;
}

int matrixSum(int **m, int dimension){
    int sum = 0;
    int i, j;
    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension; j++){
            sum+= m[i][j];
        }
    }
    return sum;
}

Sudoku::Sudoku(int dim)
{
    dimension = dim;
    grid = allocateMatrixMemory(dimension);
}

Sudoku::Sudoku(Sudoku &s){
    dimension = s.getDimension();
    int** _grid = s.getGrid();

    grid = allocateMatrixMemory(dimension);
    int i, j;
    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension; j++){
            grid[i][j] = _grid[i][j];
        }
    }
}

bool Sudoku::generateUnsolvedSudoku(){
    int **filled = allocateMatrixMemory(dimension);
    int **_grid = allocateMatrixMemory(dimension);

    int cnt = 0;
    int row, col;
    int** tmp;
    do{
        do{
            int nextToFill = rand()%(dimension * dimension);
            row = nextToFill/dimension;
            col = nextToFill%dimension;
            filled[row][col] = 1;
            _grid[row][col] = grid[row][col];

        }while((matrixSum(filled, dimension) < 20));


        tmp = grid;
        grid = _grid;
        _grid = tmp;

        countSolutions(0, 0, &cnt);
        if(cnt == 1){
            deallocateMatrixMemory(_grid, dimension);
            return true;
        }else{
            cnt = 0;

            tmp = grid;
            grid = _grid;
            _grid = tmp;
        }

    }while(matrixSum(filled, dimension) < 45);



    deallocateMatrixMemory(filled, dimension);
    deallocateMatrixMemory(_grid, dimension);
    return false;
}

bool Sudoku::checkRows(){
    int i, j;
    int* digits = new int[dimension + 1];

    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension + 1; j++){
            digits[j] = 0;
        }

        for(j = 0; j < dimension; j++){
            int index = grid[i][j];
            digits[index]++;

            if((index != 0) & (digits[index] > 1)){
               // cout << "Check failed on number " << index << " in row " << i + 1 <<" Col " << j + 1 << endl;
                return false;
            }
        }

    }

    return true;
}

bool Sudoku::checkCols(){
    int i, j;
    int* digits = new int[dimension + 1];

    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension + 1; j++){
            digits[j] = 0;
        }

        for(j = 0; j < dimension; j++){
            int index = grid[j][i];
            digits[index]++;

            if((index != 0) & (digits[index] > 1)){
                //cout << "Check failed on number " << index << " in col " << i + 1 <<" Row " << j + 1 << endl;
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::checkSquare(int i, int j){
    int i2, j2;
    int* digits = zeroArray(dimension + 1);

    for(i2 = 0; i2 < 3; i2++){
        for(j2 = 0; j2 <3; j2++){
            int index = grid[i*3 + i2][j*3 + j2];
            digits[index]++;
            if((index != 0) & (digits[index] > 1)){
               // cout << "Square check failed on number " << index << "in row " << i * 3 + i2 + 1 << " col " << j*3 + j2 + 1 << endl;
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::checkSquares(){
    int i, j;
    for(i = 0; i < (dimension + 1)/3; i++){
        for(j = 0; j < (dimension + 1)/3; j++){
        if(!checkSquare(i, j)) return false;
        }
    }
    return true;
}

bool Sudoku::checkSudoku(){
    return checkRows() & checkCols() & checkSquares();

}

bool Sudoku::generateSudoku(int row, int col){
    row += col/dimension;
    col = col%dimension;
    if( row == dimension){
        return checkSudoku();
    }
    int *array = randomArray(dimension);
    int i;
    int k = grid[row][col];

    for(i = 0; i < dimension; i++){
        grid[row][col] = array[i];
        if(!checkSudoku()){
             grid[row][col] = k;
             continue;
        }
        if(generateSudoku(row, col + 1)){
            return true;
        }else{
             grid[row][col] = k;
        }
    }
    return false;
}

void Sudoku::countSolutions(int row, int col, int* counter){
    row += col/dimension;
    col = col%dimension;
    if( row == dimension){
        if(checkSudoku()){
            (*counter)++;
        }
        return;
    }


    if(grid[row][col]){
        countSolutions(row, col + 1, counter);
        return;
    }

    int *array = randomArray(dimension);

    int i;
    for(i = 0; i < 9; i++){
        grid[row][col] = array[i];
        if(!checkSudoku()){
            grid[row][col] = 0;
            continue;
        }
        countSolutions( row, col + 1, counter);
        grid[row][col] = 0;
        if(*counter > 1) return;
    }
    return;
}

int** Sudoku::getGrid(){
    return grid;
}

int Sudoku::getDimension(){
    return dimension;
}

void Sudoku::getSudokuFromFile(string path){

    ifstream f;
    f.open(path);
    if(!f.is_open()){
        cout << "Nije otvoren fajl" << endl;
        exit(1);
    }
    int i, j = 0;
    for( i = 0; i < dimension; i++){
        for( j = 0; j < dimension; j++){
            f >> grid[i][j];
        }
    }


}

void Sudoku::printGrid(){
    int i, j;
    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension; j++){
            std::cout << grid[i][j] << " ";
        }
        std::cout << endl;
    }
}

