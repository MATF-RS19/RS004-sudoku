#ifndef POPUP_H
#define POPUP_H

#include<QPushButton>
#include <QWidget>

using namespace std;
class Popup : public QWidget
{
    Q_OBJECT
public:
    explicit Popup(int dimension = 9, QWidget *parent = nullptr);

    QPushButton *btn;
    int dimension;

public slots:
    void exit();
    void onClick();



protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif
