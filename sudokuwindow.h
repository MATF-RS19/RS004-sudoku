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
    /* Creates a Sudoku object and uses it to create a sudoku puzzle
     */
    explicit SudokuWindow(int dimension = 9, QWidget *parent = nullptr);

    /* Synchornizes button text with the Sudoku grid
     */
    void syncButtons();
signals:

public slots:
    /* timer function used to synchronize the text value of buttons with the Sudoku grid
     * if an Incorrect number is inputed or if the Sudoku has been solved, displays a warning message to the player
     */
    void checkGrid();

    /* Shows the Popup object at cursos location
     */
    void onClick();

    /* Creates a new sudoku grid
     */
    void reset();
private:
    /* if true, checkGrid does nothing and the player can input any number he wants
     */
    bool isSolved;

    /* a list of all current connections
     */
    QMetaObject::Connection *connections;
    int cons;

    int dimension;
    int **grid;
    Sudoku *s;
    Popup *p;

    /* Contains all of the buttons in the sudoku window
     */
    QPushButton ***btns;
};

#endif // SUDOKUWINDOW_H
