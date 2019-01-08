
#include "ui_main.h"
#include "sudoku.h"
#include<time.h>
#include<iostream>
#include<QTextStream>
#include<QCoreApplication>
using namespace std;

int* random2Array(int size){
    int *array = new int[size];
    int i;
    for(i = 0; i < size; i++){
        array[i] = i;
    }
    random_shuffle(&array[0], &array[size - 1]);

    return array;
}

int main(int argc, char **argv){
    QCoreApplication(argc, argv);
    srand(time(NULL));
    Sudoku s(9);
    s.generateSudoku(0, 0);
    while(!s.generateUnsolvedSudoku());
    s.printGrid();
}
