
#include"sudokuwindow.h"
#include<QGridLayout>
#include<QPushButton>
#include<QApplication>
#include<QKeyEvent>
#include<iostream>
#include<math.h>

Popup::Popup(int dim, QWidget *parent) : QWidget(parent)
{
    dimension = (int)sqrt(dim);
    dimension = dimension * dimension;
    QGridLayout *layout = new QGridLayout(this);
    layout->setSpacing(4);


    QList<QString> numbers;

    int i, j, k;
    for( i = 1; i <= dimension; i++){

        QString qs = QString::number(i);
        numbers.append(qs);
    }

    int sqrtDim = (int)sqrt(dimension);
    QPushButton *btn = new QPushButton("0", this);
    btn->setFixedSize(40, 40);
    layout->addWidget(btn, 0, 0);
    connect(btn, &QPushButton::clicked, this, &Popup::exit);


    for(i = 1, k = 1; i <= sqrtDim; i++){
        for(j = 0; j < sqrtDim; j++, k++){
            btn = new QPushButton(QString::number(k), this);

            btn ->setFixedSize(40, 40);
            layout->addWidget(btn, i, j);

            connect(btn, &QPushButton::clicked, this, &Popup::exit);
        }
    }
    setLayout(layout);
}

void Popup::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape){
        close();
    }
}

void Popup::onClick(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    btn = button;
}

void Popup::exit(){
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if(button->text().toInt() != 0){
        btn->setText(button->text());
    }else{
        btn->setText("");
    }
    close();
}
