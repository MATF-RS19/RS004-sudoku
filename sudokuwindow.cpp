#include "sudokuwindow.h"
#include<time.h>
#include<QGridLayout>
#include<QKeyEvent>
#include<QApplication>
#include<QPoint>
#include<QCursor>
#include<QPalette>
#include<QTextStream>
#include<QTimer>

SudokuWindow::SudokuWindow(int dim, QWidget *parent) : QWidget(parent)
{
    isSolved = false;
    dimension = dim;

    srand(time(nullptr));
    s = new Sudoku(dim);
    s->generateSudoku(0, 0);
    s->generateUnsolvedSudoku();

    p = new Popup(dimension);
    p->setWindowTitle("Unesite broj");

    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(3);

    int i, j;
    grid = s->getGrid();
    btns = new QPushButton **[dimension];

    for(i = 0; i < dimension; i++){
        btns[i] = new QPushButton *[dimension];
        for(j = 0; j < dimension; j++ ){

            QString qs;
            if(grid[i][j] > 0){
                qs = QString::number(grid[i][j]);
            }else{
                qs = "";
            }
            btns[i][j] = new QPushButton(qs, this);
            btns[i][j]->setFixedSize(40, 40);



            layout->addWidget(btns[i][j], i, j);
            if(grid[i][j] == 0){
                connect(btns[i][j], &QPushButton::clicked, this, &SudokuWindow::onClick);
                connect(btns[i][j], &QPushButton::clicked, p, &Popup::onClick);
            }else{
                QPalette qp = btns[i][j]->palette();
                qp.setColor(QPalette::Button,QColor(Qt::gray));
                btns[i][j]->setAutoFillBackground(true);
                btns[i][j]->setPalette(qp);
                btns[i][j]->update();
            }
        }
    }
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout, this, &SudokuWindow::checkGrid);
    timer->start(1000);
}

void SudokuWindow::checkGrid(){
    int i, j;
    if(isSolved) return;
    if(s->checkFullSudoku()){
        ErrorMessage *er = new ErrorMessage("Sudoku je resen!");
        QPoint qp = QCursor::pos();
        qp.setX(qp.x() - 100);
        er->move(qp);
        er->show();
        isSolved = true;
        return ;
    }

    for(i = 0; i < dimension; i++){
        for(j = 0; j < dimension; j++){
            QString qs = btns[i][j]->text();
            int newNumber = qs.toInt();
            int oldNumber = grid[i][j];
            grid[i][j] = newNumber;
            if(!s->checkSudoku()){
                grid[i][j] = oldNumber;
                qs = "";
                btns[i][j]->setText(qs);
                ErrorMessage *er = new ErrorMessage("Uneli ste neispravan broj");
                er->move(QCursor::pos());
                er->show();
            }
        }
    }
}


void SudokuWindow::onClick(){
    QPoint qp = QCursor::pos();
    p->move(qp);
    p->show();
}
