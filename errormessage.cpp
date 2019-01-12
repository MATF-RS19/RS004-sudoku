#include "errormessage.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QPushButton>

ErrorMessage::ErrorMessage(QString s, QWidget *parent) : QWidget(parent)
{

    this->setFixedWidth(s.length() + 200);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(3);

    QLabel *ql = new QLabel(s, this);

    layout->addWidget(ql, 0, Qt::AlignJustify);

    QPushButton *btn = new QPushButton(this);
    btn->setText("OK");
    btn->setFixedSize(40, 40);
    layout->addWidget(btn, 0, Qt::AlignCenter);

    setLayout(layout);

    connect(btn, &QPushButton::clicked, this, &ErrorMessage::exit);
}

void ErrorMessage::exit(){
    close();
}

void ErrorMessage::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Escape){
        close();
    }
}
