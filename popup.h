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
    /* Closes the current window
     * It is called once any Popup button is pressed
     * updates btn text value accordingly
     */
    void exit();

    /* Is called once a button in a SudokuWindow object is pressed
     * sets btn to point towards the sender object
     */
    void onClick();



protected:
    /* Handles keyboard inputs
     * Only the escape key is defined and causes the window to close
     */
    void keyPressEvent(QKeyEvent *e);
};

#endif
