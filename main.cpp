#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include<QApplication>

#include"errormessage.h"
#include "popup.h"
#include "sudokuwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SudokuWindow pop(9);
    pop.move(300, 300);
    pop.setWindowTitle("Sudoku");
    pop.show();

    return app.exec();
}
