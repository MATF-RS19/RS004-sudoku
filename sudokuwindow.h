#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include"errormessage.h"
#include"sudoku.h"
#include"popup.h"
#include<QWidget>
#include<QPushButton>

class SudokuWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SudokuWindow(int dimension = 9, QWidget *parent = nullptr);


signals:

public slots:
    void checkGrid();
    void onClick();
private:
    bool isSolved;
    int dimension;
    int **grid;
    Sudoku *s;
    Popup *p;
    QPushButton ***btns;
};

#endif // SUDOKUWINDOW_H
